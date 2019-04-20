include_directories(..)
add_definitions(-DTESTS_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/\")

ADD_EXECUTABLE( test_basic_assert test_basic_assert.cpp )
ADD_TEST(            basic_assert test_basic_assert    )

ADD_EXECUTABLE( test_file_readrec test_file_readrec.cpp ../pakfile.cpp)
ADD_TEST(            file_readrec test_file_readrec    )
target_link_libraries(test_file_readrec Qt5::Widgets Qt5::Charts ${ZLIB_LIBRARIES})