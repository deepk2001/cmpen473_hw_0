/**************************************************
 * File:  hw1petti1.c
 * Homework 1
 * By David Petti
 * CMPEN 473, Spring 2026, Penn State University
 *
 * Raspberry Pi 4 Computer (RPi4) GPIO pin connections:
 *   Red    LED on GPIO 05
 *   Green  LED on GPIO 06
 *   Blue   LED on GPIO 22
 *   Orange LED on GPIO 23
 *
 ***************************************************/

#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "../include/FIFO.h"
#include "../include/MPU6050.h"
#include "../include/MPU9250.h"
#include "../include/bsc.h"
#include "../include/cm.h"
#include "../include/enable_pwm_clock.h"
#include "../include/gpio.h"
#include "../include/import_registers.h"
#include "../include/io_peripherals.h"
#include "../include/pwm.h"
#include "../include/spi.h"
#include "../include/uart.h"
#include "../include/wait_key.h"
#include "../include/wait_period.h"

int main(void) {
    struct io_peripherals* io = import_registers();

    if (io == NULL)
        return 1;

    // Set pins 5, 6, 22, 23 Output
    io->gpio->GPFSEL2.field.FSEL2 = GPFSEL_OUTPUT;
    io->gpio->GPFSEL2.field.FSEL3 = GPFSEL_OUTPUT;
    io->gpio->GPFSEL0.field.FSEL5 = GPFSEL_OUTPUT;
    io->gpio->GPFSEL0.field.FSEL6 = GPFSEL_OUTPUT;

    printf("\nHit 'CTRL+C' to quit\n");

    while (1) {
        GPIO_SET(io->gpio, 5);
        sleep(1);

        GPIO_CLR(io->gpio, 5);
        sleep(1);

        GPIO_SET(io->gpio, 6);
        sleep(1);

        GPIO_CLR(io->gpio, 6);
        sleep(1);

        GPIO_SET(io->gpio, 22);
        sleep(1);

        GPIO_CLR(io->gpio, 22);
        sleep(1);

        GPIO_SET(io->gpio, 23);
        sleep(1);

        GPIO_CLR(io->gpio, 23);
        sleep(1);
    }

    return 0;
}
