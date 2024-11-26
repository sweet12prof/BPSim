            add_executable(main main.cpp)
            target_compile_options(main PRIVATE -Wall)
            target_link_libraries(main PRIVATE twoLevelBPLib)
            # target_link_libraries(main PRIVATE  )
            # target_link_directories(main PRIVATE  )
           
            # target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/lib/hpp)
            # target_link_libraries(main PRIVATE ${CMAKE_SOURCE_DIR}/lib/cache-lib.lib)
