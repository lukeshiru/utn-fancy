#include "Fancy.h"

void fancyInput(const char* label, const char* type, void* variable) {
	printf("%s%s", label, FANCY_LABEL_SUFFIX);
	scanf(type, &variable);
}
