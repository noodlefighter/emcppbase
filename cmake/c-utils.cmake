function(add_map_file target_name)
    target_link_options(${target_name} PRIVATE -Wl,-Map=${target_name}.map)
endfunction()
