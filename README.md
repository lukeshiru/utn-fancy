# UTN Fancy

[![[Build Status]](https://img.shields.io/travis/lukeshiru/utn-fancy.svg?style=flat-square)](https://travis-ci.org/lukeshiru/utn-fancy)

Functions to make fancy stuff.

## Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "Fancy/Fancy.h"

int main() {
  const char* choices[] = {"Option 1", "Option 2", "Option 3", FANCY_END};

  FancyContainer app = fancyInit();
  FancyContainer loginWindow = fancyContainerTitleCentred(app, 50, 8, "Login");
  char* username;
  char* password;
  int number;

  username = fancyInputString(loginWindow, "Username");
  password = fancyInputPassword(loginWindow, "Password");

  FancyContainer menuWindow = fancyContainerTitleCentred(app, 50, 20, "Options");
  fancyPrint(menuWindow, "Welcome, %s!\n", username);
  fancyPrint(menuWindow, "\nThe Selected option was: %s\n", choices[fancyInputMenu(menuWindow, choices)]);
  number = fancyInputInt(menuWindow, "Number");
  fancyPrint(menuWindow, "Number was: %d", number);

  return fancyEnd();
}
```

## Types

### FancyContainer

Alias for [ncurses](https://www.gnu.org/software/ncurses/) WINDOW pointer. Used to create new containers.

```c
FancyContainer ui = fancyInit();
FancyContainer containerExample = fancyContainer(ui, x, y, width, height);
```

## Functions

### Base

- `fancyInit()` - Initializes [ncurses](https://www.gnu.org/software/ncurses/) and returns a FancyContainer.
- `fancyEnd(wait)` - Closes [ncurses](https://www.gnu.org/software/ncurses/) and waits for user input (if true).

### Utils

- `fancyXGet(container)` - Get current X position for given FancyContainer.
- `fancyYGet(container)` - Get current Y position for given FancyContainer.
- `fancyXMax(container)` - Get max X position for given FancyContainer.
- `fancyYMax(container)` - Get max Y position for given FancyContainer.
- `fancyXSet(container, x)` - Set current X position for given FancyContainer.
- `fancyYSet(container, y)` - Set current Y position for given FancyContainer.
- `fancyXYSet(container, x, y)` - Set current X and Y position for given FancyContainer.
- `fancyXMin(container)` - Get min X position for given FancyContainer.
- `fancyYMin(container)` - Get min Y position for given FancyContainer.
- `fancyWidth(container)` - Get width of given FancyContainer.
- `fancyHeight(container)` - Get height of given FancyContainer.
- `fancyBorderAdd(container)` - Add border to given FancyContainer.
- `fancyClear(container)` - Clear given container.
- `fancyArrayLength(array[])` - Gets the length of an array with a FANCY_END marker.

### Scan

- `fancyScanString(container, echoVisible)` - Scan string from given FancyContainer and returns it.
- `fancyScanInt(container)` - Scan int from given FancyContainer and returns it.

### Print

- `fancyPrint(container, format, ...)` - Print in current position of given FancyContainer.
- `fancyPrintXY(container, x, y, format, ...)` - Print in given position (x, y) of given FancyContainer.

### Containers

- `fancyContainer(parent, x, y, width, height)` - Creates a new FancyContainer.
- `fancyPadding(parent, x, y, width, height, padding)` - Creates a new FancyContainer with given padding.
- `fancyContainerBorder(parent, x, y, width, height)` - Creates a new FancyContainer with border.
- `fancyContainerTitle(parent, x, y, width, height, title)` - Creates a new FancyContainer with border and title.
- `fancyContainerBorderCentred(parent, width, height)` - Creates a new FancyContainer with border and centred in parent.
- `fancyContainerTitleCentred(parent, width, height, title)` - Creates a new FancyContainer with border and title and centred in parent.

### Input

- `fancyInputString(parent, label)` - Creates a new FancyContainer for string input and returns scanned value.
- `fancyInputInt(parent, label)` - Creates a new FancyContainer for int input and returns scanned value.
- `fancyInputPassword(parent, label)` - Creates a new FancyContainer for string input with no output (for passwords) and returns scanned value.
- `fancyInputMenu(parent, choices[])` - Displays a menu with arrow selection and returns the selected index of the array of choices.
