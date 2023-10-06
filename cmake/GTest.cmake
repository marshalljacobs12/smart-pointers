if(ENABLE_GTEST)
    add_definitions(-DENABLE_GTEST_IN_LIBRARY)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include_directories(${googletest_SOURCE_DIR}/googletest/include/)
endif()
