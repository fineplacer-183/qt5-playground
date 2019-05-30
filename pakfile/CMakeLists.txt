add_library(pakfile SHARED Machine.cpp MachineStates.cpp pakfile.cpp)
target_link_libraries(pakfile Qt5::Core)