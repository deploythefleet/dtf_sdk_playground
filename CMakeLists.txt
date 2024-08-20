cmake_minimum_required(VERSION 3.16)

# Using C++ 17
set(CMAKE_CXX_STANDARD 17)

set(SDKCONFIG_DEFAULTS "sdkconfig.defaults")

# Be explicit here. Otherwise, the entirety of the IDF is built even if
# you are only using a small piece of it. This also forces you to keep track
# of every dependency you have. Helps reduce build time
set(COMPONENTS main)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# Set your project name here. This will be used to name your binary
project(esp32_production_template)
