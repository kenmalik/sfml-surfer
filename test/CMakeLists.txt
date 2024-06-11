set(TEST_SOURCES
    "../src/surfer.cpp"
    "../src/scanner.cpp"
    "../src/token.cpp"
    "../src/p.cpp"
    "../src/dom-tree.cpp"
    "../src/text-content.cpp"
    "../src/div.cpp"
    "../src/css-scanner.cpp"
    "../src/tag-scanner.cpp")
set(INCLUDES "../include" ${GUI_Library_SOURCE_DIR}/include)

add_executable(CssTest "./css-test.cpp" ${TEST_SOURCES})
target_include_directories(CssTest PUBLIC ${INCLUDES})
target_link_libraries(CssTest PUBLIC sfml-graphics sfml-window sfml-system
                                     sfml-audio gui-library)

add_executable(TagScanTest "./tag-scan-test.cpp" ${TEST_SOURCES})
target_include_directories(TagScanTest PUBLIC ${INCLUDES})
target_link_libraries(TagScanTest PUBLIC sfml-graphics sfml-window sfml-system
                                         sfml-audio gui-library)
