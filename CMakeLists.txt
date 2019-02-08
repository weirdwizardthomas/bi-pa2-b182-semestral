cmake_minimum_required(VERSION 3.13)
project(Pazaak)

set(CMAKE_CXX_STANDARD 14)

add_executable(Pazaak main.cpp "Cards/Card Interface/Card.cpp" "Cards/Card Interface/Card.h" "Cards/Card Implementation/BasicCard/BasicCard.cpp" "Cards/Card Implementation/BasicCard/BasicCard.h" "Cards/Card Implementation/DualCard/DualCard.cpp" "Cards/Card Implementation/DualCard/DualCard.h" "Cards/Card Implementation/DoubleCard/DoubleCard.cpp" "Cards/Card Implementation/DoubleCard/DoubleCard.h" "Cards/Card Implementation/DualCard/FlexCard/FlexCard.cpp" "Cards/Card Implementation/DualCard/FlexCard/FlexCard.h" PlayerBoard.cpp PlayerBoard.h "Cards/Card Implementation/DualCard/FlipCard/FlipCard.cpp" "Cards/Card Implementation/DualCard/FlipCard/FlipCard.h")