/**************************************************
* File:  hw1wang2.c 
* Homework 1 Part 2
* By Robert Wang
* CMPEN 473, Spring 2026, Penn State University
* 
* Revision V1.0 On 01/21/2026
* 
* This is a sample LED on/off program in C, 
*  for Raspberry Pi 4 Computer - with Raspberry Pi OS 32bit
*  - 1. 'r' => Red    LED on/off, hit 'r' key to toggle Red    LED on/off
*    2. 'g' => Green  LED on/off, hit 'g' key to toggle Green  LED on/off
*    3. 'b' => Blue   LED on/off, hit 'g' key to toggle Blue   LED on/off
*    4. 'o' => Orange LED on/off, hit 'g' key to toggle Orange LED on/off
*    5. 'q' => QUIT program
*    6. any other keys are ignored
*    7. works without <Enter> key, like game playing
*    8. use 'include' to create keyboard function - as an example 
* 
* Raspberry Pi 4 Computer (RPi4) GPIO pin connections:
*   Red    LED on GPIO 05 - with 330 Ohm resistor in series
*   Green  LED on GPIO 06 - with 330 Ohm resistor in series
*   Blue   LED on GPIO 22 - with 330 Ohm resistor in series
*   Orange LED on GPIO 23 - with 330 Ohm resistor in series
* 
* RPi4 GPIO pin configuration - OUTPUT and INPUT
*   OUTPUT: Logic high => 3.3V at the pin, up to 10mA current source
*           Logic low  => 0.0V at the pin, up to 10mA current sink
* 
* Homework 1 Part 2 turns on/off Red, Green, Blue, and Orange LEDs by keyboard.
*   Program stops by hitting 'q' key.  
*   Any other key than 'r', 'g', 'b', 'o', and 'q' keys are ignored.
*   >>>>> works without <Enter> key, like game playing <<<<<
*   This program use 'include' to create keyboard function - as an example 
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
#include "keypress.h"


int main( void )
{
  struct io_peripherals *io;
  bool  done = false;
  
  io = import_registers();
  if (io != NULL)
  {
    /* print where the I/O memory was actually mapped to */
    printf( "mem at 0x%8.8X\n", (unsigned int)io );
    
    /* set the pin function to OUTPUT for GPIO 12 - Red   LED */
    /* set the pin function to OUTPUT for GPIO 13 - Green LED */
    io->gpio->GPFSEL0.field.FSEL5 = GPFSEL_OUTPUT;   //GPIO 05
    io->gpio->GPFSEL0.field.FSEL6 = GPFSEL_OUTPUT;   //GPIO 06
    io->gpio->GPFSEL2.field.FSEL2 = GPFSEL_OUTPUT;   //GPIO 22
    io->gpio->GPFSEL2.field.FSEL3 = GPFSEL_OUTPUT;   //GPIO 23
    
    /* set initial output state - ON */
    GPIO_SET(io->gpio, 05);
    GPIO_SET(io->gpio, 06);
    GPIO_SET(io->gpio, 22);
    GPIO_SET(io->gpio, 23);
    
    printf("\n Press 'r' to toggle the Red    LED\n");
    printf(  " Press 'g' to toggle the Green  LED\n");
    printf("\n Press 'b' to toggle the Blue   LED\n");
    printf(  " Press 'o' to toggle the Orange LED\n");
    printf(  " Press 'q' to QUIT this program\n");
    printf(  " Any other key press will ignored\n");
    
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
        
        case 'q':
          done = true;
          break;

        default:               /* it is Line Feed, New Line, or Enter Key character */
          usleep(100*1000);    /* numbers in micro seconds (100msec.)  */
          break;
      }
    } while (!done);
    
    
    /* when finished, clean the GPIO pins */
    io->gpio->GPFSEL0.field.FSEL5 = GPFSEL_INPUT;
    io->gpio->GPFSEL0.field.FSEL6 = GPFSEL_INPUT;
    io->gpio->GPFSEL2.field.FSEL2 = GPFSEL_INPUT;
    io->gpio->GPFSEL2.field.FSEL3 = GPFSEL_INPUT;

    printf("\n 'q' key pressed, quiting loop\n");
    
  }
  else
  {
    ; /* warning message already issued */
  }

  printf("\n Main program done\n \n"); 

  return 0;
}
