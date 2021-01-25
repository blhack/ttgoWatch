
void porchLightOn() {
  const char ALL_RED[] = "{\"method\": \"setPilot\", \"params\": {\"dimming\": 100, \"state\": true, \"w\": 255}}";
  char packetBuffer[255];
  const unsigned int LIGHT_PORT = 38899;
  WiFiUDP Udp;
  //broadcastIp ip(10,69,0,255);
  
  Udp.beginPacket({10, 69, 0, 68}, LIGHT_PORT);
  Udp.print(ALL_RED);
  Udp.endPacket();
}
