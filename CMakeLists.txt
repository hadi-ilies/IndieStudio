# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.11)

# Notre projet est étiqueté "Bomberman"
project(Bomberman)

set(SRCDIR Src/)
set(INCDIR Include/)

include_directories(Include)
include_directories(/usr/include/irrlicht) # TODO modif path

link_directories(Lib)

# Crée des variables avec les fichiers à compiler
set(SRC
  ${SRCDIR}Main.cpp
  ${SRCDIR}World.cpp
  ${SRCDIR}Entity.cpp
  ${SRCDIR}PowerUp.cpp
  ${SRCDIR}Player.cpp
  )

set(INCLUDE
  ${INCDIR}World.hpp
  ${INCDIR}Entity.hpp
  ${INCDIR}PowerUp.hpp
  ${INCDIR}Player.hpp
  )

set(CMAKE_CXX_FLAGS "-W -Wall -Wextra")

# On indique que l'on veut un exécutable "bomberman" compilé à partir des fichiers décrits par les variables SRC et INCLUDE
add_executable(bomberman ${SRC} ${INCLUDE})
target_link_libraries(bomberman Irrlicht)
