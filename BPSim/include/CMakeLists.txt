            add_library(
                BPCacheLib 
                hpp/BPBaseCache.hpp
                cpp/BPBaseCache.cpp
                hpp/BPBaseStruct.hpp
            )
            target_include_directories(BPCacheLib  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hpp)

            add_library(
               patternLib 
                hpp/PatternAutomatons.hpp
                cpp/PatternAutomatons.cpp
            )
            target_include_directories(patternLib  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hpp)

            add_library(
                twoLevelBPLib
                hpp/PredictorInterface.hpp
                hpp/Pag.hpp
                cpp/Pag.cpp   
            )
            target_include_directories(twoLevelBPLib  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hpp)
            target_link_libraries(twoLevelBPLib PRIVATE  BPCacheLib  patternLib  )
