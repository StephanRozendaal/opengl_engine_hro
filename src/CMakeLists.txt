file(GLOB OPENGL "./*.cpp")
add_executable(opengl ${OPENGL})
message("links: ${SFML_LIBRARIES} ${Boost_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES}")
target_link_libraries(opengl ${SFML_LIBRARIES} ${Boost_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
