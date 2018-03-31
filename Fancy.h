#include <limits.h>
#include <ncurses.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include guard
#ifndef FANCY_H
#define FANCY_H

/* Settings *******************************************************************/

#define FANCY_PADDING 1               // Padding for containers.
#define FANCY_LIST_CHAR "> "          // Menu/List item character.
#define FANCY_PASSWORD_MAX_LENGTH 8   // Max length for passwords.
#define FANCY_PASSWORD_CHARACTER '*'  // Password character.
#define FANCY_INPUT_INT_SUFFIX "+|-"  // Suffix for int imputs.
#define FANCY_INPUT_HEIGHT 1          // Height of inputs.
#define FANCY_STRING_LIMIT 256        // String upper limit
#define FancyContainer WINDOW*        // Fancier name for ncurses WINDOW.

/* Utils **********************************************************************/

/**
 * @brief Throws error and exits program.
 *
 * @param errorDescription Description of the error.
 * @return void*
 */
void* fancyError(char* errorDescription);

/**
 * @brief Re-render a FancyContainer.
 *
 * @param container The FancyContainer to be updated
 * @return FancyContainer Updated FancyContainer
 */
FancyContainer fancyUpdate(FancyContainer container);

/**
 * @brief Enables or disables the cursor.
 *
 * @param visible Should be visible?
 */
void* fancyCursorVisible(const bool visible);

/**
 * @brief Enables or disables input echo.
 *
 * @param visible Should echo?
 */
void* fancyEchoVisible(const bool visible);

/**
 * @brief Enables or disables C break (Ctrl. + C / Cmd. + C)
 *
 * @param enabled Should CBreak?
 */
void* fancyCBreak(const bool enabled);

/**
 * @brief Enables or disables scroll on given container.
 *
 * @param target Container target.
 * @param enabled Should scroll?
 */
void* fancyScroll(FancyContainer container, const bool enabled);

/**
 * @brief Initialize ncurses (with some default options).
 *
 * @return FancyContainer The terminal container.
 */
FancyContainer fancyInit();

/**
 * @brief Closes ncurses and waits for user input.
 *
 * @return int Status code.
 */
int fancyEnd();

/**
 * @brief Get current X position for given FancyContainer.
 *
 * @param container FancyContainer to be evaluated.
 * @return int Current X value.
 */
int fancyXGet(FancyContainer container);

/**
 * @brief Get current Y position for given FancyContainer.
 *
 * @param container FancyContainer to be evaluated.
 * @return int Current Y value.
 */
int fancyYGet(FancyContainer container);

/**
 * @brief Get max X for given FancyContainer.
 *
 * @param container FancyContainer to be evaluated.
 * @return int Max X value.
 */
int fancyXMax(FancyContainer container);

/**
 * @brief Get max Y for given FancyContainer.
 *
 * @param container FancyContainer to be evaluated.
 * @return int Max Y value.
 */
int fancyYMax(FancyContainer container);

/**
 * @brief Set current X position to given FancyContainer.
 *
 * @param container FancyContainer to updated.
 * @param x X Position to be set.
 * @return FancyContainer Updated FancyContainer.
 */
FancyContainer fancyXSet(FancyContainer container, const int x);

/**
 * @brief Set current Y position to given FancyContainer.
 *
 * @param container FancyContainer to updated.
 * @param y Y Position to be set.
 * @return FancyContainer Updated FancyContainer.
 */
FancyContainer fancyYSet(FancyContainer container, const int y);

/**
 * @brief Set current X and Y position to given FancyContainer.
 *
 * @param container FancyContainer to updated.
 * @param x X Position to be set.
 * @param y Y Position to be set.
 * @return FancyContainer Updated FancyContainer.
 */
FancyContainer fancyXYSet(FancyContainer container, const int x, const int y);

/**
 * @brief Get Minimal X value for given FancyContainer.
 *
 * @param container FancyContainer to be evaluated.
 * @return int Minimal X value.
 */
int fancyXMin(FancyContainer container);

/**
 * @brief Get Minimal Y value for given FancyContainer.
 *
 * @param container FancyContainer to be evaluated.
 * @return int Minimal Y value.
 */
int fancyYMin(FancyContainer container);

/**
 * @brief Get width of given FancyContainer.
 *
 * @param container FancyContainer to be evaluated.
 * @return int Width length.
 */
int fancyWidth(FancyContainer container);

/**
 * @brief Get height of given FancyContainer.
 *
 * @param container FancyContainer to be evaluated.
 * @return int Height length.
 */
int fancyHeight(FancyContainer container);

/**
 * @brief Difference between given values (for center calculation).
 *
 * @param container Container length (width or height).
 * @param child Child length (width or height).
 * @return int Difference value.
 */
int fancyRelativeCenter(const int container, const int child);

/**
 * @brief Attaches character to string.
 *
 * @param string String to be extended.
 * @param character Character to be added.
 */
// void fancyConcatChar(char** value, const char character);

/**
 * @brief Add border to given FancyContainer.
 *
 * @param container FancyContainer to add border to.
 * @return FancyContainer Updated FancyContainer.
 */
FancyContainer fancyBorderAdd(FancyContainer container);

/* Scan ***********************************************************************/

/**
 * @brief Scan given value from FancyContainer.
 *
 * @param container FancyContainer to scan from.
 * @param echoVisible Hide echo or don't.
 * @return char* Scanned value.
 */
