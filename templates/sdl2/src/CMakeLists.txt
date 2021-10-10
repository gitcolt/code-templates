find_package(SDL2 REQUIRED)

add_executable(main
  main.c
  )

target_include_directories(main
  PRIVATE
  ${SDL2_INCLUDE_DIRS}
  )

target_link_libraries(main
  ${SDL2_LIBRARIES}
  )

add_custom_target(copy_assets
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
  )

add_dependencies(main copy_assets)

