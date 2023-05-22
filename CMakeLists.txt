cmake_minimum_required(VERSION 3.0.0)
project(dplatform VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
    merklecpp
    GIT_REPOSITORY https://github.com/microsoft/merklecpp.git
    GIT_TAG        2f3853db4b043b2df00869043c34cc1608bdad87
)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        ad0e89cbfb4d0c1ce4d097e134eb7be67baebb36
)
FetchContent_Declare(
    libfort
    GIT_REPOSITORY https://github.com/seleznevae/libfort.git
    GIT_TAG        b1c32b67511f4612996b287a1ef4a9df012521d2
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(merklecpp spdlog libfort)

find_package(OpenSSL REQUIRED)

add_executable(dplatform main.cpp src/Core/block.hpp src/Core/ledger.hpp src/Core/transaction.hpp src/Core/utils.hpp)
target_link_libraries(dplatform merklecpp OpenSSL::SSL spdlog libfort::fort)
