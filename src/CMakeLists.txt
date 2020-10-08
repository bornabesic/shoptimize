
add_library(so store.cpp)

add_executable(main main.cpp)
target_link_libraries(main so)