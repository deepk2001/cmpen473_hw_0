/**************************************************
* File:  hw1wang1.c 
* Homework 1
* By Robert Wang
* CMPEN 473, Spring 2026, Penn State University
* 
* Revision V1.0 On 01/21/2026
* 
* This is a LED blinking program in C, 
*  for Raspberry Pi 4 Computer - with Raspberry Pi OS 32bit
*  - 1. Blink Red    LED connected at GPIO 05 pin
*    2. Blink Green  LED connected at GPIO 06 pin
*    3. Blink Blue   LED connected at GPIO 22 pin
*    4. Blink Orange LED connected at GPIO 23 pin
*    5. Blinking rate set to 1 second per LED with sleep() function
*    6. Program runs indefinitely, until 'control c' key hit
*    7. Use usleep() function if faster rate is desired
* 
* Raspberry Pi 4 Computer (RPi4) GPIO pin connections:
*   Red    LED on GPIO 05 - with 330 Ohm resistor in series
*   Green  LED on GPIO 06 - with 330 Ohm resistor in series
*   Blue   LED on GPIO 22 - with 330 Ohm resistor in series
*   Orange LED on GPIO 23 - with 330 Ohm resistor in series
* 
***************************************************/

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
    
    /* set the pin function to OUTPUT for GPIO12 */
    /* set the pin function to OUTPUT for GPIO23 */
    io->gpio->GPFSEL0.field.FSEL5 = GPFSEL_OUTPUT;   //GPIO 05
    io->gpio->GPFSEL0.field.FSEL6 = GPFSEL_OUTPUT;   //GPIO 06
    io->gpio->GPFSEL2.field.FSEL2 = GPFSEL_OUTPUT;   //GPIO 22
    io->gpio->GPFSEL2.field.FSEL3 = GPFSEL_OUTPUT;   //GPIO 23

    printf("\n Hit 'ctl c' to quit \n");
    
    while (1)   // Loop forever
    {
      GPIO_SET(io->gpio, 05);
      sleep(1);

      GPIO_CLR(io->gpio, 05);
      GPIO_SET(io->gpio, 06);
      sleep(1);

      GPIO_CLR(io->gpio, 06);
      GPIO_SET(io->gpio, 22);
      sleep(1);

      GPIO_CLR(io->gpio, 22);
      GPIO_SET(io->gpio, 23);
      sleep(1);

      GPIO_CLR(io->gpio, 23);
    }

  }
  else
  {
    ; /* warning message already issued */
  }

  printf("\n main function done\n");   // this line never executed - ctl c

  return 0;
}
