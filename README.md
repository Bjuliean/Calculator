## SmartCalc_V2.0
### Made by Julieanb

- This is the second version of the educational project "SmartCalc". Written in C++ using MVC in QT.

- The calculator is able to process expressions of any complexity.

- The expression can be entered directly into the line, or using the buttons.

- The length of the entered expression is limited to 255 characters.

- To install the application, you need to complete the Makefile install goal. 
Afterwards, the executable will be in src/build. You need QT Framework to work correctly.

## Makefile targets

- all: Collects model tests and checks coverage.

- test: Gathers only model tests using gtest.

- gcov_report: Collects model coverage tests. You need gcov/lcov to work.

- install: Installs the application and generates an executable file in the build folder.

- dvi: Generates project technical documentation using doxygen. 
The documentation is initially in the repository, 
you can view it by opening src/documentation/html/index.html, 
or by executing the open makefile target.

- dist: Executes the Makefile install target, then archives the executable.

- clean: Removes files generated after the test and gcov_report targets.

- cleanall: Clears all generated files, bringing the repository to its original state.

## Examples

### --I--
![img1](misc/images/screen2.png)

![img1](misc/images/screen3.png)

After the expression is calculated, 
the expression itself flies into the Last expression block. 
When you click on the button, 
you will return the previously entered expression to the input line.

### --II--
![img1](misc/images/screen4.png)

You can draw a graph. For this, the expression you entered must contain 'x'. 
Then, you need to press either '=' or 'graph'.

### --III--
![img1](misc/images/screen5.png)

![img1](misc/images/screen6.png)

You can evaluate an expression with 'x' by substituting some specific value into it using the 'put x val' block. 
In this case, when you click on '=', a graph will appear, 
and in the input line the answer to the entered expression, 
in which yours value is substituted instead of 'x'.

### --IV--
![img1](misc/images/screen7.png)

![img1](misc/images/screen8.png)

![img1](misc/images/screen9.png)

To draw a graph, you can use the 'Adaptive graph' checkbox. 
In this case, the calculator will automatically select the y range. 
When you click on the 'Dot drawing' checkbox, the calculator will draw the graph with dots.