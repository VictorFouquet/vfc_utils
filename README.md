cmake_minimum_required(VERSION 3.16)

project(vfc_utils
    VERSION 1.0
    LANGUAGES C
)

# -------------------------------
# Build configuration
# -------------------------------

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# -------------------------------
# Library target
# -------------------------------

file(GLOB SRC_FILES CONFIGURE_DEPENDS
    src/*.c
)

add_library(vfc_utils STATIC ${SRC_FILES})

# Output name: libvfcutils.a
set_target_properties(vfc_utils PROPERTIES
    OUTPUT_NAME vfcutils
)

# Public include directory
target_include_directories(vfc_utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# -------------------------------
# Compiler warnings (common)
# -------------------------------

target_compile_options(vfc_utils
    PRIVATE
        -Wall
        -Wextra
)

# -------------------------------
# Debug / Release flags
# -------------------------------

target_compile_options(vfc_utils
    PRIVATE
        $<$<CONFIG:Debug>:
            -g
            -O0
            -fsanitize=address
            -fstack-protector-strong
        >
        $<$<CONFIG:Release>:
            -O3
            -DNDEBUG
        >
)

target_link_options(vfc_utils
    PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address>
)
