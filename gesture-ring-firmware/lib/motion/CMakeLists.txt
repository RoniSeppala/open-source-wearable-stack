target_sources(app PRIVATE
    src/vector3.c
    src/gravity.c
    src/motion.c
)

target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)