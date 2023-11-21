la#include <SPI.h>
#include <mcp2515.h>

#define MENU_PIN 5
#define ESC_PIN 6

struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(10);

unsigned long timing, timing2;  // for delay

void setup() {
  pinMode(MENU_PIN, INPUT_PULLUP);
  //FMUX present
  canMsg1.can_id = 0x122;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x00; //0x02; //0x80; //0x40;
  canMsg1.data[1] = 0x00;
  canMsg1.data[2] = 0x00;
  canMsg1.data[3] = 0x00;
  canMsg1.data[4] = 0x00;
  canMsg1.data[5] = 0x00; //0x02; //0xFF;
  canMsg1.data[6] = 0x00; //Volume potentiometer button
  canMsg1.data[7] = 0x00;

  //MENU button
  canMsg2.can_id = 0x122;
  canMsg2.can_dlc = 8;
  canMsg2.data[0] = 0x00; //0x02; //0x80; //0x40;
  canMsg2.data[1] = 0x40;
  canMsg2.data[2] = 0x00;
  canMsg2.data[3] = 0x00;
  canMsg2.data[4] = 0x00;
  canMsg2.data[5] = 0x00; //0x02; //0xFF;
  canMsg2.data[6] = 0x00; //Volume potentiometer button
  canMsg2.data[7] = 0x00;

  while (!Serial);
  Serial.begin(115200);

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  Serial.println("Universal multiplexed panel (Multimedia control) emulator");
}

void loop() {
  if (millis() - timing > 200) {  //delay 200ms
    timing = millis();
    mcp2515.sendMessage(&canMsg1);
   // Serial.println("FMUX present");
  }

  if (digitalRead(MENU_PIN) == 0) {
    if (millis() - timing2 > 200) {  //delay 200ms
    timing2 = millis();
    mcp2515.sendMessage(&canMsg2);
   // Serial.println("FMUX menu");
    }
  }
}
