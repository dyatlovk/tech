project(lua)

add_library(
	${PROJECT_NAME} SHARED
	lzio.c
	lvm.c
	lutf8lib.c
	lundump.c
	ltm.c
	ltablib.c
	ltable.c
	lstrlib.c
	lstring.c
	lstate.c
	lparser.c
	loslib.c
	lopcodes.c
	lobject.c
	loadlib.c
	lmem.c
	lmathlib.c
	llex.c
	liolib.c
	linit.c
	lgc.c
	lfunc.c
	ldump.c
	ldo.c
	ldebug.c
	ldblib.c
	lctype.c
	lcorolib.c
	lcode.c
	lbaselib.c
	lauxlib.c
	lapi.c
	luac.c
	)
add_library(Game::lua ALIAS ${PROJECT_NAME})

set(LUA_INCLUDE ${PROJECT_SOURCE_DIR})
target_include_directories(
	${PROJECT_NAME} 
	PUBLIC ${LUA_INCLUDE}
	)
target_link_libraries(${PROJECT_NAME})
install(
	TARGETS
	${PROJECT_NAME}
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	)
