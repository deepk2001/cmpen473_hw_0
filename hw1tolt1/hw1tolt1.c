/**************************************************
* File:  hw1tolt1.c 
* Homework 1 Program 1
* By Kyusun Choi / Eric Tolt
* CMPEN 473, Spring 2026, Penn State University
* 
* This is an LED blinking program in C, 
*  for Raspberry Pi 4 Computer - with Raspberry Pi OS 32bit
*  - 1. Blink Red, Green, Blue, Orange LEDs on GPIO pins 05, 06, 22, 23 respectively
*    2. Blinking rate set to 0.5 seconds per LED with usleep() function
*    3. Program runs indefinitely, until 'control c' key hit
* 
* Raspberry Pi 4 Computer (RPi4) GPIO pin connections:
*   
*   Red    LED on GPIO 05
*   Green  LED on GPIO 06
*   Blue   LED on GPIO 22
*   Orange LED on GPIO 23
*
*   
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

int main(void)
{
  struct io_peripherals *io;

  io = import_registers();
  if (io != NULL)
  {
    /* print where the I/O memory was actually mapped to */
    printf( "mem at 0x%8.8X\n", (unsigned int)io );
    
    //setting pin function to OUTPUT for GPIOs 5, 6, 22, 23

    io->gpio->GPFSEL0.field.FSEL5 = GPFSEL_OUTPUT; //GPIO 5
    io->gpio->GPFSEL0.field.FSEL6 = GPFSEL_OUTPUT; //GPIO 6
    io->gpio->GPFSEL2.field.FSEL2 = GPFSEL_OUTPUT; //GPIO 22
    io->gpio->GPFSEL2.field.FSEL3 = GPFSEL_OUTPUT; //GPIO 23
    
    printf("\n Hit 'ctrl c' to quit \n");
    
    //set GPIO pins to known state (OFF)

    GPIO_CLR(io->gpio, 5);
    GPIO_CLR(io->gpio, 6);
    GPIO_CLR(io->gpio, 22);
    GPIO_CLR(io->gpio, 23);

    while (1)   // Loop forever
    {
      GPIO_SET(io->gpio, 5);
      
      usleep(500000);
      
      GPIO_CLR(io->gpio, 5);
      GPIO_SET(io->gpio, 6);
      
      usleep(500000);

      GPIO_CLR(io->gpio, 6);
      GPIO_SET(io->gpio, 22);

      usleep(500000);

      GPIO_CLR(io->gpio, 22);
      GPIO_SET(io->gpio, 23);

      usleep(500000);
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
