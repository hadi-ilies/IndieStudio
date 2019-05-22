# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.11)

# Notre projet est étiqueté "Bomberman"
project(Bomberman)

set(SRCDIR Src/)
set(ENTITYDIR Entity/)
set(INCDIR Include/)

include_directories(Include)
#include_directories(${INCDIR}Irrlicht) # if local include

#link_directories(Lib) # if local lib

# copy resource.cfg next to our binaries where OGRE looks for it
#file(COPY ${OGRE_CONFIG_DIR}/resources.cfg DESTINATION ${CMAKE_BINARY_DIR}) # if use ogre

# Crée des variables avec les fichiers à compiler
set(SRC
  ${SRCDIR}Main.cpp
  ${SRCDIR}Server.cpp
  ${SRCDIR}Client.cpp
  ${SRCDIR}Window.cpp
  ${SRCDIR}Error.cpp
  ${SRCDIR}Globpp.cpp # TODO or (Utility.cpp and rename Globpp.hpp in Utility.hpp)
  ${SRCDIR}Block.cpp
  ${SRCDIR}World.cpp
  ${SRCDIR}Entity.cpp
  ${SRCDIR}${ENTITYDIR}Bomb.cpp
  ${SRCDIR}${ENTITYDIR}PowerUp.cpp
  ${SRCDIR}${ENTITYDIR}Character.cpp
  ${SRCDIR}${ENTITYDIR}Player.cpp
  )

set(INCLUDE
  ${INCDIR}Window.hpp
  ${INCDIR}Error.hpp
  ${INCDIR}Globpp.hpp
  ${INCDIR}Block.hpp
  ${INCDIR}World.hpp
  ${INCDIR}Entity.hpp
  ${INCDIR}${ENTITYDIR}Bomb.hpp
  ${INCDIR}${ENTITYDIR}PowerUp.hpp
  ${INCDIR}${ENTITYDIR}Character.hpp
  ${INCDIR}${ENTITYDIR}Player.hpp
  )

#set(CMAKE_CXX_FLAGS "-W -Wall -Wextra")
set(CMAKE_CXX_FLAGS "-pedantic")

# On indique que l'on veut un exécutable "bomberman" compilé à partir des fichiers décrits par les variables SRC et INCLUDE
add_executable(Bomberman ${SRC} ${INCLUDE})
target_link_libraries(Bomberman Irrlicht)
find_package(SFML 2.5 COMPONENTS system audio network REQUIRED)
target_link_libraries(Bomberman sfml-system sfml-audio sfml-network)
