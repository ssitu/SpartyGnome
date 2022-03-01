project(SpartyGnomeLib)

set(SOURCE_FILES MainFrame.cpp MainFrame.h pch.h SpartyGnomeView.cpp SpartyGnomeView.h Game.cpp Game.h ids.h Item.cpp Item.h
        BackgroundImage.cpp BackgroundImage.h ItemSpartyGnome.cpp ItemSpartyGnome.h Wall.cpp Wall.h Villain.cpp Villain.h ItemDoor.cpp ItemDoor.h
        Platform.cpp Platform.h Vector.cpp Vector.h)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
