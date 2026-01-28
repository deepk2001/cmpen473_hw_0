/**************************************************
* File:  hw1ottaviano2.c 
* Homework 1 Part 2
* By Anthony Ottaviano
* CMPEN 473, Spring 2026, Penn State University
* 
* 
* This is an LED toggling program in C, 
*  for Raspberry Pi 4 Computer - with Raspberry Pi OS 32bit
*    1. Toggle LEDs connected at GPIO 22,23,05,06 pins with keyboard
*    2. Program runs indefinitely, until 'control c' key hit
* 
* Raspberry Pi 4 Computer (RPi4) GPIO pin connections:
*   Red   LED on GPIO 12 - with 330 Ohm resistor in series
*   Green LED on GPIO 23 - with 330 Ohm resistor in series
*   Blue  LED on GPIO 05 - with 330 Ohm resistor in series
*   Yellow  LED on GPIO 06 - with 330 Ohm resistor in series
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
  
  /* struct used for storing termios settings */
  struct termios terminal_settings;
  /* get current terminal settings */
  tcgetattr(STDIN_FILENO, &terminal_settings);
  /* disable canonical mode and echo flags */
  terminal_settings.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &terminal_settings);
  
  /* make stdin nonblocking */
  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
  
  if (io != NULL)
  {
    /* print where the I/O memory was actually mapped to */
    printf( "mem at 0x%8.8X\n", (unsigned int)io );
    
    /* set the pin function to OUTPUT for GPIO pins */
    io->gpio->GPFSEL2.field.FSEL2 = GPFSEL_OUTPUT;   //GPIO 22
    io->gpio->GPFSEL2.field.FSEL3 = GPFSEL_OUTPUT;   //GPIO 23
    io->gpio->GPFSEL0.field.FSEL5 = GPFSEL_OUTPUT;   //GPIO 05
    io->gpio->GPFSEL0.field.FSEL6 = GPFSEL_OUTPUT;   //GPIO 06
    
    printf("\n Hit 'ctl c' to quit \n");
    
    bool rset = false, gset = false, bset = false, yset = false; 
    
    while (1)   // Loop forever
    {
      /* get most recently pressed character */
      char key = getchar();
      /* if r, g, b, or y hit, toggle the corresponding boolean */
      if (key == 'r') {
        rset = !rset;
      }
      if (key == 'g') {
        gset = !gset;
      }
      if (key == 'b') {
        bset = !bset;
      }
      if (key == 'y') {
        yset = !yset;
      }
      /* if the bool is true, turn on LED, if false, turn off */
      if (rset) {
        GPIO_SET(io->gpio, 22);
      } else {
        GPIO_CLR(io->gpio, 22);
      }
      if (gset) {
        GPIO_SET(io->gpio, 23);
      } else {
        GPIO_CLR(io->gpio, 23);
      }  
      if (bset) {
        GPIO_SET(io->gpio, 05);
      } else {
        GPIO_CLR(io->gpio, 05);
      }  
      if (yset) {
        GPIO_SET(io->gpio, 06);
      } else {
        GPIO_CLR(io->gpio, 06);
      }    
    }

  }
  else
  {
    ; /* warning message already issued */
  }

  printf("\n main function done\n");   // this line never executed - ctl c

  return 0;
}
