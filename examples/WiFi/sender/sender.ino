#include <Artnet.h>

// WiFi stuff
const char* ssid = "your-ssid";
const char* pwd = "your-password";
const IPAddress ip(192, 168, 1, 201);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

ArtnetSender artnet;
uint32_t universe = 1;

const uint16_t size = 512;
uint8_t data[size];
uint8_t value = 0;

void setup()
{
    // WiFi stuff
    WiFi.begin(ssid, pwd);
    WiFi.config(ip, gateway, subnet);
    while (WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(500); }
    Serial.print("WiFi connected, IP = "); Serial.println(WiFi.localIP());

    artnet.begin("127.0.0.1");
}

void loop()
{
    value = millis() % 256;
    memset(data, value, size);

    artnet.set(universe, data, size);
    artnet.streaming(); // automatically send set data in 40fps
}
