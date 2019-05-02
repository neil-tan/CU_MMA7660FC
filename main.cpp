#include "mbed.h"
#include "mbed_events.h"
#include "MMA7660FC.h"

MMA7660FC Acc(I2C_SDA, I2C_SCL, ADDR_MMA7660); 
EventQueue printQueue;

struct ACC_UINT8_VECTOR {
  uint8_t x;
  uint8_t y;
  uint8_t z;
};

ACC_UINT8_VECTOR sample;

void print() {
    //printf("%d, %d, %d\r\n", sample.x, sample.y, sample.z);
}

void accTimerHandler(void) {
  sample.x = 0b111111 & (uint8_t) Acc.read_x();
  sample.y = 0b111111 & (uint8_t) Acc.read_y();
  sample.z = 0b111111 & (uint8_t) Acc.read_z();
  printQueue.call(&print);
}

int main(void)
{
      // create a thread that'll run the event queue's dispatch function
    Thread eventThread;
    eventThread.start(callback(&printQueue, &EventQueue::dispatch_forever));

    Ticker sensorTick;
    sensorTick.attach(&accTimerHandler, 1.0f/1); //1Hz

  while(1) {
    printf("background thread\r\n");
    wait(5);
  }

  return 0;
}