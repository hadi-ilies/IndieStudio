# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.11)

# Notre projet est étiqueté "Bomberman"
project(Bomberman)

set(SRCDIR Src/)
set(ENTITYDIR Entity/)
set(UIDIR UserInterface/)
set(TXTDIR Text3d/)
set(INCDIR Include/)

include_directories(Include)
#include_directories(${INCDIR}Irrlicht) # if local include

#link_directories(Lib) # if local lib

# copy resource.cfg next to our binaries where OGRE looks for it
#file(COPY ${OGRE_CONFIG_DIR}/resources.cfg DESTINATION ${CMAKE_BINARY_DIR}) # if use ogre

# Crée des variables avec les fichiers à compiler
set(SRC
  ${SRCDIR}Main.cpp
  ${SRCDIR}FormattedSocket.cpp
  ${SRCDIR}Server.cpp
  ${SRCDIR}Client.cpp
  ${SRCDIR}Window.cpp
  ${SRCDIR}Error.cpp
  ${SRCDIR}Utility.cpp
  ${SRCDIR}Block.cpp
  ${SRCDIR}World.cpp
  ${SRCDIR}Entity.cpp
  ${SRCDIR}CameraMove.cpp
  ${SRCDIR}JukeBox.cpp
  ${SRCDIR}${ENTITYDIR}Bomb.cpp
  ${SRCDIR}${ENTITYDIR}PowerUp.cpp
  ${SRCDIR}${ENTITYDIR}Character.cpp
  ${SRCDIR}${ENTITYDIR}Player.cpp
  ${SRCDIR}${UIDIR}Button.cpp
  ${SRCDIR}${UIDIR}Menu.cpp
  ${SRCDIR}${UIDIR}MenuElement.cpp
  ${SRCDIR}${UIDIR}ButtonElement.cpp
  ${SRCDIR}${UIDIR}Wheel.cpp
  ${SRCDIR}${UIDIR}UserInterface.cpp
  ${SRCDIR}${TXTDIR}IrrFont.cpp
  ${SRCDIR}${TXTDIR}IrrFontBuffer.cpp
  ${SRCDIR}${TXTDIR}CharacterSceneNode.cpp
  ${SRCDIR}${TXTDIR}WordSceneNode.cpp
  )

set(INCLUDE
  ${INCDIR}FormattedSocket.hpp
  ${INCDIR}Window.hpp
  ${INCDIR}Error.hpp
  ${INCDIR}Utility.hpp
  ${INCDIR}Block.hpp
  ${INCDIR}World.hpp
  ${INCDIR}Entity.hpp
  ${INCDIR}CameraMove.hpp
  ${INCDIR}JukeBox.hpp
  ${INCDIR}${ENTITYDIR}Bomb.hpp
  ${INCDIR}${ENTITYDIR}PowerUp.hpp
  ${INCDIR}${ENTITYDIR}Character.hpp
  ${INCDIR}${ENTITYDIR}Player.hpp
  ${INCDIR}${UIDIR}Button.hpp
  ${INCDIR}${UIDIR}Menu.hpp
  ${INCDIR}${UIDIR}MenuElement.hpp
  ${INCDIR}${UIDIR}ButtonElement.hpp
  ${INCDIR}${UIDIR}Wheel.hpp
  ${INCDIR}${UIDIR}UserInterface.hpp
  ${INCDIR}${TXTDIR}IrrFont.hpp
  ${INCDIR}${TXTDIR}IrrFontBuffer.hpp
  ${INCDIR}${TXTDIR}CharacterSceneNode.hpp
  ${INCDIR}${TXTDIR}WordSceneNode.hpp
  )

#set(CMAKE_CXX_FLAGS "-W -Wall -Wextra")
set(CMAKE_CXX_FLAGS "-pedantic")

# On indique que l'on veut un exécutable "bomberman" compilé à partir des fichiers décrits par les variables SRC et INCLUDE
add_executable(Bomberman ${SRC} ${INCLUDE})
target_link_libraries(Bomberman Irrlicht)
find_package(SFML 2.5 COMPONENTS system graphics audio network REQUIRED)
target_link_libraries(Bomberman sfml-system sfml-graphics sfml-audio sfml-network)
target_link_libraries(Bomberman -lpthread)
target_link_libraries(Bomberman -lboost_system -lboost_filesystem)
