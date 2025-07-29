//XIAO ESP32-S3 Usb host for HID keyboards to serial


#include "EspUsbHost.h"

#define LED_PIN LED_BUILTIN
HardwareSerial mySerial(0);  // Use UART0

class MyEspUsbHost : public EspUsbHost {
public:
  void onKeyboardKey(uint8_t ascii, uint8_t keycode, uint8_t modifier) {
    digitalWrite(LED_PIN, HIGH);
    delay(50);
    digitalWrite(LED_PIN, LOW);

    if (' ' <= ascii && ascii <= '~') {
      mySerial.printf("%c", ascii);
    } else if (ascii == '\r') {
      mySerial.println();
    }
  }
  void onConfig(uint8_t num, const uint8_t* data) {}
};

MyEspUsbHost usbHost;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  // Explicitly attach hardware UART0 to D6 (TX, GPIO6), D7 (RX, GPIO7)
  mySerial.begin(115200, SERIAL_8N1, 44, 43);  // RX=7, TX=6 for XIAO
  // If your FTDI RX is connected to D6(G6), this is correct.
  delay(500);
  usbHost.begin();
  mySerial.println("Setup complete!");  // This should now print
}

void loop() {
  usbHost.task();
}
