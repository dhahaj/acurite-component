
#pragma once

#include "esphome.h"
#include "esphome/core/log.h"
#include "esphome/core/component.h"
#include "esphome/components/wifi/wifi_component.h"

#define RING_BUFFER_SIZE 256

#define SYNC_LENGTH 2200

#define SYNC_HIGH 600
#define SYNC_LOW 600
#define BIT1_HIGH 400
#define BIT1_LOW 220
#define BIT0_HIGH 220
#define BIT0_LOW 400

#define DATAPIN 14
#define LEDPIN 2

/// @brief AcuriteSensor component
class AcuriteSensor : public esphome::Component
{
public:
  esphome::sensor::Sensor *temperature_sensor = new esphome::sensor::Sensor();
  esphome::sensor::Sensor *humidity_sensor = new esphome::sensor::Sensor();

  bool connected = false;

  bool isSync(unsigned int idx);
  int timeToBits(unsigned int t0, unsigned int t1);
  unsigned long extractData(unsigned int syncIndex, unsigned int bits, unsigned int startPos, unsigned int size);
  bool check_wifi_status(void);
  void setup(void) override;
  void loop() override;
  void handle_interrupt();

  AcuriteSensor()
  {
    instance = this; // Set the instance pointer in the constructor
  }

private:
  volatile unsigned long timings[RING_BUFFER_SIZE];
  volatile unsigned int syncIndex1 = 0; // index of the first sync signal
  volatile unsigned int syncIndex2 = 0; // index of the second sync signal
  volatile bool received = false;
  volatile bool interruptFlag = false;
  static AcuriteSensor *instance; // Static instance pointer

  /// @brief Interrupt handler
  static void IRAM_ATTR interrupt_handler()
  {
    if (instance)
    {
      instance->handle_interrupt();
    }
  }

 

 
};
