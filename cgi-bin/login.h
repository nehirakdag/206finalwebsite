#ifndef _INCLUDE_HEADER_H_
#define _INCLUDE_HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BOOLEAN int
#define TRUE 1
#define FALSE 0

typedef struct user{
	char* username;
	char* password;
} user;

// Declare public functions of.c to prevent "Warning: implicit declaration of function"

#endif //_INCLUDE_HEADER_H_
