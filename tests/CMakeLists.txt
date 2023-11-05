add_executable(
	testMain
	test.c)

message(STATUS "test include 	${INSTALL_INCLUDEDIR} ")

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../src
	${INSTALL_INCLUDEDIR}
)

target_link_libraries(
	testMain
    lexer
)

enable_testing()

add_test(
  NAME		test_lexer
  COMMAND	$<TARGET_FILE:testMain>
  )

set_tests_properties(
	test_lexer
	PROPERTIES
	PASS_REGULAR_EXPRESSION
	"token value correct"
	FAIL_REGULAR_EXPRESSION
	"UNFINISHED"
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testSrc.test DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} FOLLOW_SYMLINK_CHAIN)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testSrc.test DESTINATION ${PROJECT_BINARY_DIR}/tests FOLLOW_SYMLINK_CHAIN)