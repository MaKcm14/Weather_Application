# Setting main info
cmake_minimum_required(VERSION 3.1...3.28 FATAL_ERROR)

project(WeatherWebApplication)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
message("-- Configuring has begun")

# Setting some variables
set(CACHE_MANAGER_DIR ./source/cache_manager)
set(LOGGER_DIR ./source/logger)
set(REQUEST_MANAGER_DIR ./source/request_manager)
set(WEATHER_SERVICE_DIR ./source/weather_service)
set(ENABLE_TEST TRUE)


# Creating main targets
include_directories(./source/request_manager/include)
include_directories(./source/logger/include)
include_directories(./source/cache_manager/include)
include_directories(./source/weather_service/include)

add_subdirectory(${CACHE_MANAGER_DIR})
add_subdirectory(${LOGGER_DIR})
add_subdirectory(${REQUEST_MANAGER_DIR})
add_subdirectory(${WEATHER_SERVICE_DIR})

message("-- creating main target")
add_executable(main ./source/main.cpp)

target_link_libraries(request_manager_lib PUBLIC logger_lib)
target_link_libraries(cache_manager_lib PUBLIC request_manager_lib)
target_link_libraries(weather_service_lib PUBLIC cache_manager_lib)
target_link_libraries(main PRIVATE weather_service_lib)


# Finding packages
set(nlohmann_json_DIR ./source/nlohmann_json/build)

message("-- finding packages for Boost-1.55.0 and upper")
find_package(Boost 1.55.0 COMPONENTS system regex REQUIRED)

message("-- finding packages for PostgreSQL-10.0 and upper")
find_package(PostgreSQL 10.0)

message("-- finding packages for nlohmann_json-3.1.0 and upper")
find_package(nlohmann_json 3.1.0)


# Linking found packages
if (Boost_FOUND)
    message("-- packages for Boost-1.55.0 and upper were found")
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(request_manager_lib PUBLIC ${Boost_INCLUDE_LIBRARIES})
endif()

if (PostgreSQL_FOUND)
    message("-- packages for PostgreSQL-10.0 and upper were found")
    include_directories(${PostgreSQL_INCLUDE_DIRS})
    target_link_libraries(data_base_lib PUBLIC PostgreSQL::PostgreSQL)
endif()

if (nlohmann_json_FOUND)
    message("-- packages for nlohmann_json-3.1.0 and upper were found")
    include_directories(${nlohmann_json_INCLUDE_DIRS})
    target_link_libraries(request_manager_lib PUBLIC ${nlohmann_json_INCLUDE_LIBRARIES})
endif()


# Tests part
if (ENABLE_TEST)
    message("-- Tests are ENABLED")
    
    # Finding GTest
    message("-- finding packages for GTest")
    find_package(GTest 1.0)
    include(GoogleTest)

    if (GTest_FOUND)
        message("-- packages for GTest were found")
        message("-- enable testing for WeatherWebApplication")

        enable_testing()
        add_subdirectory(./tests)

        endif()

else ()
    message("-- Tests are NOT ENABLED")

endif()
