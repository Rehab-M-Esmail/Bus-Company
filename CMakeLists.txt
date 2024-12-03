cmake_minimum_required(VERSION 3.25)
project(dsProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(dsProject main.cpp Company.h Event.h Passenger.h LinkedList.h Node.h LinkedList.cpp Node.cpp Bus.h Station.h Queue.h Queue.cpp Company.cpp Station.cpp Bus.cpp Passenger.cpp Time.h Time.cpp PriorityQueue.h PriorityQueue.cpp Event.cpp)
