function(add_map_file target_name)
    target_link_options(${target_name} PRIVATE -Wl,-Map=${target_name}.map)
endfunction()

function(print_size_of_target TARGET)
    add_custom_target(${TARGET}_always_display_size
        ALL COMMAND ${CMAKE_SIZE} "$<TARGET_FILE:${TARGET}>"
        COMMENT "Target Sizes: "
        DEPENDS ${TARGET}
    )
endfunction()
