#include "Game/gameScene.h"
#include "KingSystem/System/StageInfo.h"

namespace uking {

// Internal-linkage globals of the GameScene TU (0x728 / 0x72c / 0x730; the original addresses them
// directly, not through the GOT).
static bool sSceneStartEventReady;
static bool sIsTransitionFromFarActorDone;
static bool sIsStageUnloaded;

bool GameScene::sIsOpenWorldDemo{};
GameScene* GameScene::sInstance;
bool GameScene::sIsInitialisingStage;
GameScene* GameScene::sInstance2;
GameScene* GameScene::sInstance3;
bool GameScene::sFlag;

bool GameScene::getIsInitialisingStage() {
    return sIsInitialisingStage;
}

void GameScene::setInstance2() {
    sInstance2 = sInstance;
}

void GameScene::setInstance3() {
    sInstance3 = sInstance;
}

bool sceneStartEventReady() {
    return sSceneStartEventReady;
}

void setSceneStartEventReady() {
    sSceneStartEventReady = true;
}

void setSceneStartEventNotReady() {
    sSceneStartEventReady = false;
}

bool isTransitionFromFarActorDone() {
    return sIsTransitionFromFarActorDone;
}

void setIsTransitionFromFarActorDone(bool value) {
    sIsTransitionFromFarActorDone = value;
}

bool getIsStageUnloaded() {
    return sIsStageUnloaded;
}

void setIsStageUnloaded(bool value) {
    sIsStageUnloaded = value;
}

void gameSceneSetFlag(bool value) {
    GameScene::sFlag = value;
}

bool gameSceneGetFlag() {
    return GameScene::sFlag;
}

bool isGameSceneInitialized() {
    return GameScene::sInstance3 != nullptr;
}

const sead::SafeString& GameScene::getCurrentMapType() {
    return ksys::StageInfo::getCurrentMapType();
}

const sead::SafeString& GameScene::getCurrentMapName() {
    return ksys::StageInfo::getCurrentMapName();
}

bool GameScene::ret0() {
    return false;
}

void GameScene::m11_null() {}

void GameScene::StageMgrEnter() {}

void GameScene::StageMgrLeave() {}

bool GameScene::StageMgrReenter() {
    return false;
}

void GameScene::PatchErrorRun() {}

void GameScene::PatchErrorLeave() {}

bool GameScene::PatchErrorReenter() {
    return false;
}

void GameScene::StageSelectLeave() {}

bool GameScene::StageSelectReenter() {
    return false;
}

void GameScene::setFadeType(s32 type) {
    _93c = type;
}

bool GameScene::hasStageBinder() const {
    return _2a8 != nullptr;
}

void GameScene::LunchTitleLeave() {}

bool GameScene::LunchTitleReenter() {
    return false;
}

void GameScene::StageTransitionEnter() {}

void GameScene::StageTransitionRun() {}

void GameScene::StageTransitionLeave() {}

bool GameScene::StageTransitionReenter() {
    return false;
}

bool GameScene::NewSaveReenter() {
    return false;
}

void GameScene::setStageBinder(StageBinder* binder) {
    if (_2a8)
        return;
    _2a8 = binder;
    _279 |= 1;
}

}  // namespace uking
