# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/ljh/workspace/training/t3/httpserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ljh/workspace/training/t3/httpserver/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ljh/workspace/training/t3/httpserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/main.cpp.o -c /home/ljh/workspace/training/t3/httpserver/main.cpp

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ljh/workspace/training/t3/httpserver/main.cpp > CMakeFiles/main.dir/main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ljh/workspace/training/t3/httpserver/main.cpp -o CMakeFiles/main.dir/main.cpp.s

CMakeFiles/main.dir/asio/asio_server.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/asio/asio_server.cpp.o: ../asio/asio_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ljh/workspace/training/t3/httpserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/asio/asio_server.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/asio/asio_server.cpp.o -c /home/ljh/workspace/training/t3/httpserver/asio/asio_server.cpp

CMakeFiles/main.dir/asio/asio_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/asio/asio_server.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ljh/workspace/training/t3/httpserver/asio/asio_server.cpp > CMakeFiles/main.dir/asio/asio_server.cpp.i

CMakeFiles/main.dir/asio/asio_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/asio/asio_server.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ljh/workspace/training/t3/httpserver/asio/asio_server.cpp -o CMakeFiles/main.dir/asio/asio_server.cpp.s

CMakeFiles/main.dir/http/http_conn.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/http/http_conn.cpp.o: ../http/http_conn.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ljh/workspace/training/t3/httpserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/http/http_conn.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/http/http_conn.cpp.o -c /home/ljh/workspace/training/t3/httpserver/http/http_conn.cpp

CMakeFiles/main.dir/http/http_conn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/http/http_conn.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ljh/workspace/training/t3/httpserver/http/http_conn.cpp > CMakeFiles/main.dir/http/http_conn.cpp.i

CMakeFiles/main.dir/http/http_conn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/http/http_conn.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ljh/workspace/training/t3/httpserver/http/http_conn.cpp -o CMakeFiles/main.dir/http/http_conn.cpp.s

CMakeFiles/main.dir/userinfo/data.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/userinfo/data.cpp.o: ../userinfo/data.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ljh/workspace/training/t3/httpserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/userinfo/data.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/userinfo/data.cpp.o -c /home/ljh/workspace/training/t3/httpserver/userinfo/data.cpp

CMakeFiles/main.dir/userinfo/data.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/userinfo/data.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ljh/workspace/training/t3/httpserver/userinfo/data.cpp > CMakeFiles/main.dir/userinfo/data.cpp.i

CMakeFiles/main.dir/userinfo/data.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/userinfo/data.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ljh/workspace/training/t3/httpserver/userinfo/data.cpp -o CMakeFiles/main.dir/userinfo/data.cpp.s

CMakeFiles/main.dir/database/Connection_pool.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/database/Connection_pool.cpp.o: ../database/Connection_pool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ljh/workspace/training/t3/httpserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/database/Connection_pool.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/database/Connection_pool.cpp.o -c /home/ljh/workspace/training/t3/httpserver/database/Connection_pool.cpp

CMakeFiles/main.dir/database/Connection_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/database/Connection_pool.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ljh/workspace/training/t3/httpserver/database/Connection_pool.cpp > CMakeFiles/main.dir/database/Connection_pool.cpp.i

CMakeFiles/main.dir/database/Connection_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/database/Connection_pool.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ljh/workspace/training/t3/httpserver/database/Connection_pool.cpp -o CMakeFiles/main.dir/database/Connection_pool.cpp.s

CMakeFiles/main.dir/log/log.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/log/log.cpp.o: ../log/log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ljh/workspace/training/t3/httpserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main.dir/log/log.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/log/log.cpp.o -c /home/ljh/workspace/training/t3/httpserver/log/log.cpp

CMakeFiles/main.dir/log/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/log/log.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ljh/workspace/training/t3/httpserver/log/log.cpp > CMakeFiles/main.dir/log/log.cpp.i

CMakeFiles/main.dir/log/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/log/log.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ljh/workspace/training/t3/httpserver/log/log.cpp -o CMakeFiles/main.dir/log/log.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o" \
"CMakeFiles/main.dir/asio/asio_server.cpp.o" \
"CMakeFiles/main.dir/http/http_conn.cpp.o" \
"CMakeFiles/main.dir/userinfo/data.cpp.o" \
"CMakeFiles/main.dir/database/Connection_pool.cpp.o" \
"CMakeFiles/main.dir/log/log.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/main.cpp.o
main: CMakeFiles/main.dir/asio/asio_server.cpp.o
main: CMakeFiles/main.dir/http/http_conn.cpp.o
main: CMakeFiles/main.dir/userinfo/data.cpp.o
main: CMakeFiles/main.dir/database/Connection_pool.cpp.o
main: CMakeFiles/main.dir/log/log.cpp.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ljh/workspace/training/t3/httpserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/ljh/workspace/training/t3/httpserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ljh/workspace/training/t3/httpserver /home/ljh/workspace/training/t3/httpserver /home/ljh/workspace/training/t3/httpserver/build /home/ljh/workspace/training/t3/httpserver/build /home/ljh/workspace/training/t3/httpserver/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

