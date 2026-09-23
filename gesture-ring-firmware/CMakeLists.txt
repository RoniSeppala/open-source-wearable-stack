cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(gesture_ring_firmware)

target_sources(app PRIVATE
    src/main.c
    src/get_all_imu_data.c
    src/gesture_test.c
)

add_subdirectory(drivers)
add_subdirectory(lib)