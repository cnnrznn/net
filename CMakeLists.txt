# libraries
add_library(net net.c)

add_executable(test-client test-client.c)
target_link_libraries(test-client net)

add_executable(test-server test-server.c)
target_link_libraries(test-server net)
