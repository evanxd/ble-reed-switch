#include <SPI.h>
#include <BLEPeripheral.h>

#define BLE_REQ          9
#define BLE_RDY          8
#define BLE_RST         -1
#define REED_SWITCH_PIN  4

BLEPeripheral         blePeripheral       = BLEPeripheral(BLE_REQ, BLE_RDY, BLE_RST);
BLEService            reedSwitchService   = BLEService("25104E8300001000800000805F9B34FB");
BLECharCharacteristic stateCharacteristic = BLECharCharacteristic("25104E8400001000800000805F9B34FB", BLERead | BLENotify);

void setup() {
  pinMode(REED_SWITCH_PIN, INPUT);
  blePeripheral.setLocalName("Reed Switch");
  blePeripheral.setAdvertisedServiceUuid(reedSwitchService.uuid());
  blePeripheral.addAttribute(reedSwitchService);
  blePeripheral.addAttribute(stateCharacteristic);
  blePeripheral.begin();
}

void loop() {
  blePeripheral.poll();
  char reedSwitchValue = digitalRead(REED_SWITCH_PIN);
  if (stateCharacteristic.value() != reedSwitchValue) {
    stateCharacteristic.setValue(reedSwitchValue);
  }
}
