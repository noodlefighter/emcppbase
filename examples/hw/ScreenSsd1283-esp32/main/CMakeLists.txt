set(srcs
    "main.cpp"
    )

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "."
                    )


set(EMBASE_CONFIG_OS "freertos")
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../../.. embase_root)

target_link_libraries(${COMPONENT_LIB} embase)
