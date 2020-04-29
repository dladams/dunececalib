# dunececalib/Utility/CMakeLists.txt

# Build a utility library.
set(PKGLIB ${PROJECT_NAME})
find_library(libDuneCommon NAMES dune_DuneCommon)
find_library(libArtSupport NAMES dune_ArtSupport)
find_library(libart_Framework_Services_Registry NAMES art_Framework_Services_Registry)
#message(FATAL_ERROR "service_lib_list: ${service_lib_list}")
FILE(GLOB MYSRCS *.cxx)
add_library(${PKGLIB} SHARED ${MYSRCS})
target_link_libraries(${PKGLIB} ${libDuneCommon})
target_link_libraries(${PKGLIB} ${libArtSupport})
target_link_libraries(${PKGLIB} ${libart_Framework_Services_Registry})
target_link_libraries(${PKGLIB} ${source_lib_list})
target_link_libraries(${PKGLIB} ${ROOT_LIBRARIES})
install(TARGETS ${PKGLIB} DESTINATION lib)

# Build Root dictionary.
message("Start building dictionaries")
set(DICT_NAME ${PROJECT_NAME})
reflex_generate_dictionary(${DICT_NAME} classes.h SELECTION classes_def.xml)
add_library(${PKGLIB}Dict SHARED ${CMAKE_CURRENT_BINARY_DIR}/${DICT_NAME}.cxx)
target_link_libraries(${PKGLIB}Dict ${PKGLIB})
#target_link_libraries(${PKGLIB}Dict ${source_lib_list})
target_link_libraries(${PKGLIB}Dict ${ROOT_LIBRARIES})
install(TARGETS ${PKGLIB}Dict DESTINATION lib)
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${DICT_NAME}_rdict.pcm
    ${CMAKE_CURRENT_BINARY_DIR}/${DICT_NAME}Dict.rootmap
  DESTINATION lib
)

#add_subdirectory(test)
