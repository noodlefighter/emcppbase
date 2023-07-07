# fixme: 目前仅能在build的根目录生成map文件
function(add_map_file TARGET)
    target_link_options(${TARGET} PRIVATE -Wl,-Map=${TARGET}.map)
endfunction()

function(print_size_of_target TARGET)
    add_custom_target(${TARGET}_always_display_size
        ALL
        COMMAND ${CMAKE_SIZE} --format=berkeley "$<TARGET_FILE:${TARGET}>"
        COMMENT "Target Sizes: "
        DEPENDS ${TARGET}
    )
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
