# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hsa/Desktop/ImuTemplate

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hsa/Desktop/ImuTemplate/build

# Include any dependencies generated for this target.
include CMakeFiles/qcustomplot.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/qcustomplot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/qcustomplot.dir/flags.make

include/RazorImu/moc_FtdiPort.cxx: ../include/RazorImu/FtdiPort.h
include/RazorImu/moc_FtdiPort.cxx: include/RazorImu/moc_FtdiPort.cxx_parameters
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/hsa/Desktop/ImuTemplate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating include/RazorImu/moc_FtdiPort.cxx"
	cd /home/hsa/Desktop/ImuTemplate/build/include/RazorImu && /usr/lib/x86_64-linux-gnu/qt4/bin/moc @/home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_FtdiPort.cxx_parameters

include/RazorImu/moc_RazorImu.cxx: ../include/RazorImu/RazorImu.h
include/RazorImu/moc_RazorImu.cxx: include/RazorImu/moc_RazorImu.cxx_parameters
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/hsa/Desktop/ImuTemplate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating include/RazorImu/moc_RazorImu.cxx"
	cd /home/hsa/Desktop/ImuTemplate/build/include/RazorImu && /usr/lib/x86_64-linux-gnu/qt4/bin/moc @/home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_RazorImu.cxx_parameters

include/RazorImu/moc_ImuDataLogger.cxx: ../include/RazorImu/ImuDataLogger.h
include/RazorImu/moc_ImuDataLogger.cxx: include/RazorImu/moc_ImuDataLogger.cxx_parameters
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/hsa/Desktop/ImuTemplate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Generating include/RazorImu/moc_ImuDataLogger.cxx"
	cd /home/hsa/Desktop/ImuTemplate/build/include/RazorImu && /usr/lib/x86_64-linux-gnu/qt4/bin/moc @/home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_ImuDataLogger.cxx_parameters

include/RazorImu/moc_RazorImu2.cxx: ../include/RazorImu/RazorImu2.h
include/RazorImu/moc_RazorImu2.cxx: include/RazorImu/moc_RazorImu2.cxx_parameters
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/hsa/Desktop/ImuTemplate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Generating include/RazorImu/moc_RazorImu2.cxx"
	cd /home/hsa/Desktop/ImuTemplate/build/include/RazorImu && /usr/lib/x86_64-linux-gnu/qt4/bin/moc @/home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_RazorImu2.cxx_parameters

include/qcustomplot/moc_qcustomplot.cxx: ../include/qcustomplot/qcustomplot.h
include/qcustomplot/moc_qcustomplot.cxx: include/qcustomplot/moc_qcustomplot.cxx_parameters
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/hsa/Desktop/ImuTemplate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Generating include/qcustomplot/moc_qcustomplot.cxx"
	cd /home/hsa/Desktop/ImuTemplate/build/include/qcustomplot && /usr/lib/x86_64-linux-gnu/qt4/bin/moc @/home/hsa/Desktop/ImuTemplate/build/include/qcustomplot/moc_qcustomplot.cxx_parameters

CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.o: CMakeFiles/qcustomplot.dir/flags.make
CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.o: ../src/qcustomplot/qcustomplot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hsa/Desktop/ImuTemplate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.o -c /home/hsa/Desktop/ImuTemplate/src/qcustomplot/qcustomplot.cpp

CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hsa/Desktop/ImuTemplate/src/qcustomplot/qcustomplot.cpp > CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.i

CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hsa/Desktop/ImuTemplate/src/qcustomplot/qcustomplot.cpp -o CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.s

CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.o.requires:

.PHONY : CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.o.requires

CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.o.provides: CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.o.requires
	$(MAKE) -f CMakeFiles/qcustomplot.dir/build.make CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.o.provides.build
.PHONY : CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.o.provides

CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.o.provides.build: CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.o


CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.o: CMakeFiles/qcustomplot.dir/flags.make
CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.o: include/RazorImu/moc_FtdiPort.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hsa/Desktop/ImuTemplate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.o -c /home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_FtdiPort.cxx

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_FtdiPort.cxx > CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.i

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_FtdiPort.cxx -o CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.s

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.o.requires:

.PHONY : CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.o.requires

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.o.provides: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.o.requires
	$(MAKE) -f CMakeFiles/qcustomplot.dir/build.make CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.o.provides.build
.PHONY : CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.o.provides

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.o.provides.build: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.o


CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.o: CMakeFiles/qcustomplot.dir/flags.make
CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.o: include/RazorImu/moc_RazorImu.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hsa/Desktop/ImuTemplate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.o -c /home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_RazorImu.cxx

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_RazorImu.cxx > CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.i

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_RazorImu.cxx -o CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.s

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.o.requires:

.PHONY : CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.o.requires

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.o.provides: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.o.requires
	$(MAKE) -f CMakeFiles/qcustomplot.dir/build.make CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.o.provides.build
.PHONY : CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.o.provides

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.o.provides.build: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.o


CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.o: CMakeFiles/qcustomplot.dir/flags.make
CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.o: include/RazorImu/moc_ImuDataLogger.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hsa/Desktop/ImuTemplate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.o -c /home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_ImuDataLogger.cxx

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_ImuDataLogger.cxx > CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.i

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_ImuDataLogger.cxx -o CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.s

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.o.requires:

.PHONY : CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.o.requires

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.o.provides: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.o.requires
	$(MAKE) -f CMakeFiles/qcustomplot.dir/build.make CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.o.provides.build
.PHONY : CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.o.provides

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.o.provides.build: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.o


CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.o: CMakeFiles/qcustomplot.dir/flags.make
CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.o: include/RazorImu/moc_RazorImu2.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hsa/Desktop/ImuTemplate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.o -c /home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_RazorImu2.cxx

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_RazorImu2.cxx > CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.i

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hsa/Desktop/ImuTemplate/build/include/RazorImu/moc_RazorImu2.cxx -o CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.s

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.o.requires:

.PHONY : CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.o.requires

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.o.provides: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.o.requires
	$(MAKE) -f CMakeFiles/qcustomplot.dir/build.make CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.o.provides.build
.PHONY : CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.o.provides

CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.o.provides.build: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.o


CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.o: CMakeFiles/qcustomplot.dir/flags.make
CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.o: include/qcustomplot/moc_qcustomplot.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hsa/Desktop/ImuTemplate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.o -c /home/hsa/Desktop/ImuTemplate/build/include/qcustomplot/moc_qcustomplot.cxx

CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hsa/Desktop/ImuTemplate/build/include/qcustomplot/moc_qcustomplot.cxx > CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.i

CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hsa/Desktop/ImuTemplate/build/include/qcustomplot/moc_qcustomplot.cxx -o CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.s

CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.o.requires:

.PHONY : CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.o.requires

CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.o.provides: CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.o.requires
	$(MAKE) -f CMakeFiles/qcustomplot.dir/build.make CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.o.provides.build
.PHONY : CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.o.provides

CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.o.provides.build: CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.o


# Object files for target qcustomplot
qcustomplot_OBJECTS = \
"CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.o" \
"CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.o" \
"CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.o" \
"CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.o" \
"CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.o" \
"CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.o"

# External object files for target qcustomplot
qcustomplot_EXTERNAL_OBJECTS =

libqcustomplot.so: CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.o
libqcustomplot.so: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.o
libqcustomplot.so: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.o
libqcustomplot.so: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.o
libqcustomplot.so: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.o
libqcustomplot.so: CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.o
libqcustomplot.so: CMakeFiles/qcustomplot.dir/build.make
libqcustomplot.so: /usr/lib/x86_64-linux-gnu/libQtGui.so
libqcustomplot.so: /usr/lib/x86_64-linux-gnu/libQtCore.so
libqcustomplot.so: CMakeFiles/qcustomplot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hsa/Desktop/ImuTemplate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX shared library libqcustomplot.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/qcustomplot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/qcustomplot.dir/build: libqcustomplot.so

.PHONY : CMakeFiles/qcustomplot.dir/build

CMakeFiles/qcustomplot.dir/requires: CMakeFiles/qcustomplot.dir/src/qcustomplot/qcustomplot.cpp.o.requires
CMakeFiles/qcustomplot.dir/requires: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_FtdiPort.cxx.o.requires
CMakeFiles/qcustomplot.dir/requires: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu.cxx.o.requires
CMakeFiles/qcustomplot.dir/requires: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_ImuDataLogger.cxx.o.requires
CMakeFiles/qcustomplot.dir/requires: CMakeFiles/qcustomplot.dir/include/RazorImu/moc_RazorImu2.cxx.o.requires
CMakeFiles/qcustomplot.dir/requires: CMakeFiles/qcustomplot.dir/include/qcustomplot/moc_qcustomplot.cxx.o.requires

.PHONY : CMakeFiles/qcustomplot.dir/requires

CMakeFiles/qcustomplot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qcustomplot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qcustomplot.dir/clean

CMakeFiles/qcustomplot.dir/depend: include/RazorImu/moc_FtdiPort.cxx
CMakeFiles/qcustomplot.dir/depend: include/RazorImu/moc_RazorImu.cxx
CMakeFiles/qcustomplot.dir/depend: include/RazorImu/moc_ImuDataLogger.cxx
CMakeFiles/qcustomplot.dir/depend: include/RazorImu/moc_RazorImu2.cxx
CMakeFiles/qcustomplot.dir/depend: include/qcustomplot/moc_qcustomplot.cxx
	cd /home/hsa/Desktop/ImuTemplate/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hsa/Desktop/ImuTemplate /home/hsa/Desktop/ImuTemplate /home/hsa/Desktop/ImuTemplate/build /home/hsa/Desktop/ImuTemplate/build /home/hsa/Desktop/ImuTemplate/build/CMakeFiles/qcustomplot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/qcustomplot.dir/depend
