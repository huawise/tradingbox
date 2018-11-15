# CMakeList.txt: TradeDemo 的 CMake 项目，包括源和定义
# 此处特定于项目的逻辑。
#
cmake_minimum_required (VERSION 2.8.8)
project("TradeDemo")


set(CMAKE_CXX_FLAGS "-std=c++1y")
set(CMAKE_BUILD_TYPE  Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

IF (WIN32)
    set(EsunnyTradeLibDir  ${PROJECT_SOURCE_DIR}/3rdparty/iTapTradeApi8.1_Win64_6048/)
ELSEIF(UNIX)
    set(EsunnyTradeLibDir  ${PROJECT_SOURCE_DIR}/3rdparty/iTapTradeApi8.1_Linux_6048/)
ENDIF(WIN32)

include_directories(
    .
    ./gateway/
    ${EsunnyTradeLibDir}/include/
)

link_directories(
    ${EsunnyTradeLibDir}/lib/
)

IF (WIN32)
    link_libraries(iTapTradeAPI_64)
ELSEIF(UNIX)
    link_libraries(libiTapTradeAPI.so)
ENDIF(WIN32)


file(GLOB SRC *.cpp ./gateway/*.cpp )
add_executable(${PROJECT_NAME} ${SRC})


set(CMAKE_INSTALL_PREFIX ./dist/)

file(GLOB LIBS
    ${EsunnyTradeLibDir}/lib/*
)
file(COPY  ${LIBS} DESTINATION  "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}")

