#include "Game/gameScene.h"
#include "Game/gameStageBinder.h"

namespace uking {

// (own file: the original calls the gameSceneHasStageBinder() thunk, which lives in gameStage.cpp, out of line)
// NON_MATCHING: store order of the inlined TitleStageArg / binder constructors (the original stores the null heap
// first and pairs the argument's vtable with the null environment archive in one stp).
void createTitleStageBinder(bool a1, bool a2) {
    if (gameSceneHasStageBinder())
        return;
    TitleStageBinder* binder = nullptr;
    if (GameScene::sInstance3->_288)
        binder = new (GameScene::sInstance3->_288, 8) TitleStageBinder;
    binder->_10.mEnvArchive = GameScene::sInstance3->getEnvArchive();
    binder->_10._1c = a1;
    setForceEnableGlidingSurfingRupee(false);
    GameScene::sIsOpenWorldDemo = false;
    if (!a2)
        GameScene::sInstance3->setFadeType(2);
    binder->initAndReportDungeonLeaveEnter();
}

// 0x71007b8ce8 (CSV createViewerStageBinder; mirrors createTitleStageBinder above).
// NON_MATCHING: store order of the inlined ViewerStageArg / binder constructors (same shape as the title version).
void createViewerStageBinder() {
    if (gameSceneHasStageBinder())
        return;
    ViewerStageBinder* binder = nullptr;
    if (GameScene::sInstance3->_288)
        binder = new (GameScene::sInstance3->_288, 8) ViewerStageBinder;
    binder->_10.mEnvArchive = GameScene::sInstance3->getEnvArchive();
    setForceEnableGlidingSurfingRupee(false);
    GameScene::sIsOpenWorldDemo = false;
    binder->initAndReportDungeonLeaveEnter();
}

// 0x71007be380 (placeholder name): creates the open world stage binder (unless there is one) with the given map type
// and flag, and initialises it.
void sub_71007BE380(s32 a1, bool a2) {
    if (GameScene::sInstance3->hasStageBinder())
        return;
    OpenWorldStageBinder* binder = GameScene::sInstance3->createOpenWorldStageBinder();
    binder->_10._8 = GameScene::sInstance3->getEnvArchive();
    binder->_10._1f4 = a1;
    binder->_10._130.clear();
    binder->_10._168.clear();
    binder->_10._18.clear();
    binder->_10._1a0.clear();
    binder->_10._1d8 = false;
    binder->_10._1dc = 0;
    binder->_10._1e0 = 0;
    binder->_10._1e4 = 0;
    binder->_10._1e8 = 0;
    binder->_10._1ec = 0;
    binder->_10._1f0 = 0;
    binder->_10._1fc = a2;
    binder->initAndReportDungeonLeaveEnter();
}

}  // namespace uking
