#include "Fancy.h"

/* Utils **********************************************************************/

FancyContainer fancyUpdate(FancyContainer container) {
	wrefresh(container);

	return container;
}

void fancyCursor(const bool visible) {
	curs_set(visible ? 1 : 0);
}

int fancyEcho(const bool shouldEcho) {
	return shouldEcho ? echo() : noecho();
}

FancyContainer fancyInit() {
	FancyContainer ui = initscr();
	cbreak();            // App can be break with Ctrl+C / Cmd+C
	fancyCursor(false);  // Cursor is hidden (will be visible in key input)
	fancyEcho(false);    // Disable echo by default (Turned on on inputs)
	return fancyUpdate(ui);
}

int fancyEnd() {
	getch();
	fancyCursor(true);

	return endwin();
}

int fancyXGet(FancyContainer container) {
	return getcurx(container);
}

int fancyYGet(FancyContainer container) {
	return getcury(container);
}

int fancyXMax(FancyContainer container) {
	return getmaxx(container);
}

int fancyYMax(FancyContainer container) {
	return getmaxy(container);
}

FancyContainer fancyXSet(FancyContainer container, const int x) {
	wmove(container, fancyYGet(container), x < 0 ? fancyXMax(container) + x : x);

	return fancyUpdate(container);
}

FancyContainer fancyYSet(FancyContainer container, const int y) {
	wmove(container, y < 0 ? fancyYMax(container) + y : y, fancyXGet(container));

	return fancyUpdate(container);
}

FancyContainer fancyXYSet(FancyContainer container, const int x, const int y) {
	wmove(container, y < 0 ? fancyYMax(container) + y : y, x < 0 ? fancyXMax(container) + x : x);

	return fancyUpdate(container);
}

int fancyXMin(FancyContainer container) {
	int x = fancyXGet(container);
	int minX = fancyXGet(fancyXSet(container, 0));
	fancyXSet(container, x);

	return minX;
}

int fancyYMin(FancyContainer container) {
	int y = fancyYGet(container);
	int minY = fancyYGet(fancyYSet(container, 0));
	fancyYSet(container, y);

	return minY;
}

int fancyWidth(FancyContainer container) {
	return fancyXMax(container) - fancyXMin(container);
}

int fancyHeight(FancyContainer container) {
	return fancyYMax(container) - fancyYMin(container);
}

int fancyRelativeCenter(const int container, const int child) {
	const int relativeCenter = (container - child) / 2;
	return relativeCenter < 0 ? 0 : relativeCenter;
}

void fancyConcatChar(char** value, const char character) {
	const int length = sizeof(value) / sizeof(value[0]);
	char* concat = malloc(length + 1);
	strcpy(concat, *value);
	concat[length] = character;
	concat[length + 1] = '\0';
	*value = concat;
}

int fancyAdd(int value1, int value2) {
	return (value1 > 0 && value2 > INT_MAX - value1)
		? INT_MAX
		: (value1 < 0 && value2 < INT_MIN - value1)
			? INT_MIN
			: value1 + value2;
}

int fancyMultiply(int value1, int value2) {
	const int product = value1 * value2;

	return (product < value1 || product < value2) ? INT_MAX : product;
}

FancyContainer fancyBorderAdd(FancyContainer container) {
	box(container, 0, 0);

	return fancyUpdate(container);
}

/* Scan ***********************************************************************/

FancyContainer fancyScanString(FancyContainer container, char** value) {
	const int bufferSize = fancyWidth(container);

	char* buffer = malloc(bufferSize);

	fancyCursor(true);
	fancyEcho(true);
	wgetnstr(container, buffer, bufferSize);
	fancyCursor(false);
	fancyEcho(false);

	*value = buffer;

	return fancyUpdate(container);
}

FancyContainer fancyScanInt(FancyContainer container, int* number) {
	const int x = fancyXGet(container);
	const int y = fancyYGet(container);

	bool running = true;
	int currentValue = 0;

	fancyCursor(true);
	fancyPrintXY(container, x, y, "%d", currentValue);

	while (running) {
		int key = wgetch(container);
		int keyValue = key - 48;
		switch (keyValue) {
			/* 0-9 */ case 0 ... 9:
				currentValue = (currentValue == 0)
					? keyValue
					: fancyAdd(fancyMultiply(currentValue, 10), keyValue);
				break;
			/* Backspace */ case 79:
				currentValue = currentValue / 10;
				break;
			/* Arrow Up */ case 17:
				currentValue = (currentValue == INT_MAX) ? INT_MAX : currentValue + 1;
				break;
			/* Arrow Down */ case 18:
				currentValue = (currentValue == INT_MIN) ? INT_MIN : currentValue - 1;
				break;
			/* Minus symbol */ case -3:
				currentValue *= -1;
				break;
		}

		fancyPrintXY(container, x, y, "%d \b", currentValue);

		running = (key != 10);
	}

	fancyPrintXY(container, x, y, "%d\n", currentValue);
	fancyCursor(false);

	*number = currentValue;

	return fancyUpdate(container);
}

FancyContainer fancyScanPassword(FancyContainer container, char** value) {
	const int bufferSize = fancyWidth(container);

	char* buffer = malloc(bufferSize);

	fancyCursor(true);
	wgetnstr(container, buffer, bufferSize);
	fancyCursor(false);

	*value = buffer;

	return fancyUpdate(container);
}

/* Print **********************************************************************/

FancyContainer fancyPrint(FancyContainer container, char* format, ...) {
	va_list args;
	va_start(args, format);
	vwprintw(container, format, args);
	va_end(args);

	return fancyUpdate(container);
}

