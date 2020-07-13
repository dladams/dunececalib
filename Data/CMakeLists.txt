# dunececalib/Data/CMakeLists.txt

# Install data files.
install(
  DIRECTORY .
  DESTINATION data
  FILES_MATCHING PATTERN "*.fcl"
)
