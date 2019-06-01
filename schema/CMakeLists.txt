cmake_minimum_required(VERSION 3.0)

set(FLATC ${PROJECT_SOURCE_DIR}/../flatbuffers/Debug/flatc.exe)

message(${FLATC})

add_custom_command(
	OUTPUT ${PROJECT_SOURCE_DIR}/include/Person_generated.h
	COMMAND ${FLATC} -o ${PROJECT_SOURCE_DIR}/include -c ${PROJECT_SOURCE_DIR}/schema/Person.fbs --scoped-enums
	DEPENDS ${PROJECT_SOURCE_DIR}/schema/Person.fbs
)

add_custom_target(schema_headers DEPENDS ${PROJECT_SOURCE_DIR}/include/Person_generated.h)
