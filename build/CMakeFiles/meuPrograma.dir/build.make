# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio\build

# Include any dependencies generated for this target.
include CMakeFiles/meuPrograma.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/meuPrograma.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/meuPrograma.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/meuPrograma.dir/flags.make

CMakeFiles/meuPrograma.dir/utils/functions/functions.c.obj: CMakeFiles/meuPrograma.dir/flags.make
CMakeFiles/meuPrograma.dir/utils/functions/functions.c.obj: C:/Users/sonal_rkyba0o/OneDrive/Documentos/GitHub/projeto_klaudio/utils/functions/functions.c
CMakeFiles/meuPrograma.dir/utils/functions/functions.c.obj: CMakeFiles/meuPrograma.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/meuPrograma.dir/utils/functions/functions.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/meuPrograma.dir/utils/functions/functions.c.obj -MF CMakeFiles\meuPrograma.dir\utils\functions\functions.c.obj.d -o CMakeFiles\meuPrograma.dir\utils\functions\functions.c.obj -c C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio\utils\functions\functions.c

CMakeFiles/meuPrograma.dir/utils/functions/functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/meuPrograma.dir/utils/functions/functions.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio\utils\functions\functions.c > CMakeFiles\meuPrograma.dir\utils\functions\functions.c.i

CMakeFiles/meuPrograma.dir/utils/functions/functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/meuPrograma.dir/utils/functions/functions.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio\utils\functions\functions.c -o CMakeFiles\meuPrograma.dir\utils\functions\functions.c.s

CMakeFiles/meuPrograma.dir/main.c.obj: CMakeFiles/meuPrograma.dir/flags.make
CMakeFiles/meuPrograma.dir/main.c.obj: C:/Users/sonal_rkyba0o/OneDrive/Documentos/GitHub/projeto_klaudio/main.c
CMakeFiles/meuPrograma.dir/main.c.obj: CMakeFiles/meuPrograma.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/meuPrograma.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/meuPrograma.dir/main.c.obj -MF CMakeFiles\meuPrograma.dir\main.c.obj.d -o CMakeFiles\meuPrograma.dir\main.c.obj -c C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio\main.c

CMakeFiles/meuPrograma.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/meuPrograma.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio\main.c > CMakeFiles\meuPrograma.dir\main.c.i

CMakeFiles/meuPrograma.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/meuPrograma.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio\main.c -o CMakeFiles\meuPrograma.dir\main.c.s

# Object files for target meuPrograma
meuPrograma_OBJECTS = \
"CMakeFiles/meuPrograma.dir/utils/functions/functions.c.obj" \
"CMakeFiles/meuPrograma.dir/main.c.obj"

# External object files for target meuPrograma
meuPrograma_EXTERNAL_OBJECTS =

meuPrograma.exe: CMakeFiles/meuPrograma.dir/utils/functions/functions.c.obj
meuPrograma.exe: CMakeFiles/meuPrograma.dir/main.c.obj
meuPrograma.exe: CMakeFiles/meuPrograma.dir/build.make
meuPrograma.exe: CMakeFiles/meuPrograma.dir/linkLibs.rsp
meuPrograma.exe: CMakeFiles/meuPrograma.dir/objects1.rsp
meuPrograma.exe: CMakeFiles/meuPrograma.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable meuPrograma.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\meuPrograma.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/meuPrograma.dir/build: meuPrograma.exe
.PHONY : CMakeFiles/meuPrograma.dir/build

CMakeFiles/meuPrograma.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\meuPrograma.dir\cmake_clean.cmake
.PHONY : CMakeFiles/meuPrograma.dir/clean

CMakeFiles/meuPrograma.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio\build C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio\build C:\Users\sonal_rkyba0o\OneDrive\Documentos\GitHub\projeto_klaudio\build\CMakeFiles\meuPrograma.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/meuPrograma.dir/depend
