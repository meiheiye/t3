cmake_minimum_required(VERSION 3.12)

project(main)

#set(Boost_COMPONENTS json)
#find_package(Boost 1.83.0 REQUIRED COMPONENTS ${Boost_COMPONENTS})

include_directories(http log userinfo database asio)

aux_source_directory(http SRC_LIST1)

aux_source_directory(userinfo SRC_LIST2)

aux_source_directory(database SRC_LIST3)

aux_source_directory(log SRC_LIST4)

aux_source_directory(asio SRC_LIST5)

# 创建可执行文件
add_executable(${PROJECT_NAME} main.cpp ${SRC_LIST5} ${SRC_LIST1} ${SRC_LIST2} ${SRC_LIST3} ${SRC_LIST4} )

target_link_libraries(${PROJECT_NAME} mysqlclient)

target_link_libraries(${PROJECT_NAME}  pthread)

