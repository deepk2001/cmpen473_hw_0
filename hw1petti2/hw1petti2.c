/**************************************************
 * File:  hw1petti2.c
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

void toggle_led(struct io_peripherals* registerSet, int gpioPin) {
    int pinLevel = GPIO_READ(registerSet->gpio, gpioPin);

    if (pinLevel > 0) {
        GPIO_CLR(registerSet->gpio, gpioPin);
        return;
    }

    GPIO_SET(registerSet->gpio, gpioPin);
}

int determine_gpio(char c) {
    switch (c) {
        case 'r':
            return 5;
        case 'g':
            return 6;
        case 'b':
            return 22;
        case 'o':
            return 23;
        default:
            exit(0);
    }
}

void init_gpio(struct io_peripherals* io) {
    io->gpio->GPFSEL2.field.FSEL2 = GPFSEL_OUTPUT;
    io->gpio->GPFSEL2.field.FSEL3 = GPFSEL_OUTPUT;
    io->gpio->GPFSEL0.field.FSEL5 = GPFSEL_OUTPUT;
    io->gpio->GPFSEL0.field.FSEL6 = GPFSEL_OUTPUT;
}

void init_terminal() {
    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

int main(void) {
    struct io_peripherals* io = import_registers();

    if (io == NULL)
        return 1;

    // Set pins 5, 6, 22, 23 Output
    init_gpio(io);

    // Disable enter requirement to capture char
    init_terminal();

    printf("Toggle the LEDs with the following keys\n");
    printf("\tr:\tRed LED\n");
    printf("\tg:\tGreen LED\n");
    printf("\tb:\tBlue LED\n");
    printf("\to:\tOrange LED\n");
    printf("\nExit with any other key or CTRL+C\n");
    printf("======================================================\n");

    while (1) {
        char ledColor = getchar();
        int gpioPin = determine_gpio(ledColor);
        toggle_led(io, gpioPin);
    }

    return 0;
}
