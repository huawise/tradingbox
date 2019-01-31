# CMakeList.txt: TradeDemo 的 CMake 项目，包括源和定义
# 此处特定于项目的逻辑。
#
cmake_minimum_required (VERSION 2.8.8)
project("TradeDemo")


set(CMAKE_CXX_FLAGS "--std=c++11")
set(CMAKE_BUILD_TYPE  Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

set(EsunnyTradeLibDir  ${PROJECT_SOURCE_DIR}/3rdparty/Esunny9.0)


include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/gateway
    ${EsunnyTradeLibDir}
)

link_directories(
    ${EsunnyTradeLibDir}
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
    ${EsunnyTradeLibDir}/*.dll
    ${EsunnyTradeLibDir}/*.so
)
file(COPY  ${LIBS} DESTINATION  "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}")

