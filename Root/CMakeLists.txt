# dunececalib/Root/CMakeLists.txt

# Install Root scripts.
install(
  DIRECTORY .
  DESTINATION root
  FILES_MATCHING
    PATTERN "*.h"
    PATTERN "*.C"
)

add_subdirectory("Iceberg")
add_subdirectory("Protodune")
