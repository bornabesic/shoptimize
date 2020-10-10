
add_library(so STATIC store.cpp product.cpp meal.cpp config.cpp)
target_link_libraries(so yaml-cpp)

add_executable(main main.cpp)
target_link_libraries(main so)