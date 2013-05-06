# Ecubee Cmake configuration
# @TODO: Support for Bart, Gert-Jan and Martijn

#initialize project
cmake_minimum_required(VERSION 2.8)
project(ecubee)

set (ecubee_VERSION_MAJOR 1)
set (ecubee_VERSION_MINOR 0)

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
	
SET (CALSRC imucal.c
	math/quaternion.c
	math/vector3d.c
	i2c/mpu9150.c
	i2c/linux_glue.c
	eMPL/inv_mpu.c
	eMPL/inv_mpu_dmp_motion_driver.c)

# Compile for Bart and MPU9150
#set(CMAKE_CXX_FLAGS "-DBART")
set_target_properties(ecubee-bart PROPERTIES COMPILE_FLAGS "-DBART")
set_target_properties(ecubee-gertjan PROPERTIES COMPILE_FLAGS "-DGERTJAN")
set_target_properties(ecubee-martijn PROPERTIES COMPILE_FLAGS "-DMARTIJN")

set(CMAKE_C_FLAGS "-DEMPL_TARGET_LINUX -DMPU9150 -DAK8975_SECONDARY")
include_directories(math comm osg i2c eMPL)

add_executable(ecubee-bart ${SRC})
add_executable(ecubee-gertjan ${SRC})
add_executable(ecubee-martijn ${SRC})
add_executable(ecubeecal ${CALSRC})

# OSG libs
target_link_libraries(ecubee-bart osg)
target_link_libraries(ecubee-bart osgViewer)
target_link_libraries(ecubee-bart osgSim)
target_link_libraries(ecubee-bart osgUtil)
target_link_libraries(ecubee-bart osgGA)

target_link_libraries(ecubee-gertjan osg)
target_link_libraries(ecubee-gertjan osgViewer)
target_link_libraries(ecubee-gertjan osgSim)
target_link_libraries(ecubee-gertjan osgUtil)
target_link_libraries(ecubee-gertjan osgGA)

target_link_libraries(ecubee-martijn osg)
target_link_libraries(ecubee-martijn osgViewer)
target_link_libraries(ecubee-martijn osgSim)
target_link_libraries(ecubee-martijn osgUtil)
target_link_libraries(ecubee-martijn osgGA)


# Other libs
target_link_libraries(ecubee-bart m)
target_link_libraries(ecubee-bart dl)
#target_link_libraries(ecubee-bart GL)
#target_link_libraries(ecubee-bart GLU)
target_link_libraries(ecubee-bart GLESv2)
target_link_libraries(ecubee-bart OpenThreads)
target_link_libraries(ecubee-bart Xext)
target_link_libraries(ecubee-bart X11)

target_link_libraries(ecubee-gertjan m)
target_link_libraries(ecubee-gertjan dl)
#target_link_libraries(ecubee-gertjan GL)
#target_link_libraries(ecubee-gertjan GLU)
target_link_libraries(ecubee-bart GLESv2)
target_link_libraries(ecubee-gertjan OpenThreads)
target_link_libraries(ecubee-gertjan Xext)
target_link_libraries(ecubee-gertjan X11)

target_link_libraries(ecubee-martijn m)
target_link_libraries(ecubee-martijn dl)
#target_link_libraries(ecubee-martijn GL)
#target_link_libraries(ecubee-martijn GLU)
target_link_libraries(ecubee-bart GLESv2)
target_link_libraries(ecubee-martijn OpenThreads)
target_link_libraries(ecubee-martijn Xext)
target_link_libraries(ecubee-martijn X11)

target_link_libraries(ecubeecal m)

# Put Ecubee in bin dir
install(TARGETS ecubee-bart DESTINATION bin)
install(TARGETS ecubee-gertjan DESTINATION bin)
install(TARGETS ecubee-martijn DESTINATION bin)
install(TARGETS ecubeecal DESTINATION bin)

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_VERSION_MAJOR "${ecubee_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${ecubee_VERSION_MINOR}")
include (CPack)
