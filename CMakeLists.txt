# CMakeList.txt: TradeDemo 的 CMake 项目，包括源和定义
# 此处特定于项目的逻辑。
#
cmake_minimum_required (VERSION 2.8.8)
project("TradeDemo")

set(CMAKE_CONFIGURATION_TYPES Debug)
#set(CMAKE_CXX_FLAGS "-std=c++11 -m64")



set(EsunnyTradeLibDir  ${PROJECT_SOURCE_DIR}/3rdparty/iTapTradeApi8.1_Win64_6048/)
include_directories(
    .
    ./gateway/
    ${EsunnyTradeLibDir}/include/
)

link_directories(
    ${EsunnyTradeLibDir}/lib/
)


link_libraries(iTapTradeAPI_64)

file(GLOB SRC *.cpp ./gateway/*.cpp )
add_executable(${PROJECT_NAME} ${SRC})


set(CMAKE_INSTALL_PREFIX ./dist/)

file(GLOB LIBS
    ${EsunnyTradeLibDir}/lib/*
)
file(COPY  ${LIBS} DESTINATION ${PROJECT_BINARY_DIR}/Debug/)

