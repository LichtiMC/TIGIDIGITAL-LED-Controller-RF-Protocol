#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

#include "PL1167_nRF24.h"
#include "MiLightRadio.h"

#define CE_PIN 7
#define CSN_PIN 8

RF24 radio(CE_PIN, CSN_PIN);
PL1167_nRF24 prf(radio);
MiLightRadio mlr(prf);

void setup()
{
  Serial.begin(115200);
  printf_begin();
  delay(1000);
  Serial.println("# Transmitter starting");
  mlr.begin();
}


static int dupesPrinted = 0;
static bool receiving = true;
static bool escaped = false;
uint8_t outgoingPacket[5];
static uint8_t outgoingPacketPos = 0;
static uint8_t nibble;
static enum {
  IDLE,
  HAVE_NIBBLE,
  COMPLETE,
} state;

void loop()
{
  if (receiving) {
    if (mlr.available()) {
      printf("\n");
      uint8_t packet[5];
      size_t packet_length = sizeof(packet);
      mlr.read(packet, packet_length);
      for (int i = 0; i < packet_length - 1; i++) {
        printf("%02X ", packet[i]);
      }
    }
    int dupesReceived = mlr.dupesReceived();
    for (; dupesPrinted < dupesReceived; dupesPrinted++) {
      printf(".");
    }
  }

  while (Serial.available()) {
    char inChar = (char)Serial.read();
    uint8_t val = 0;
    bool have_val = true;

    if (inChar >= '0' && inChar <= '9') {
      val = inChar - '0';
    } else if (inChar >= 'a' && inChar <= 'f') {
      val = inChar - 'a' + 10;
    } else if (inChar >= 'A' && inChar <= 'F') {
      val = inChar - 'A' + 10;
    } else {
      have_val = false;
    }

    if (!escaped) {
      if (have_val) {
        switch (state) {
          case IDLE:
            nibble = val;
            state = HAVE_NIBBLE;
            break;
          case HAVE_NIBBLE:
            if (outgoingPacketPos < sizeof(outgoingPacket)) {
              outgoingPacket[outgoingPacketPos++] = (nibble << 4) | (val);
            } else {
              Serial.println("# Error: outgoing packet buffer full/packet too long");
            }
            if (outgoingPacketPos + 1 >= sizeof(outgoingPacket)) {
              outgoingPacket[4] = ( outgoingPacket[0] + outgoingPacket[1] + outgoingPacket[2] ) ^ outgoingPacket[3]; //CRC
              state = COMPLETE;
            } else {
              state = IDLE;
            }
            break;
          case COMPLETE:
            Serial.println("# Info: outgoing packet complete. Press enter to send.");
            break;
        }
      } else {
        switch (inChar) {
          case ' ':
          case '\n':
          case '\r':
          case '.':
            if (state == COMPLETE) {
              mlr.write(outgoingPacket, sizeof(outgoingPacket));
            }
            if(inChar != ' ') {
              outgoingPacketPos = 0;
              state = IDLE;
            }
            if (inChar == '.') {
              mlr.resend();
              delay(1);
            }
            break;
          case 'x':
            Serial.println("# Escaped to extended commands: r - Toggle receiver; Press enter to return to normal mode.");
            escaped = true;
            break;
        }
      }
    } else {
      switch (inChar) {
        case '\n':
        case '\r':
          outgoingPacketPos = 0;
          state = IDLE;
          escaped = false;
          break;
        case 'r':
          receiving = !receiving;
          if (receiving) {
            Serial.println("# Now receiving");
          } else {
            Serial.println("# Now not receiving");
          }
          break;
      }
    }
  }
  
//  outgoingPacket[0] = 0xFF;
//  outgoingPacket[1] = 0xCC;
//  outgoingPacket[2] = 0x01; //ID
//  outgoingPacket[3] = 0x00; //CMD
//  outgoingPacket[4] = ( outgoingPacket[0] + outgoingPacket[1] + outgoingPacket[2] ) ^ outgoingPacket[3]; //CRC
//  for (size_t i = 0; i < sizeof(outgoingPacket); i++) {
//    printf("%02X ", outgoingPacket[i]);
//  }
//  Serial.println();
//  for (int j = 0; j < 20; j++) {
//    //mlr.write(outgoingPacket, sizeof(outgoingPacket));
//  }
//  delay(1000);
//  outgoingPacket[0] = 0xFF;
//  outgoingPacket[1] = 0xCC;
//  outgoingPacket[2] = 0x01; //ID
//  outgoingPacket[3] = 0x01; //CMD
//  outgoingPacket[4] = ( outgoingPacket[0] + outgoingPacket[1] + outgoingPacket[2] ) ^ outgoingPacket[3]; //CRC
//  for (size_t i = 0; i < sizeof(outgoingPacket); i++) {
//    printf("%02X ", outgoingPacket[i]);
//  }
//  Serial.println();
//  for (int j = 0; j < 40; j++) {
//    //mlr.write(outgoingPacket, sizeof(outgoingPacket));
//  }
//  delay(1000);
}
