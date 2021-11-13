For our program to be according to the project specifications, a certain saveFile.txt must be in the same directory/folder of the .exe file created by the compiler. The saveFile.txt is already
in the same folder as the .cpp and .h files so you should not run into any problems. If for some reason, the file becomes corrupt or it's deleted, we created an initial_setup.cpp that after it's
compiled, it will be able to create an initial saveFile.txt file as stated by the project specifications. To facilitate the creation of the .exe files we created a makefile with the commands
'setup' and 'compile' that compiles and runs with the intial_setup.cpp and the main.cpp of the actual project, respectively, with the command make (or mingw32-make if the bin folder of mingw has
been added correctly to the Path).
We coded the program in Visual Studio Code, so we recommend that you run in Visual Studio Code and compile with g++ (mingw). If the program is to be compiled in CLion, you must create
a new project, copy the .cpp and .h files, change the CMake file, and copy the saveFile.txt to the debug folder, where the .exe will be located.
NOTE: the initial_setup.exe deletes the previous saveFile.txt if it already exists.