﻿# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.1.1\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.1.1\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\12893\Desktop\CG resources\AppliedMathLearning\pbrt\exercises"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\12893\Desktop\CG resources\AppliedMathLearning\pbrt\exercises\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles\exercises.dir\depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles\exercises.dir\compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles\exercises.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\exercises.dir\flags.make

CMakeFiles\exercises.dir\main.cpp.obj: CMakeFiles\exercises.dir\flags.make
CMakeFiles\exercises.dir\main.cpp.obj: "C:\Users\12893\Desktop\CG resources\AppliedMathLearning\pbrt\exercises\main.cpp"
CMakeFiles\exercises.dir\main.cpp.obj: CMakeFiles\exercises.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\12893\Desktop\CG resources\AppliedMathLearning\pbrt\exercises\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/exercises.dir/main.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\exercises.dir\main.cpp.obj.d --working-dir="C:\Users\12893\Desktop\CG resources\AppliedMathLearning\pbrt\exercises\cmake-build-debug" --filter-prefix="Note: including file: " -- C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1434~1.319\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\exercises.dir\main.cpp.obj /FdCMakeFiles\exercises.dir\ /FS -c "C:\Users\12893\Desktop\CG resources\AppliedMathLearning\pbrt\exercises\main.cpp"
<<

CMakeFiles\exercises.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exercises.dir/main.cpp.i"
	C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1434~1.319\bin\Hostx64\x64\cl.exe > CMakeFiles\exercises.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\12893\Desktop\CG resources\AppliedMathLearning\pbrt\exercises\main.cpp"
<<

CMakeFiles\exercises.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exercises.dir/main.cpp.s"
	C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1434~1.319\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\exercises.dir\main.cpp.s /c "C:\Users\12893\Desktop\CG resources\AppliedMathLearning\pbrt\exercises\main.cpp"
<<

# Object files for target exercises
exercises_OBJECTS = \
"CMakeFiles\exercises.dir\main.cpp.obj"

# External object files for target exercises
exercises_EXTERNAL_OBJECTS =

exercises.exe: CMakeFiles\exercises.dir\main.cpp.obj
exercises.exe: CMakeFiles\exercises.dir\build.make
exercises.exe: CMakeFiles\exercises.dir\objects1
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\12893\Desktop\CG resources\AppliedMathLearning\pbrt\exercises\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable exercises.exe"
	"C:\Program Files\JetBrains\CLion 2023.1.1\bin\cmake\win\x64\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\exercises.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100220~1.0\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100220~1.0\x64\mt.exe --manifests -- C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1434~1.319\bin\Hostx64\x64\link.exe /nologo @CMakeFiles\exercises.dir\objects1 @<<
 /out:exercises.exe /implib:exercises.lib /pdb:"C:\Users\12893\Desktop\CG resources\AppliedMathLearning\pbrt\exercises\cmake-build-debug\exercises.pdb" /version:0.0 /machine:x64 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<
	echo >nul && "C:\Program Files\PowerShell\7\pwsh.exe" -noprofile -executionpolicy Bypass -file "C:/Users/12893/Desktop/CG resources/AppliedMathLearning/pbrt/exercises/vcpkg/scripts/buildsystems/msbuild/applocal.ps1" -targetBinary "C:/Users/12893/Desktop/CG resources/AppliedMathLearning/pbrt/exercises/cmake-build-debug/exercises.exe" -installedDir "C:/Users/12893/Desktop/CG resources/AppliedMathLearning/pbrt/exercises/cmake-build-debug/vcpkg_installed/x64-windows/debug/bin" -OutVariable out

# Rule to build all files generated by this target.
CMakeFiles\exercises.dir\build: exercises.exe
.PHONY : CMakeFiles\exercises.dir\build

CMakeFiles\exercises.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\exercises.dir\cmake_clean.cmake
.PHONY : CMakeFiles\exercises.dir\clean

CMakeFiles\exercises.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Users\12893\Desktop\CG resources\AppliedMathLearning\pbrt\exercises" "C:\Users\12893\Desktop\CG resources\AppliedMathLearning\pbrt\exercises" "C:\Users\12893\Desktop\CG resources\AppliedMathLearning\pbrt\exercises\cmake-build-debug" "C:\Users\12893\Desktop\CG resources\AppliedMathLearning\pbrt\exercises\cmake-build-debug" "C:\Users\12893\Desktop\CG resources\AppliedMathLearning\pbrt\exercises\cmake-build-debug\CMakeFiles\exercises.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\exercises.dir\depend

