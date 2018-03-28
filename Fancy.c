#include "Fancy.h"

void fancyInput(const char* label, const char* type, void* variable) {
	printf("%s: ", label);
	scanf(type, &variable);
}
