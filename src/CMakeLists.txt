
add_library(so store.cpp product.cpp)

add_executable(main main.cpp)
target_link_libraries(main so)