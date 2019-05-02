#include "mbed.h"
#include "MMA7660FC.h"

MMA7660FC Acc(I2C_SDA, I2C_SCL, ADDR_MMA7660); 

struct ACC_UINT8_VECTOR {
  uint8_t x;
  uint8_t y;
  uint8_t z;
};

ACC_UINT8_VECTOR sample;

int main(void)
{
  Acc.init();
  while(1) {
    sample.x = 0b111111 & (uint8_t) Acc.read_x();
    sample.y = 0b111111 & (uint8_t) Acc.read_y();
    sample.z = 0b111111 & (uint8_t) Acc.read_z();

    printf("%d %d %d\r\n", (int)sample.x, (int)sample.y, (int)sample.z);
    wait(0.5);
  }

  return 0;
}