# Ecubee Cmake configuration
# @TODO: Support for Bart, Gert-Jan and Martijn

#initialize project
cmake_minimum_required(VERSION 2.8)
project(ecubee)

set (ecubee_VERSION_MAJOR 0)
set (ecubee_VERSION_MINOR 1)

SET (SRC main.cpp
	acos.cpp
	Box.cpp
	communicator.cpp
	CreateWindows.cpp
	CustomCamera.cpp
	HMC5843.cpp
	i2cManager.cpp
	LIS3LV02DL.cpp
	rs232.cpp)

# Compile for Bart
set(CMAKE_CXX_FLAGS "-D BART")


add_executable(ecubee ${SRC})

# OSG libs
target_link_libraries(ecubee osg)
target_link_libraries(ecubee osgViewer)
target_link_libraries(ecubee osgSim)
target_link_libraries(ecubee osgUtil)
target_link_libraries(ecubee osgGA)

# Other libs
target_link_libraries(ecubee m)
target_link_libraries(ecubee dl)
target_link_libraries(ecubee GL)
target_link_libraries(ecubee GLU)
target_link_libraries(ecubee OpenThreads)
target_link_libraries(ecubee Xext)
target_link_libraries(ecubee X11)

# Put Ecubee in bin dir
install(TARGETS ecubee DESTINATION bin)

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_VERSION_MAJOR "${ecubee_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${ecubee_VERSION_MINOR}")
include (CPack)
