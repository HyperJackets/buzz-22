# CMake generated Testfile for 
# Source directory: C:/SEAN/HyperJackets/buzz-22
# Build directory: C:/SEAN/HyperJackets/buzz-22/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(BuzzTest "C:/SEAN/HyperJackets/buzz-22/build/core/test/Test.exe")
set_tests_properties(BuzzTest PROPERTIES  _BACKTRACE_TRIPLES "C:/SEAN/HyperJackets/buzz-22/CMakeLists.txt;9;add_test;C:/SEAN/HyperJackets/buzz-22/CMakeLists.txt;0;")
subdirs("core/src")
subdirs("core/test")
