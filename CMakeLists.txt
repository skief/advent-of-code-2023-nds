cmake_minimum_required(VERSION 3.25)
project(advent_of_code_2023_nds)

set(CMAKE_CXX_STANDARD 17)

add_custom_command(
        OUTPUT nds/generated/soundbank.bin nds/generated/soundbank.h
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/nds/generated
        COMMAND ${MMUTIL_EXE} ../sfx/* -d -osoundbank.bin -hsoundbank.h
)

add_custom_command(
        OUTPUT nds/generated/soundbank.o nds/generated/soundbank_bin.h
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/nds/generated
        COMMAND ${DKP_BIN2S} -a 4 -H soundbank_bin.h soundbank.bin > tempFile
        COMMAND ${CMAKE_C_COMPILER} -x assembler-with-cpp -c tempFile -o soundbank.o
        COMMAND rm tempFile
        DEPENDS nds/generated/soundbank.bin
)

set(graphics background_night textures_32)

foreach (graphic in ${graphics})
    add_custom_command(
            OUTPUT nds/generated/${graphic}.c nds/generated/${graphic}.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/nds/generated
            COMMAND ${GRIT_EXE} ../gfx/${graphic}.bmp -gb -gB8 -ftc -o ${graphic}
            COMMAND cmake -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/nds/generated/
            COMMAND cp ${graphic}.* ${CMAKE_CURRENT_BINARY_DIR}/nds/generated/
    )
endforeach ()


set(media nds/generated/soundbank_bin.h nds/generated/background_night.c nds/generated/textures_32.c)
set(nds nds/christmasTree.cpp nds/particleSystem.cpp nds/graphics.cpp nds/sounds.cpp ${media})
set(nds_libs nds9 mm9 fat ${CMAKE_CURRENT_SOURCE_DIR}/nds/generated/soundbank.o)

foreach (day RANGE 1 4)
    set(dayInt ${day})
    string(LENGTH "${day}" _strlen)
    if (_strlen EQUAL 1)
        set(day "day0${day}")
    else()
        set(day "day${day}")
    endif()

    add_executable(${day} main.cpp ${nds} aoc/${day}/solution.cpp aoc/utils/utils.cpp)
    target_link_libraries(${day} ${nds_libs})
    target_include_directories(${day} PUBLIC aoc/${day} aoc/utils)
    target_compile_definitions(${day} PUBLIC DAY=${dayInt})
    nds_create_rom(${day})
endforeach ()

include(${CMAKE_CURRENT_SOURCE_DIR}/visualizations/day02/day02.cmake)
