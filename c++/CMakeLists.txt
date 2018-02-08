PROJECT(md5)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


#add source file to compile
SET(SRC_LIST "md5sha.cpp")
#output log mesage about SRC_list
MESSAGE(${SRC_LIST})

#add include dirctories
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})


#add link libraris
#LINK_LIBRARIES(${PROJECT_SOURCE_DIR}/build/libbase64.so.0)

#complie Base64.cpp to make share librariy libbase64.so
add_library(base64 SHARED Base64.cpp)  #ADD_LIBRARY(NAME [STATIC| SHARED|MODULE] [EXCLUDE_FROM_ALL] source1, source2,...) 创建一个名字name的库文件，SHARED STATIC 制定生成库的类型
#add link directories
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/build/)

#complie SRC_LIST to make excute software Test
add_executable(Test ${SRC_LIST})
TARGET_LINK_LIBRARIES(Test crypto) #TARGET_LINK_LIBRARIES(target [item1 [item2] [ ...] ]),将给定的库链接到target上，默认优先链接动态库，类似于静态链接，必须放置在
TARGET_LINK_LIBRARIES(Test base64)

