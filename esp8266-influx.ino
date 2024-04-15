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

#define WIFI_SSID 
#define WIFI_PASSWORD 
#define INFLUXDB_URL 
#define INFLUXDB_TOKEN 
#define INFLUXDB_ORG 
#define INFLUXDB_BUCKET 

#define TZ_INFO "EET-2EEST,M3.5.0/3,M10.5.0/4"

InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Data point
Point sensor("energy_data");

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Device...");

  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);  // Increase delay for less spammy output
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("Connected to SSID: ");
  Serial.println(WiFi.SSID());

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
  sensor.clearFields();

  // Generate random data for solar panel voltage and battery voltage
  float solarPanelVoltage = random(120, 140) / 10.0; // Simulating 12.0V to 14.0V
  float batteryVoltage = random(110, 130) / 10.0; // Simulating 11.0V to 13.0V

  sensor.addField("solarPanelVoltage", solarPanelVoltage);
  sensor.addField("batteryVoltage", batteryVoltage);

  Serial.print("Writing: ");
  Serial.println(sensor.toLineProtocol());

  if (WiFi.RSSI() == 0 && wifiMulti.run() != WL_CONNECTED) {
    Serial.println("Wifi connection lost. Reconnecting...");
  }

  if (!client.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  Serial.println("Wait 10s");
  delay(10000);
}
