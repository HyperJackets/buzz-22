# CMake generated Testfile for 
# Source directory: /Users/vulcan/work/HJ/buzz-22
# Build directory: /Users/vulcan/work/HJ/buzz-22/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(BuzzTest "/Users/vulcan/work/HJ/buzz-22/build/core/test/Test")
set_tests_properties(BuzzTest PROPERTIES  _BACKTRACE_TRIPLES "/Users/vulcan/work/HJ/buzz-22/CMakeLists.txt;9;add_test;/Users/vulcan/work/HJ/buzz-22/CMakeLists.txt;0;")
subdirs("core/src")
subdirs("core/test")
