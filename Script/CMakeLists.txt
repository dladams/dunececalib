# duneproc/Script/CMakeLists.txt

# Install shell scripts.
install(PROGRAMS
  dunececalibHelp
  doCalibPdsp
  doCalibIceberg
  makeCalibPdsp
  makeCalibFcl
DESTINATION bin)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Build setup file for this package.
string(TOUPPER ${PROJECT_NAME} PROJECT_UPNAME)
configure_file(setup.sh.in setup.sh)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/setup.sh DESTINATION .)
