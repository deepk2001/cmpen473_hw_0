/**************************************************
* File:  hw1zanotti2.c 
* Homework 1 Program 2
* By August Zanotti
* CMPEN 473, Spring 2026, Penn State University
* 
* This is a LED blinking program in C, 
*  for Raspberry Pi 4 Computer - with Raspberry Pi OS 32bit
*  - intended to toggle 4 LEDs red, green, blue, orange
*       in response to key presses
*          > r - red LED toggle
*          > g - green LED toggle
*          > b - blue LED toggle
*          > o - orange LED toggle
* 
* Raspberry Pi 4 Computer (RPi4) GPIO pin connections:
*   Red    LED on GPIO 05 - with 220 Ohm resistor in series
*   Green  LED on GPIO 06 - with 220 Ohm resistor in series
*   Blue   LED on GPIO 22 - with 220 Ohm resistor in series
*   Orange LED on GPIO 23 - with 220 Ohm resistor in series
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


int get_pressed_key(void)
{
  int             ch;

  ch = getchar();   // Must followed by an <Enter> key

  return ch;
}


int main( void )
{
  struct io_peripherals *io;
  bool  done = false;
  
  io = import_registers();
  if (io != NULL)
  {
    /* print where the I/O memory was actually mapped to */
    printf( "mem at 0x%8.8X\n", (unsigned int)io );
    
    /* set the pin function to OUTPUT for GPIO05 */
    /* set the pin function to OUTPUT for GPIO06 */
    /* set the pin function to OUTPUT for GPIO22 */
    /* set the pin function to OUTPUT for GPIO23 */
    io->gpio->GPFSEL0.field.FSEL5 = GPFSEL_OUTPUT;   //GPIO 05
    io->gpio->GPFSEL0.field.FSEL6 = GPFSEL_OUTPUT;   //GPIO 06
    io->gpio->GPFSEL2.field.FSEL2 = GPFSEL_OUTPUT;   //GPIO 22
    io->gpio->GPFSEL2.field.FSEL3 = GPFSEL_OUTPUT;   //GPIO 23
    
    /* set initial output state - OFF */
    GPIO_CLR(io->gpio, 05);
    GPIO_CLR(io->gpio, 06);
    GPIO_CLR(io->gpio, 22);
    GPIO_CLR(io->gpio, 23);
    
    printf("\n Press 'r' to toggle the Red    LED\n");
    printf(  " Press 'g' to toggle the Green  LED\n");
    printf(  " Press 'b' to toggle the Blue   LED\n");
    printf(  " Press 'o' to toggle the Orange LED\n");
    printf(  " Be sure to hit <Enter> key\n");
    printf(  " Press any other key will exit\n");
    
    do
    {
      switch (get_pressed_key())
      {
        case 'r':
          if (GPIO_READ(io->gpio, 05) == 0)
          {
            GPIO_SET(io->gpio, 05);
          }
          else
          {
            GPIO_CLR(io->gpio, 05);
          }
          break;

        case 'g':
          if (GPIO_READ(io->gpio, 06) == 0)
          {
            GPIO_SET(io->gpio, 06);
          }
          else
          {
            GPIO_CLR(io->gpio, 06);
          }
          break;

        case 'b':
          if (GPIO_READ(io->gpio, 22) == 0)
          {
            GPIO_SET(io->gpio, 22);
          }
          else
          {
            GPIO_CLR(io->gpio, 22);
          }
          break;

        case 'o':
          if (GPIO_READ(io->gpio, 23) == 0)
          {
            GPIO_SET(io->gpio, 23);
          }
          else
          {
            GPIO_CLR(io->gpio, 23);
          }
          break;

        case 10:               /* it is Line Feed, New Line, or Enter Key character */
          usleep(100*1000);    /* numbers in micro seconds (100msec.)  */
          break;

        default:
          done = true;
          break;
      }
    } while (!done);
    
    
    /* when finished, clean the GPIO pins */
    io->gpio->GPFSEL0.field.FSEL5 = GPFSEL_INPUT;
    io->gpio->GPFSEL0.field.FSEL6 = GPFSEL_INPUT;
    io->gpio->GPFSEL2.field.FSEL2 = GPFSEL_INPUT;
    io->gpio->GPFSEL2.field.FSEL3 = GPFSEL_INPUT;

    printf("\n Key hit is not valid key, quiting loop\n");
    
  }
  else
  {
    ; /* warning message already issued */
  }

  printf("\n Main program done\n \n"); 

  return 0;
}
