project(SpartyGnomeLib)

set(SOURCE_FILES MainFrame.cpp MainFrame.h pch.h SpartyGnomeView.cpp SpartyGnomeView.h Game.cpp Game.h ids.h
        Item.cpp Item.h BackgroundImage.cpp BackgroundImage.h ItemSpartyGnome.cpp ItemSpartyGnome.h
        Wall.cpp Wall.h Villain.cpp Villain.h ItemDoor.cpp ItemDoor.h Platform.cpp Platform.h
        Vector.cpp Vector.h ItemMoney.cpp ItemMoney.h ItemTuitionUp.cpp ItemTuitionUp.h
        DrawScrollingVisitor.cpp DrawScrollingVisitor.h ItemVisitor.h
        DrawStaticVisitor.cpp DrawStaticVisitor.h CollisionVisitor.cpp CollisionVisitor.h
        SolidCollisionVisitor.cpp SolidCollisionVisitor.h PlatformF.cpp PlatformF.h
        ItemMessage.cpp ItemMessage.h
        DrawMessagesVisitor.cpp DrawMessagesVisitor.h
        InteractionCollisionVisitor.cpp InteractionCollisionVisitor.h
        ItemLevelTimer.cpp ItemLevelTimer.h
        ItemMessageAnimated.cpp ItemMessageAnimated.h
        ItemScoreBoard.cpp ItemScoreBoard.h
        MoneyValueVisitor.cpp MoneyValueVisitor.h)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
