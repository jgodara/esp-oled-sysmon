#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Wifi SSID
const char *ssid = "WifiSSID";
const char *pass = "Password";

WiFiClient client;
HTTPClient http;

DynamicJsonBuffer jsonBuffer(200);

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();

  display.setTextSize(1.6);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  display.println("Connecting to WiFi:");
  display.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);  
  }

  display.println("Connected!");
  display.display(); 
}

void loop() {
  // Should be the HOST/IP of the flask server
  http.begin("http://the_ip_addr:9795/api/system");
  int httpCode = http.GET();
  display.clearDisplay();

  display.setTextSize(1.6);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  if (httpCode == 200) {
    JsonObject& root = jsonBuffer.parseObject(http.getString());
    if (!root.success()) {
      display.println("Parse failed");
      return;
    }

    JsonArray& cpus = root["cpu"];
    showCpus(cpus);

    JsonObject& memory = root["mem"];
    showMemory(memory);

    display.printf("Swap: %.2f%%\n", root["swp"].as<double>());
    
  } else {
    display.println("HTTP GET FAILED");  
  }
  
  display.display();


  delay(500);
}

void showCpus(JsonArray& cpus) {
  display.printf("CPUs (%d)\n", cpus.size());
  for (long cpu : cpus) {
    display.printf("%d ", cpu);
  }
  display.println("%\n");
}

void showMemory(JsonObject& mem) {
  double totalBytes = mem["total"].as<double>();
  double availableBytes = mem["used"].as<double>();

  display.println("Memory (GiB):");
  // FIXME: Jay, you're a fucking idiot.
  display.printf("%.2f of %.2f\n", availableBytes / 1024 / 1024 / 1024, totalBytes / 1024 / 1024 / 1024);
}
