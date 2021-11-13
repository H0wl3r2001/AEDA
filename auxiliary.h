#ifndef AUX_H
#define AUX_H

/** @file  auxiliary header file, to have input restrictive and consolidating functions*/
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

/**
 * @brief Get the integer input restricted to an inclusive interval.
 * @param lower lower limit of the interval.
 * @param upper upper limit of teh interval.
 * @return integer contained in [lower, upper].
 */
int getInt(int lower, int upper);

/**
 * @brief Get the float input restricted to an inclusive interval, by conversion of strings. Throws invalid argument exception if string does not convert successfully to a float.
 * @param lower lower limit of the interval.
 * @param upper upper limit of teh interval.
 * @return float contained in [lower, upper].
 */
float getFloat(int lower, int upper);

/**
 * @brief Get Yes(Y/y) or No(N/n) from the user.
 * @return true (Yes).
 * @return false (No).
 */
bool getYesNo();

/**
 * @brief Sets the Color from the font.
 * @param color an integer argument that codifies the color.
 */
void setColor(int color);

/**
 * @brief Sets the position of the cursor in the console.
 * @param x horizontal coordinate integer argument.
 * @param y vertical coordinate integer argument.
 */
void cursorPos(int x, int y);

#endif //AUX_H
