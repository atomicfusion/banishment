add_library(banishment SHARED banishment.cpp)

add_executable(banishment_test test.cpp)
target_link_libraries(banishment_test
	banishment
)

install(TARGETS banishment DESTINATION lib)
install(FILES banishment.h DESTINATION include)

##FIXME: Clean this up. Should it exist at all? As a different package?
install(TARGETS banishment_test DESTINATION bin)