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
CMAKE_SOURCE_DIR = /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ping.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ping.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ping.dir/flags.make

CMakeFiles/ping.dir/srcs/ft_ping.c.o: CMakeFiles/ping.dir/flags.make
CMakeFiles/ping.dir/srcs/ft_ping.c.o: ../srcs/ft_ping.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ping.dir/srcs/ft_ping.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ping.dir/srcs/ft_ping.c.o   -c /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/ft_ping.c

CMakeFiles/ping.dir/srcs/ft_ping.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ping.dir/srcs/ft_ping.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/ft_ping.c > CMakeFiles/ping.dir/srcs/ft_ping.c.i

CMakeFiles/ping.dir/srcs/ft_ping.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ping.dir/srcs/ft_ping.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/ft_ping.c -o CMakeFiles/ping.dir/srcs/ft_ping.c.s

CMakeFiles/ping.dir/srcs/rtt_utility.c.o: CMakeFiles/ping.dir/flags.make
CMakeFiles/ping.dir/srcs/rtt_utility.c.o: ../srcs/rtt_utility.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ping.dir/srcs/rtt_utility.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ping.dir/srcs/rtt_utility.c.o   -c /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/rtt_utility.c

CMakeFiles/ping.dir/srcs/rtt_utility.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ping.dir/srcs/rtt_utility.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/rtt_utility.c > CMakeFiles/ping.dir/srcs/rtt_utility.c.i

CMakeFiles/ping.dir/srcs/rtt_utility.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ping.dir/srcs/rtt_utility.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/rtt_utility.c -o CMakeFiles/ping.dir/srcs/rtt_utility.c.s

CMakeFiles/ping.dir/srcs/dns_utility.c.o: CMakeFiles/ping.dir/flags.make
CMakeFiles/ping.dir/srcs/dns_utility.c.o: ../srcs/dns_utility.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/ping.dir/srcs/dns_utility.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ping.dir/srcs/dns_utility.c.o   -c /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/dns_utility.c

CMakeFiles/ping.dir/srcs/dns_utility.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ping.dir/srcs/dns_utility.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/dns_utility.c > CMakeFiles/ping.dir/srcs/dns_utility.c.i

CMakeFiles/ping.dir/srcs/dns_utility.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ping.dir/srcs/dns_utility.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/dns_utility.c -o CMakeFiles/ping.dir/srcs/dns_utility.c.s

CMakeFiles/ping.dir/srcs/statistics.c.o: CMakeFiles/ping.dir/flags.make
CMakeFiles/ping.dir/srcs/statistics.c.o: ../srcs/statistics.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/ping.dir/srcs/statistics.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ping.dir/srcs/statistics.c.o   -c /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/statistics.c

CMakeFiles/ping.dir/srcs/statistics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ping.dir/srcs/statistics.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/statistics.c > CMakeFiles/ping.dir/srcs/statistics.c.i

CMakeFiles/ping.dir/srcs/statistics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ping.dir/srcs/statistics.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/statistics.c -o CMakeFiles/ping.dir/srcs/statistics.c.s

CMakeFiles/ping.dir/srcs/icmp_packet.c.o: CMakeFiles/ping.dir/flags.make
CMakeFiles/ping.dir/srcs/icmp_packet.c.o: ../srcs/icmp_packet.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/ping.dir/srcs/icmp_packet.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ping.dir/srcs/icmp_packet.c.o   -c /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/icmp_packet.c

CMakeFiles/ping.dir/srcs/icmp_packet.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ping.dir/srcs/icmp_packet.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/icmp_packet.c > CMakeFiles/ping.dir/srcs/icmp_packet.c.i

CMakeFiles/ping.dir/srcs/icmp_packet.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ping.dir/srcs/icmp_packet.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/icmp_packet.c -o CMakeFiles/ping.dir/srcs/icmp_packet.c.s

CMakeFiles/ping.dir/srcs/loop.c.o: CMakeFiles/ping.dir/flags.make
CMakeFiles/ping.dir/srcs/loop.c.o: ../srcs/loop.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/ping.dir/srcs/loop.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ping.dir/srcs/loop.c.o   -c /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/loop.c

CMakeFiles/ping.dir/srcs/loop.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ping.dir/srcs/loop.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/loop.c > CMakeFiles/ping.dir/srcs/loop.c.i

CMakeFiles/ping.dir/srcs/loop.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ping.dir/srcs/loop.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/srcs/loop.c -o CMakeFiles/ping.dir/srcs/loop.c.s

# Object files for target ping
ping_OBJECTS = \
"CMakeFiles/ping.dir/srcs/ft_ping.c.o" \
"CMakeFiles/ping.dir/srcs/rtt_utility.c.o" \
"CMakeFiles/ping.dir/srcs/dns_utility.c.o" \
"CMakeFiles/ping.dir/srcs/statistics.c.o" \
"CMakeFiles/ping.dir/srcs/icmp_packet.c.o" \
"CMakeFiles/ping.dir/srcs/loop.c.o"

# External object files for target ping
ping_EXTERNAL_OBJECTS =

ping: CMakeFiles/ping.dir/srcs/ft_ping.c.o
ping: CMakeFiles/ping.dir/srcs/rtt_utility.c.o
ping: CMakeFiles/ping.dir/srcs/dns_utility.c.o
ping: CMakeFiles/ping.dir/srcs/statistics.c.o
ping: CMakeFiles/ping.dir/srcs/icmp_packet.c.o
ping: CMakeFiles/ping.dir/srcs/loop.c.o
ping: CMakeFiles/ping.dir/build.make
ping: CMakeFiles/ping.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable ping"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ping.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ping.dir/build: ping

.PHONY : CMakeFiles/ping.dir/build

CMakeFiles/ping.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ping.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ping.dir/clean

CMakeFiles/ping.dir/depend:
	cd /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/cmake-build-debug /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/cmake-build-debug /mnt/c/Users/m4xdo/OneDrive/Bureau/share_folder/ft_ping/cmake-build-debug/CMakeFiles/ping.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ping.dir/depend

