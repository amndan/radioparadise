cmake_minimum_required (VERSION 2.8.11)
project (gpio)

include_directories (
	src/include
	src)

#add_library (gpio src/GPIOClass.cpp)

add_executable (mpdGpio src/main.cpp)
#target_link_libraries (gpioDemo gpio)