char* fancyScanString(FancyContainer container, const bool echoVisible);

/**
 * @brief As fancyScan, but only scans ints (up and down for increment and decrement).
 *
 * @param container FancyContainer to scan from.
 * @return int Scanned value.
 */
int fancyScanInt(FancyContainer container);

/* Print **********************************************************************/

/**
 * @brief Print given value to given FancyContainer.
 *
 * @param container FancyContainer to be printed on.
 * @param format Format of the string to be printed.
 * @param ... Values to be printed.
 * @return FancyContainer Updated FancyContainer.
 */
FancyContainer fancyPrint(FancyContainer container, const char* format, ...);

/**
 * @brief Same as fancyPrint, but with positioning.
 *
 * @param container FancyContainer to be printed on.
 * @param x X Position.
 * @param y Y Position.
 * @param format Format of the string to be printed.
 * @param ... Values to be printed.
 * @return FancyContainer Updated FancyContainer.
 */
FancyContainer fancyPrintXY(FancyContainer container, const int x, const int y, const char* format, ...);

/* Containers *****************************************************************/

/**
 * @brief Creates a new FancyContainer.
 *
 * @param parent Parent of the FancyContainer.
 * @param x X position
 * @param y Y Position.
 * @param width Width (in cols).
 * @param height Height (in rows).
 * @return FancyContainer New FancyContainer.
 */
FancyContainer fancyContainer(FancyContainer parent, const int x, const int y, const int width, const int height);

/**
 * @brief Same as FancyContainer, but with a padding.
 *
 * @param parent Parent of the FancyContainer.
 * @param x X position
 * @param y Y Position.
 * @param width Width (in cols).
 * @param height Height (in rows).
 * @param padding Padding value.
 * @return FancyContainer New FancyContainer.
 */
FancyContainer fancyPadding(FancyContainer parent, const int x, const int y, const int width, const int height, const int padding);

/**
 * @brief Same as FancyContainer, but with a border (using fancyBorderAdd and fancyPadding).
 *
 * @param parent Parent of the FancyContainer.
 * @param x X position
 * @param y Y Position.
 * @param width Width (in cols).
 * @param height Height (in rows).
 * @return FancyContainer New FancyContainer.
 */
FancyContainer fancyContainerBorder(FancyContainer parent, const int x, const int y, const int width, const int height);

/**
 * @brief Same as FancyContainerBorder, but with a title (using fancyContainerBorder and fancyPrintXY).
 *
 * @param parent Parent of the FancyContainer.
 * @param x X position
 * @param y Y Position.
 * @param width Width (in cols).
 * @param height Height (in rows).
 * @param title Title of the FancyContainer.
 * @return FancyContainer New FancyContainer.
 */
FancyContainer fancyContainerTitle(FancyContainer parent, const int x, const int y, const int width, const int height, const char* title);

/**
 * @brief Same as FancyContainerBorder, but centred in parent (using fancyRelativeCenter).
 *
 * @param parent Parent of the FancyContainer.
 * @param width Width (in cols).
 * @param height Height (in rows).
 * @return FancyContainer New FancyContainer.
 */
FancyContainer fancyContainerBorderCentred(FancyContainer parent, const int width, const int height);

/**
 * @brief Same as FancyContainerTitle, but centred in parent (using fancyRelativeCenter).
 *
 * @param parent Parent of the FancyContainer.
 * @param width Width (in cols).
 * @param height Height (in rows).
 * @param title Title of the FancyContainer.
 * @return FancyContainer New FancyContainer.
 */
FancyContainer fancyContainerTitleCentred(FancyContainer parent, const int width, const int height, const char* title);

/* Inputs *********************************************************************/

/**
 * @brief Input base.
 *
 * @param parent Parent of the FancyContainer Input
 * @param label Label of the input
 * @return FancyContainer FancyContainer Input.
 */
FancyContainer fancyInput(FancyContainer parent, const char* label);

/**
 * @brief Input base with suffix.
 *
 * @param parent Parent of the FancyContainer Input.
 * @param label Label of the input.
 * @param suffix Suffix of the input.
 * @return FancyContainer FancyContainer Input.
 */
FancyContainer fancyInputSuffix(FancyContainer parent, const char* label, const char* suffix);

/**
 * @brief Input (using FancyContainerTitle and fancyScanString).
 *
 * @param parent Parent of the FancyContainer Input
 * @param label Label of the input
 * @return char* Input value.
 */
char* fancyInputString(FancyContainer parent, const char* label);

/**
 * @brief Link Input, but just for ints (uses fancyScanInt).
 *
 * @param parent Parent of the FancyContainer Input
 * @param label Label of the input
 * @return int Input value.
 */
int fancyInputInt(FancyContainer parent, const char* label);

/**
 * @brief Link Input, but just for passwords (uses fancyScanString with no echo).
 *
 * @param parent Parent of the FancyContainer Input
 * @param label Label of the input
 * @return char* Input value.
 */
char* fancyInputPassword(FancyContainer parent, const char* label);

/**
 * @brief Menu with keyboard control.
 *
 * @param parent Parent of the FancyContainer Menu.
 * @param choices Array of strings for the choices.
 * @param choicesLength Length of the menu.
 * @return int Index of the menu selected menu option.
 */
int fancyInputMenu(FancyContainer parent, const char* choices[], int choicesLength);

#endif  // FANCY_H
