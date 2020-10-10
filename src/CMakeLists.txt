
add_executable(shoptimize main.cpp store.cpp product.cpp meal.cpp config.cpp)
target_link_libraries(shoptimize yaml-cpp)