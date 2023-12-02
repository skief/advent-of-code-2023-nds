set(nds_libs nds9)

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/visualizations/day02)

add_executable(vis_day02 ${dir}/main.cpp)
target_link_libraries(vis_day02 ${nds_libs})
nds_create_rom(vis_day02)
