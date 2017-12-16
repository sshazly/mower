#!/usr/bin/env bash
# THIS FILE IS FOR INITIALIZING ALL THE PLUGINS

# Reset the plugins
unset GAZEBO_PLUGIN_PATH
#$(echo $(rospack find mower_gazebo))
# Remove the plugin build directories
#$(rm -r $(rospack find mower_gazebo)/plugins/World/build)
#$(rm -r $(rospack find mower_gazebo)/plugins/Visual/build)
#$(rm -r $(rospack find mower_gazebo)/plugins/System/build)
#$(rm -r $(rospack find mower_gazebo)/plugins/Sensor/build)
#$(rm -r $(rospack find mower_gazebo)/plugins/Model/build)

# Remake the plugin build directories
#$(mkdir $(rospack find mower_gazebo)/plugins/World/build)
#$(mkdir $(rospack find mower_gazebo)/plugins/Visual/build)
#$(mkdir $(rospack find mower_gazebo)/plugins/System/build)
#$(mkdir $(rospack find mower_gazebo)/plugins/Sensor/build)
#$(mkdir $(rospack find mower_gazebo)/plugins/Model/build)

echo compiling and making CXX Plugin Files ..
# CMake the plugin directories
cd $(rospack find mower_gazebo)/plugins/World/build && cmake ../ && make
echo [ 15%] ... compiling and making CXX World Plugins
cd $(rospack find mower_gazebo)/plugins/Visual/build && cmake ../ && make
echo [ 30%] ... compiling and making CXX Visual Plugins
cd $(rospack find mower_gazebo)/plugins/System/build && cmake ../ && make
echo [ 50%] ... compiling and making CXX System Plugins
cd $(rospack find mower_gazebo)/plugins/Sensor/build && cmake ../ && make
echo [ 65%] ... compiling and making CXX Sensor Plugins
cd $(rospack find mower_gazebo)/plugins/Model/build && cmake ../ && make
echo [ 80%] ... compiling and making CXX Model Plugins
cd $(rospack find mower_gazebo)/plugins/GUI/build && cmake ../ && make
echo [100%] ... compiling and making CXX GUI Plugins
echo finished compiling and making CXX Gazebo Plugin Files

# Add the plugins to the GAZEBO_PLUGIN_PATH variable
export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:$(rospack find mower_gazebo)/plugins/World/build
export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:$(rospack find mower_gazebo)/plugins/Visual/build
export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:$(rospack find mower_gazebo)/plugins/System/build
export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:$(rospack find mower_gazebo)/plugins/Sensor/build
export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:$(rospack find mower_gazebo)/plugins/Model/build

cd $(rospack find mower_gazebo)/worlds


