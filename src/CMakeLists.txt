aux_source_directory(. LEETCODE_SRC)
add_executable(leetcode ${LEETCODE_SRC})
target_link_libraries(leetcode PRIVATE Catch2::Catch2)
