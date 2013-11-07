cmake_minimum_required(VERSION 2.8)

project(Core)

aux_source_directory(. SRC_LIST)

add_library(${PROJECT_NAME} ${SRC_LIST})
