#if defined(ESP32)
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#define DEVICE "ESP32"
#elif defined(ESP8266)
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#define DEVICE "ESP8266"
#endif

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define INFLUXDB_URL ""
#define INFLUXDB_TOKEN ""
#define INFLUXDB_ORG ""
#define INFLUXDB_BUCKET ""
#define TZ_INFO "EET-2EEST,M3.5.0/3,M10.5.0/4"

InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
Point sensor("energy_data");

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Device...");

  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nWiFi Connected!");
  Serial.println("Connected to SSID: " + WiFi.SSID());

  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    float batteryVoltage = data.substring(0, data.indexOf(',')).toFloat();
    data = data.substring(data.indexOf(',') + 1);
    float batteryPercentage = data.substring(0, data.indexOf(',')).toFloat();
    float solarPanelVoltage = data.substring(data.indexOf(',') + 1).toFloat();

    sensor.clearFields();
    sensor.addField("solarPanelVoltage", solarPanelVoltage);
    sensor.addField("batteryVoltage", batteryVoltage);
    sensor.addField("batteryPercentage", batteryPercentage);

    if (!client.writePoint(sensor)) {
      Serial.print("InfluxDB write failed: ");
      Serial.println(client.getLastErrorMessage());
    }
    Serial.println("Data sent to InfluxDB");
  }
  delay(10000); // Delay pentru reducerea traficului de date
}
