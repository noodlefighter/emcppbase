
set(EMBASE_SRC
  ${EMBASE_SRC}
)

message("CMAKE_HOST_SYSTEM_NAME is: ${CMAKE_HOST_SYSTEM_NAME}")

if(NOT EMBASE_TARGET_PLATFORM)
  if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    set(EMBASE_TARGET_PLATFORM 1)
    set(EMBASE_LINKS uuid)
  elseif(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
    set(EMBASE_TARGET_PLATFORM 2)
  else()
    set(EMBASE_TARGET_PLATFORM 0)
  endif()
  set(EMBASE_TARGET_PLATFORM ${EMBASE_TARGET_PLATFORM} PARENT_SCOPE)
endif()

message("EMBASE_TARGET_PLATFORM is: ${EMBASE_TARGET_PLATFORM}")



if((${EMBASE_TARGET_PLATFORM} MATCHES 1) OR (${EMBASE_TARGET_PLATFORM} MATCHES 2))
set(EMBASE_SRC
  ${EMBASE_SRC}
  ${CMAKE_CURRENT_LIST_DIR}/embase_thread-pthread.cpp
)
set(EMBASE_LINKS ${EMBASE_LINKS} etl::etl)
endif()



if(${EMBASE_TARGET_PLATFORM} MATCHES 2)
  include_directories(/opt/homebrew/include)
  link_directories(/opt/homebrew/lib)
endif()

message("EMBASE_TARGET_LOGGER is: ${EMBASE_TARGET_LOGGER}")
if(${EMBASE_TARGET_LOGGER} MATCHES 1)
message("USE: EMBASE_STDOUT_LOGGER")
# set(EMBASE_SRC
#   ${EMBASE_SRC}
#   ${CMAKE_CURRENT_LIST_DIR}/game_log_stdout.cpp
# )
endif()

# if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
# target_compile_definitions(embase PRIVATE _DEBUG)
# endif()

add_library(embase ${EMBASE_SRC})
target_link_libraries(embase PUBLIC ${EMBASE_LINKS})
