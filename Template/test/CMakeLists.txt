
add_executable(TemplateTests
        MainTestSpec.cpp)

set(internal_libs Source)

target_link_libraries(TemplateTests
        PRIVATE Catch2::Catch2 Catch2::Catch2WithMain ${internal_libs})

target_include_directories(TemplateTests PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/source"
        )

add_test(NAME TemplateTests COMMAND TemplateTests)