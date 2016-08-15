#Sudoku
#Description

The Application uses Qt for creating and managing the GUI.
The Application solves the Sudoku puzzle by using a recursive algotithm.

#How to Build
##Windows
This was developed using MinGW compiler in QtCreator. I would reccommend
using the QtCreator IDE and using the opening the sudoku solver project
file. Then using the the native build command in Qt Creator for a
dynamic build.

To build a static version add the "-config static" flag to the arguments 
in qmake. Also make a custom process that calls windeployqt.exe and
specifies the build directory as an arguement.
##MAC
*Not attempted yet*
##Linux
*Not attempted yet*

#Personal Significance

In my sophmore year of college I had a project that led me to fall in
love with computer science. Unsurprisingly it was writing a recursive
Sudoku solving algorithm in Java.

#Future Devolopments

-Enhance Sudoku generation algorithm
-Add new skins
-rename classes to better correspond to new added functionality
