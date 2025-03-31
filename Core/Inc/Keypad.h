/*
 * Keypad.h
 *
 *  Created on: Oct 12, 2024
 *      Author: PC
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include "main.h"
#include <stdio.h>
#include <stdbool.h>

extern float temp_price;
extern int flag_total;
static float decimal_place = 1.0;
static int flag_decimal = 0;
static int flag_add = 0;

static float previous_result;
char read_keypad (void);

void get_keypad(float *result, float weight);

#endif /* INC_KEYPAD_H_ */
