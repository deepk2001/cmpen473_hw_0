/**************************************************
* File:  hw1stump2.c 
* Homework 1 Program 2
* By Carson Stump
* CMPEN 473, Spring 2025, Penn State University
*
* 
* This program allows you to toggle the LEDs on the GPIO pins 5, 6, 22, and 23
* using the 'r', 'g', 'b' and 'o' keys respectively in the terminal
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

//translation for reading a pin
enum STATE digitalRead(int pin) {
  struct io_peripherals *io;//set up io pins
  io = import_registers();
  if (GPIO_READ(io->gpio, pin) == 0) { //if pin is LOW
    return LOW;
  }
  else { //else pin is HIGH
    return HIGH;
  }
}

//toggles a pin
void toggle(int pin) {
  
  if (digitalRead(pin) == LOW) { //if the pin is LOW
    digitalWrite(pin, HIGH); //write it HIGH
  }
  else { //else the pin is HIGH
    digitalWrite(pin, LOW); //so write it low
  }
  
}


//doesnt require hitting enter
char get_pressed_key(void) {
  
  struct termios oldt, newt;
  char ch;
  tcgetattr(STDIN_FILENO, &oldt); //save terminal state
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO); //disable buffering and echo
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  read(STDIN_FILENO, &ch, 1); //read a char
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt); //restore terminal
  return ch; //return character
  
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
    
    //set pin types
    io->gpio->GPFSEL0.field.FSEL5 = GPFSEL_OUTPUT;   //GPIO 05
    io->gpio->GPFSEL0.field.FSEL6 = GPFSEL_OUTPUT;   //GPIO 06
    io->gpio->GPFSEL2.field.FSEL2 = GPFSEL_OUTPUT;   //GPIO 22
    io->gpio->GPFSEL2.field.FSEL3 = GPFSEL_OUTPUT;   //GPIO 23
    
    
    
    //set initial state to off
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
    
    printf("\n Press 'r' to toggle the Red    LED\n");
    printf(  " Press 'g' to toggle the Green  LED\n");
    printf(  " Press 'b' to toggle the Blue   LED\n");
    printf(  " Press 'o' to toggle the Orange LED\n");
    //printf(  " Be sure to hit <Enter> key\n");
    printf(  " Press any other key will exit\n");
    
    do
    {
      switch (get_pressed_key())
      {
        case 'r': //if r is pressed
          toggle(5); //toggle 5 pin
          break;
        case 'g': //if g is pressed
          toggle(6); //toggle 6 pin
          break;
        case 'b': //if b is pressed
          toggle(22); //toggle 22 pin
          break;
        case 'o': //if g is pressed
          toggle(23); //toggle 23 pin
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
    
    //turn off all LEDs
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);

    printf("\n Key hit is not 'r', 'g', 'b', or 'o' key, quiting loop\n");
    
  }
  else
  {
    ; /* warning message already issued */
  }

  printf("\n Main program done\n \n"); 

  return 0;
}
