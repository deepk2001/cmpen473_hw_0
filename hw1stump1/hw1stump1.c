/**************************************************
* File:  hw1name1.c
* Homework 1 program 1
* By Carson Stump
* CMPEN 473, Spring 2025, Penn State University
* 
* This program blinks the LEDS on GPIO pins 5, 6, 22, and 23 in ascending order,
* each for one second
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

enum STATE {
  LOW, //equals 0
  HIGH //equals 1
};

//im used to Arduinos, so this function just translates the Raspberry
//pi function to how its written in the arduino IDE
void digitalWrite(int pin, int state) { //function that neatly writes a value to a certain pin
  struct io_peripherals *io; //set up io pins
  io = import_registers();
  
  //state should only be 0 (for low) or 1 (for high)
  if (state == LOW) { //write low
    GPIO_CLR(io->gpio, pin);
  }
  if (state == HIGH) { //write high
    GPIO_SET(io->gpio, pin);
  }
}

int main( void )
{
  struct io_peripherals *io;

  io = import_registers();
  if (io != NULL)
  {
    /* print where the I/O memory was actually mapped to */
    printf( "mem at 0x%8.8X\n", (unsigned int)io );
    
    //set pin types
    io->gpio->GPFSEL0.field.FSEL5 = GPFSEL_OUTPUT;   //GPIO 5
    io->gpio->GPFSEL0.field.FSEL6 = GPFSEL_OUTPUT;   //GPIO 6
    io->gpio->GPFSEL2.field.FSEL2 = GPFSEL_OUTPUT;   //GPIO 22
    io->gpio->GPFSEL2.field.FSEL3 = GPFSEL_OUTPUT;   //GPIO 23
    
    printf("\n Hit 'ctl c' to quit \n");
    
    //turn all LEDs off
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
    
    while (1)   // Loop forever
    {
      //blink 5
      digitalWrite(5, HIGH); //turn LED on 
      sleep(1); //delay 1 second
      digitalWrite(5, LOW); //turn LED off
      
      //blink 6
      digitalWrite(6, HIGH); //turn LED on 
      sleep(1); //delay 1 second
      digitalWrite(6, LOW); //turn LED off
      
      //blink 22
      digitalWrite(22, HIGH); //turn LED on 
      sleep(1); //delay 1 second
      digitalWrite(22, LOW); //turn LED off
      
      //blink 23
      digitalWrite(23, HIGH); //turn LED on 
      sleep(1); //delay 1 second
      digitalWrite(23, LOW); //turn LED off
      
    }

  }
  else
  {
    ; /* warning message already issued */
  }

  printf("\n main function done\n");   // this line never executed - ctl c
  

  return 0;
}

