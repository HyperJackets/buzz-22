add_library (CStateMachine CStateMachine.cpp CStateMachine.hpp)
add_executable (main main.cpp)
target_link_libraries (main CStateMachine)