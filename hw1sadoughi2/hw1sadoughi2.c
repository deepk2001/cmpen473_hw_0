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
    
    io->gpio->GPFSEL0.field.FSEL5 = GPFSEL_OUTPUT;   //red
    io->gpio->GPFSEL0.field.FSEL6 = GPFSEL_OUTPUT;   //green
    io->gpio->GPFSEL2.field.FSEL2 = GPFSEL_OUTPUT;   //blue
    io->gpio->GPFSEL2.field.FSEL3 = GPFSEL_OUTPUT;   //orange
    
   
    /* set initial output state - ON */
    GPIO_SET(io->gpio, 5);
    GPIO_SET(io->gpio, 6);
	GPIO_SET(io->gpio, 22);
	GPIO_SET(io->gpio, 23);
    
    printf("\n Press 'r' to toggle the Red   LED\n");
    printf(  " Press 'g' to toggle the Green LED\n");
    printf(  " Press 'b' to toggle the Blue LED\n");
    printf(  " Press 'o' to toggle the Orange LED\n");
    printf(  " Be sure to hit <Enter> key\n");
    printf(  " Press any other key will exit\n");
    
    do
    {
      switch (get_pressed_key())
      {
        case 'r':
          if (GPIO_READ(io->gpio, 5) == 0)
          {
            GPIO_SET(io->gpio, 5);
          }
          else
          {
            GPIO_CLR(io->gpio, 5);
          }
          break;

        case 'g':
          if (GPIO_READ(io->gpio, 6) == 0)
          {
            GPIO_SET(io->gpio, 6);
          }
          else
          {
            GPIO_CLR(io->gpio, 6);
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
    io->gpio->GPFSEL1.field.FSEL2 = GPFSEL_INPUT;
    io->gpio->GPFSEL1.field.FSEL3 = GPFSEL_INPUT;

    printf("\n Key hit is not 'r', 'g', 'b', or 'o' key, quiting loop\n");
    
  }
  else
  {
    ; /* warning message already issued */
  }

  printf("\n Main program done\n \n"); 

  return 0;
}
