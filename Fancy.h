#include <stdio.h>
#include <stdlib.h>

// Include guard
#ifndef FANCY_H
#define FANCY_H

// Suffix for fancy labels
#define FANCY_LABEL_SUFFIX ": "

// Display the given label next to the input value
void fancyInput(const char* label, const char* type, void* variable);

#endif // FANCY_H
