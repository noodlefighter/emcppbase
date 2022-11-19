set(srcs
    "main.cpp"
    )

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "."
                    )
target_link_libraries(${COMPONENT_LIB} embase)
