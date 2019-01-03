/* Template function for getnum.h
 * Authors: Lukas Griffin and Thomas Nemeh. 10/18/2018. */

#ifndef BITS_H
#define BITS_H

//function declarations
void skipWhiteSpace();
void nextWord();
void checkNegative();
long readDecimal();
long readBinary();
long readHexadecimal();
long readOctal();
long checkTypeAndGetNum();
long getNum();
void tooctal(long num);
void tohex(long num);
long getnum();

#endif
