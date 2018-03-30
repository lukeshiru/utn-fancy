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

#define FANCY_PADDING 1               // Padding for containers
#define FANCY_LIST_CHAR "> "          // Menu/List item character
#define FANCY_PASSWORD_MAX_LENGTH 8   // Max length for passwords
#define FANCY_PASSWORD_CHARACTER '*'  // Password character
#define FANCY_INPUT_INT_SUFFIX "+|-"  //
#define FancyContainer WINDOW*        // Fancier name for ncurses WINDOW

/* Utils **********************************************************************/

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
void fancyCursor(const bool visible);

/**
 * @brief Enables or disables input echo.
 *
 * @param shouldEcho Should echo?
 */
int fancyEcho(const bool shouldEcho);

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
 * @return string Scanned value.
 */
FancyContainer fancyScanString(FancyContainer container, char** value);

/**
 * @brief Scan given value from FancyContainer.
 *
 * @param container FancyContainer to scan from.
 * @return string Scanned value.
 */
FancyContainer fancyScan(FancyContainer container, char* value);

/**
 * @brief As fancyScan, but only scans ints (up and down for increment and decrement).
 *
 * @param container FancyContainer to scan from.
 * @param number Value where the scan will be stored.
 * @return FancyContainer Scanned FancyContainer.
 */
FancyContainer fancyScanInt(FancyContainer container, int* number);

/**
 * @brief As fancyScan, but for passwords.
 *
 * @param container FancyContainer to scan from.
 * @param password Value where the scan will be stored.
 * @return FancyContainer Scanned FancyContainer.
 */
FancyContainer fancyScanPassword(FancyContainer container, char** password);

/* Print **********************************************************************/

/**
 * @brief Print given value to given FancyContainer.
 *
 * @param container FancyContainer to be printed on.
 * @param format Format of the string to be printed.
 * @param ... Values to be printed.
 * @return FancyContainer Updated FancyContainer.
 */
FancyContainer fancyPrint(FancyContainer container, char* format, ...);

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
FancyContainer fancyPrintXY(FancyContainer container, const int x, const int y, char* format, ...);

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
FancyContainer fancyContainerPadding(FancyContainer parent, const int x, const int y, const int width, const int height, const int padding);

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
 * @brief Input (using FancyContainerTitle and fancyScan).
 *
 * @param parent Parent of the FancyContainer Input
 * @param label Label of the input
 * @param string String to store the scanned value.
 * @return FancyContainer FancyContainer Input.
 */
FancyContainer fancyInput(FancyContainer parent, const char* label, char** value);

/**
 * @brief Link Input, but just for ints (uses fancyScanInt).
 *
 * @param parent Parent of the FancyContainer Input
 * @param label Label of the input
 * @param number Value to store the scanned value.
 * @return FancyContainer FancyContainer Input.
 */
FancyContainer fancyInputInt(FancyContainer parent, const char* label, int* number);

/**
 * @brief Link Input, but just for passwords (uses fancyScanPassword).
 *
 * @param parent Parent of the FancyContainer Input
 * @param label Label of the input
 * @param password Value to store the scanned value.
 * @return FancyContainer FancyContainer Input.
 */
FancyContainer fancyInputPassword(FancyContainer parent, const char* label, char** password);

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
