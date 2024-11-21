            add_library(
                BPCacheLib 
                hpp/BPBaseCache.hpp
                cpp/BPBaseCache.cpp
                hpp/BPBaseStruct.hpp
            )
            target_include_directories(BPCacheLib  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hpp)
