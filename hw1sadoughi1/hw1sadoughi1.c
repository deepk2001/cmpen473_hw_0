// header files - at /usr/include and ../include and .
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <termios.h>
#include <fcntl.h>
#include <pthread.h>
#include "../include/import_registers.h"
#include "../include/cm.h"
#include "../include/gpio.h"
#include "../include/uart.h"
#include "../include/spi.h"
#include "../include/bsc.h"
#include "../include/pwm.h"
#include "../include/enable_pwm_clock.h"
#include "../include/io_peripherals.h"
#include "../include/wait_period.h"
#include "../include/FIFO.h"
#include "../include/MPU6050.h"
#include "../include/MPU9250.h"
#include "../include/wait_key.h"

int main( void )
{
  struct io_peripherals *io;

  io = import_registers();
  if (io != NULL)
  {
    /* print where the I/O memory was actually mapped to */
    printf( "mem at 0x%8.8X\n", (unsigned int)io );
    
    io->gpio->GPFSEL0.field.FSEL5 = GPFSEL_OUTPUT;   //red
    io->gpio->GPFSEL0.field.FSEL6 = GPFSEL_OUTPUT;   //green
    io->gpio->GPFSEL2.field.FSEL2 = GPFSEL_OUTPUT;   //blue
    io->gpio->GPFSEL2.field.FSEL3 = GPFSEL_OUTPUT;   //orange
    
    printf("\n Hit 'ctl c' to quit \n");
    
    while (1)   // Loop forever
    {
      GPIO_SET(io->gpio, 5); //set red
      
      sleep(1);
      
      GPIO_SET(io->gpio, 6); //set green
      
      sleep(1);
      
      GPIO_SET(io->gpio, 22); //set blue
      
      sleep(1);
      
      GPIO_SET(io->gpio, 23); //set orange
      
      sleep(1);
      
      GPIO_CLR(io->gpio, 5); //clear red
      GPIO_CLR(io->gpio, 6); //clear green      
      GPIO_CLR(io->gpio, 22); //clear blue  
      GPIO_CLR(io->gpio, 23); //clear orange
      
      sleep(1);
    }
  }
  else
  {
    ; /* warning message already issued */
  }

  printf("\n main function done\n");   // this line never executed - ctl c

  return 0;
}
