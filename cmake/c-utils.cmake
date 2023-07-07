# fixme: 目前仅能在build的根目录生成map文件
function(add_map_file TARGET)
    get_target_property(TARGET_BINARY_DIR ${TARGET} BINARY_DIR)
    target_link_options(${TARGET} PRIVATE -Wl,-Map=${TARGET_BINARY_DIR}/${TARGET}.map)
endfunction()

function(print_size_of_target TARGET)
    target_link_options(${TARGET} BEFORE PUBLIC -Wl,--print-memory-usage)

    # add_custom_target(${TARGET}_always_display_size
    #     ALL
    #     COMMAND ${CMAKE_SIZE} --format=berkeley "$<TARGET_FILE:${TARGET}>"
    #     COMMENT "Target Sizes: "
    #     DEPENDS ${TARGET}
    # )
endfunction()

function(generate_bin_file TARGET)
    add_custom_target(${TARGET}_always_generate_bin_file
        ALL
        COMMAND ${CMAKE_OBJCOPY} -Oihex "$<TARGET_FILE:${TARGET}>" "${TARGET}.hex"
        COMMAND ${CMAKE_OBJCOPY} -Obinary "$<TARGET_FILE:${TARGET}>" "${TARGET}.bin"
        COMMAND ${CMAKE_OBJDUMP} --all-headers --demangle --disassemble "$<TARGET_FILE:${TARGET}>" > "${TARGET}.lst"
        COMMENT "Generate Binary File: "
        DEPENDS ${TARGET}
    )
endfunction()

function(generate_fw_files TARGET)
    generate_bin_file(${TARGET})
    print_size_of_target(${TARGET})
    add_map_file(${TARGET})
endfunction()
