include_directories(.. ../pakfile)
add_definitions(-DTESTS_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/\")
add_definitions(-DDOCDATA_PATH=\"${CMAKE_SOURCE_DIR}/doc/example-protocols/\")

# basic tests of the macros in tests.h
ADD_EXECUTABLE( test_basic_assert test_basic_assert.cpp )
ADD_TEST(            basic_assert test_basic_assert    )

# test of a pointer based state machine c
ADD_EXECUTABLE( test_state_machine test_state_machine_c.cpp)
ADD_TEST(            state_machine test_state_machine)

# test of a pointer based state machine cpp
ADD_EXECUTABLE( test_state_machine++ test_state_machine_c++.cpp)
target_link_libraries(test_state_machine++ pakfile)
ADD_TEST(            state_machine++ test_state_machine++)

# test of the zlib.h implementation
ADD_EXECUTABLE( test_file_zlib    test_file_zlib.cpp)
ADD_TEST(            file_zlib    test_file_zlib)
target_link_libraries(test_file_zlib Qt5::Widgets ${ZLIB_LIBRARIES} pakfile)

# test of the implementation with external arj ('password' protected files)
ADD_EXECUTABLE( test_file_arj     ${HEADERS} test_file_arj.cpp)
ADD_TEST(            file_arj     test_file_arj)
target_link_libraries(test_file_arj Qt5::Widgets ${ZLIB_LIBRARIES} pakfile)