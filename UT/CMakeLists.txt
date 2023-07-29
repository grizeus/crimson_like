set(This crimson_UT)

set(Sources
    Crimson_UT.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    GTest::gtest_main
)

add_test(
    NAME ${This}
    COMMAND ${This}
)

add_custom_command(
    TARGET ${This}
    COMMENT "Run tests"
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> -R "^crimson_UT" --output-on-failures
)
