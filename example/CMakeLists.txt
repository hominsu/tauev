cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

set(EXAMPLES
        logger)

foreach (example ${EXAMPLES})
    add_executable(${example} ${example}/${example}.cc)
    target_link_libraries(${example} tauev)
endforeach()

add_custom_target(examples ALL DEPENDS ${EXAMPLES})
