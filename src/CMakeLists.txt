
add_executable(shoptimize main.cpp store.cpp product.cpp meal.cpp config.cpp solver.cpp constraint.cpp)
target_link_libraries(shoptimize yaml-cpp)