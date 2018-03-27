#include "Fancy.h"

void fancyInput(const char* label, const char* type, ...) {
	va_list args;
	va_start(args, type);
	printf("%s: ", label);
	vscanf(type, args);
	va_end(args);
}