FancyContainer fancyPrintXY(FancyContainer container, const int x, const int y, char* format, ...) {
	va_list args;
	va_start(args, format);
	vwprintw(fancyXYSet(container, x, y), format, args);
	va_end(args);

	return fancyUpdate(container);
}

/* Containers *****************************************************************/

FancyContainer fancyContainer(FancyContainer parent, const int x, const int y, const int width, const int height) {
	const int parentWidth = fancyWidth(parent);
	const int parentHeight = fancyHeight(parent);
	const int fixedWidth = x + width > parentWidth ? (parentWidth - x - FANCY_PADDING) : width;
	const int fixedHeight = y + height > parentHeight ? (parentHeight - y - FANCY_PADDING) : height;
	FancyContainer container = derwin(parent, fixedHeight, fixedWidth, y, x);
	wclear(container);

	return fancyUpdate(container);
}

FancyContainer fancyContainerPadding(FancyContainer parent,
                                     const int x,
                                     const int y,
                                     const int width,
                                     const int height,
                                     const int padding) {
	return fancyContainer(parent, x + padding, y + padding, width - (padding * 2), height - (padding * 2));
}

FancyContainer fancyContainerBorder(FancyContainer parent, const int x, const int y, const int width, const int height) {
	FancyContainer border = fancyBorderAdd(fancyContainer(parent, x, y, width, height));
	FancyContainer container = fancyContainerPadding(border, 0, 0, width, height, FANCY_PADDING);

	return fancyUpdate(container);
}

FancyContainer fancyContainerTitle(FancyContainer parent, const int x, const int y, const int width, const int height, const char* title) {
	FancyContainer border = fancyBorderAdd(fancyContainer(parent, x, y, width, height));
	FancyContainer container = fancyContainerPadding(border, 0, 0, width, height, FANCY_PADDING);
	fancyPrintXY(border, 1, 0, "%s", title);

	return fancyUpdate(container);
}

FancyContainer fancyContainerBorderCentred(FancyContainer parent, const int width, const int height) {
	const int x = fancyRelativeCenter(fancyWidth(parent), width);
	const int y = fancyRelativeCenter(fancyHeight(parent), height);

	return fancyContainerBorder(parent, x, y, width, height);
}

FancyContainer fancyContainerTitleCentred(FancyContainer parent, const int width, const int height, const char* title) {
	const int x = fancyRelativeCenter(fancyWidth(parent), width);
	const int y = fancyRelativeCenter(fancyHeight(parent), height);

	return fancyContainerTitle(parent, x, y, width, height, title);
}

/* Inputs *********************************************************************/

FancyContainer fancyInput(FancyContainer parent, const char* label, char** value) {
	const int x = fancyXGet(parent);
	const int y = fancyYGet(parent);
	const int width = fancyXMax(parent) - x;
	const int height = FANCY_PADDING * 2 + 1;

	FancyContainer inputArea = fancyContainerTitle(parent, x, y, fancyXMax(parent) - x, height, label);

	fancyScanString(inputArea, value);
	fancyXYSet(parent, 0, fancyYGet(parent) + height);

	return fancyUpdate(inputArea);
}

FancyContainer fancyInputInt(FancyContainer parent, const char* label, int* number) {
	const int x = fancyXGet(parent);
	const int y = fancyYGet(parent);
	const int width = fancyXMax(parent) - x;
	const int height = FANCY_PADDING * 2 + 1;
	const int suffixSize = sizeof(FANCY_INPUT_INT_SUFFIX);

	FancyContainer inputArea = fancyContainerTitle(parent, x, y, fancyXMax(parent) - x, height, label);

	fancyPrintXY(inputArea, -(suffixSize), 0, FANCY_INPUT_INT_SUFFIX);
	fancyXSet(inputArea, 0);
	fancyScanInt(inputArea, number);

	return fancyXYSet(parent, 0, fancyYGet(parent) + height);
}

FancyContainer fancyInputPassword(FancyContainer parent, const char* label, char** password) {
	const int x = fancyXGet(parent);
	const int y = fancyYGet(parent);
	const int width = fancyXMax(parent) - x;
	const int height = FANCY_PADDING * 2 + 1;

	FancyContainer inputArea = fancyContainerTitle(parent, x, y, fancyXMax(parent) - x, height, label);

	fancyScanPassword(inputArea, password);
	fancyXYSet(parent, 0, fancyYGet(parent) + height);

	return inputArea;
}

int fancyInputMenu(FancyContainer parent, const char* choices[], int choicesLength) {
	const int x = fancyXGet(parent);
	const int y = fancyYGet(parent);

	bool running = true;
	int choice = 0;

	keypad(parent, true);

	while (running) {
		int index = 0;
		int key = 0;
		while (index < choicesLength) {
			const int effect = index == choice ? A_REVERSE : A_NORMAL;
			wattron(parent, effect);
			fancyPrintXY(parent, x, y + index, "%s%s ", FANCY_LIST_CHAR, choices[index]);
			wattroff(parent, effect);
			index += 1;
		}

		key = wgetch(parent);
		choice = (key == KEY_UP) ? (choice - 1 < 0 ? choicesLength : choice) - 1
		                         : (key == KEY_DOWN) ? choice + 1 >= choicesLength ? 0 : choice + 1 : choice;
		running = (key != 10);
	}

	fancyUpdate(fancyXYSet(parent, x, y + choicesLength));

	return choice;
}
