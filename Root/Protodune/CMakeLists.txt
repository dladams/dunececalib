# dunececalib/Root/Protodune/CMakeLists.txt

# Install Root scripts.
install(
  DIRECTORY .
  DESTINATION root
  FILES_MATCHING PATTERN "*.C"
)
