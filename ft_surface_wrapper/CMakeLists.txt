cmake_minimum_required(VERSION 3.15)

# set the project name
project(ft_surface_wrapper)
enable_testing()

# include dir
include_directories(include)

# add the executable
add_library(ft_surface_wrapper SHARED src/native_window_wrapper.c)

#test
add_executable(surface_test test/test.c)

target_link_libraries(surface_test ft_surface_wrapper)

add_test(NAME SurfaceTest COMMAND surface_test)

# install
install (TARGETS ft_surface_wrapper DESTINATION /usr/lib64)
install (FILES ft_surface_wrapper.pc DESTINATION /usr/lib64/pkgconfig/)
install (FILES include/display_type.h DESTINATION /usr/include/ftsurface)
install (FILES include/window.h DESTINATION /usr/include/ftsurface)
install (FILES include/external_window.h DESTINATION /usr/include/ftsurface)
install (FILES include/buffer_handle.h DESTINATION /usr/include/ftsurface)
install (FILES include/native_window_wrapper.h DESTINATION /usr/include/ftsurface)

# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
