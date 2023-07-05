#include "calculator.h"
#include <iostream>
#include <string>
#include <FL/Fl.h>
#include <FL/Fl_Window.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>

#define WINDOW_WIDTH 425
#define WINDOW_HEIGHT 300
#define INPUT_HEIGHT 30
#define COLUMN_NUM 4
#define GAP 5

int inputWidth = WINDOW_WIDTH - 10;
int buttonWidth = ((inputWidth - (GAP * (COLUMN_NUM - 1))) / 4);

Fl_Float_Input* numField;
double num1 = 0;
double num2 = 0;
double res = 0;
const char* operation = "";

/*
 * Calculate the position of of an element in the window
 */
int calculateXPos (int xIndex) {
    return (buttonWidth * xIndex) + (GAP * (xIndex + 1));
}

/*
 * Calculate the position of of an element in the window
 */
int calculateYPos(int yIndex) {
    return (INPUT_HEIGHT * yIndex) + (GAP * (yIndex + 1));
}

/*
 * Adds a new button to the window
 * 
 * @params x - the position of the button in the x axis
 * @params y - the position of the button in the y axis
 */
Fl_Button* addNewButton(int x, int y, int width, int height, char* label) {
    int xPos = calculateXPos(x);
    int yPos = calculateYPos(y);

    Fl_Button* button = new Fl_Button(xPos, yPos, width, height, label);

    return button;
}

/*
 * Clears the number field 
 * 
 * This still keeps the previous calculation
 */
void clear(Fl_Widget* widget, void* data) {
    numField->value("");
}

/*
 * Resets the whole calculator. Thereby deleting the previous calculation
 */
void reset(Fl_Widget* widget, void* data) {
    clear(widget, data);

    operation = "";
    num1 = 0;
    num2 = 0;
}

/*
 * Stores the number on the field to num2
 * 
 * Always assume that this number is the second number in any operation
 */
void storeNumber(Fl_Widget* widget, void* data) {
    Fl_Button* numButton = (Fl_Button*)widget;

    numField->insert(numButton->label());

    num2 = atof(numField->value());
}

/*
 * Do the calculation and show the final result
 * 
 * Assume that the final result will be used in the next calculation
 * 
 * Reset the operation variable to avoid redoing this calculation
 */
void doOperation (Fl_Widget* widget, void* data) {
    if (operation == "+") {
        res = add(num1, num2);
    }
    else if (operation == "-") {
        res = subtract(num1, num2);
    }
    else if (operation == "*") {
        res = multiply(num1, num2);
    }
    else if (operation == "/") {
        res = divide(num1, num2);
    }
    else if (operation == "^") {
        res = power(num1, num2);
    }

    numField->value(std::to_string(res).c_str());

    // Assume that the final result will be used in the next calculation
    num2 = res;

    // Reset the operation variable to avoid redoing this calculation
    operation = "";
}

/*
 * Store a new operation while making sure that any previous operation has already been calculated to it's final result
 * 
 * Assumes that the current value of the numField is the first number in any operation
 * Wait for the second number for this operation
 */
void storeOperation(Fl_Widget* widget, void* data) {
    Fl_Button* operationButton = (Fl_Button*)widget;

    if (operation != "") {
        doOperation(widget, data);
    }

    operation = operationButton->label();

    // Assumes that the current value of the numField is the first number in any operation
    num1 = num2;

    // Wait for the second number for this operation
    clear(widget, data);
    num2 = 0;
}

/*
 * Adds a decimal point to the number
 */
void addDecimal(Fl_Widget* widget, void* data) {
    numField->insert(".");
}

int main () {
    Fl_Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Personal Finance");

    numField = new Fl_Float_Input(calculateXPos(0), calculateYPos(0), inputWidth, INPUT_HEIGHT, "");

    addNewButton(0, 1, buttonWidth, INPUT_HEIGHT, "C")->callback(reset);
    addNewButton(1, 1, buttonWidth, INPUT_HEIGHT, "CE")->callback(clear);
    addNewButton(2, 1, buttonWidth, INPUT_HEIGHT, "^")->callback(storeOperation);
    addNewButton(3, 1, buttonWidth, INPUT_HEIGHT, "+")->callback(storeOperation);

    addNewButton(0, 2, buttonWidth, INPUT_HEIGHT, "1")->callback(storeNumber);
    addNewButton(1, 2, buttonWidth, INPUT_HEIGHT, "2")->callback(storeNumber);
    addNewButton(2, 2, buttonWidth, INPUT_HEIGHT, "3")->callback(storeNumber);
    addNewButton(3, 2, buttonWidth, INPUT_HEIGHT, "-")->callback(storeOperation);

    addNewButton(0, 3, buttonWidth, INPUT_HEIGHT, "4")->callback(storeNumber);
    addNewButton(1, 3, buttonWidth, INPUT_HEIGHT, "5")->callback(storeNumber);
    addNewButton(2, 3, buttonWidth, INPUT_HEIGHT, "6")->callback(storeNumber);
    addNewButton(3, 3, buttonWidth, INPUT_HEIGHT, "*")->callback(storeOperation);

    addNewButton(0, 4, buttonWidth, INPUT_HEIGHT, "7")->callback(storeNumber);
    addNewButton(1, 4, buttonWidth, INPUT_HEIGHT, "8")->callback(storeNumber);
    addNewButton(2, 4, buttonWidth, INPUT_HEIGHT, "9")->callback(storeNumber);
    addNewButton(3, 4, buttonWidth, INPUT_HEIGHT, "/")->callback(storeOperation);

    addNewButton(0, 5, (buttonWidth * 2) + GAP, INPUT_HEIGHT, "0")->callback(storeNumber);
    addNewButton(2, 5, buttonWidth, INPUT_HEIGHT, ".")->callback(addDecimal);
    addNewButton(3, 5, buttonWidth, INPUT_HEIGHT, "=")->callback(doOperation);

    window.end();
    window.show();

    return Fl::run();
}