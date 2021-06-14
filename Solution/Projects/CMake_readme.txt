Project Details:
--C++17
--CMake version 3.8 or higher
--Generator "Visual Studio 16 2019" (Can be changed)


Create Executable:
1. Open CMake gui
2. select the source project path and where the build should be saved in the respective paths
3. Configure and Generate and the build folder (selected in step 2) should contain the .sln file (name of the .sln file is same as the project's folder name)
4. Open the .sln, right click on the project (name same as the folder name) and choose "Set as Startup Project". Also, confirm that the C++ language standard is set to C++17.
5. Run the debugger once for this project (F5 in visual studio).
6. Now the executable will be created in build folder->{Project Name}->Debug->{Project Name}.executable
7. You can now run this executable from commandline and pass additional arguments if the project needs.


Note: Executables for both the projects are also provided in the "Executables" folder.