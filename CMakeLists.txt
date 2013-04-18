# Ecubee Cmake configuration
# @TODO: Support for Bart, Gert-Jan and Martijn

#initialize project
cmake_minimum_required(VERSION 2.8)
project(ecubee)

set (ecubee_VERSION_MAJOR 0)
set (ecubee_VERSION_MINOR 1)

SET (SRC main.cpp
	math/acos.cpp
	math/quaternion.c
	math/vector3d.c
	comm/communicator.cpp
	comm/rs232.cpp
	osg/Box.cpp
	osg/CreateWindows.cpp
	osg/CustomCamera.cpp
	i2c/MPU9150Wrapper.cpp
	i2c/mpu9150.c
	i2c/linux_glue.c
	eMPL/inv_mpu.c
	eMPL/inv_mpu_dmp_motion_driver.c)

# Compile for Bart and MPU9150
set(CMAKE_CXX_FLAGS "-DBART")
set(CMAKE_C_FLAGS "-DEMPL_TARGET_LINUX -DMPU9150 -DAK8975_SECONDARY -DMPU9150_DEBUG")
include_directories(math comm osg i2c eMPL)

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
