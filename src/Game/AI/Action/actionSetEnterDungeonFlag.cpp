#include "Game/AI/Action/actionSetEnterDungeonFlag.h"
#include "Game/gamePlayReport.h"
#include "Game/gameScene.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::action {

SetEnterDungeonFlag::SetEnterDungeonFlag(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetEnterDungeonFlag::~SetEnterDungeonFlag() = default;

bool SetEnterDungeonFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool SetEnterDungeonFlag::oneShot_() {
    ksys::gdt::setDungeonEntered(GameScene::getCurrentMapName(), true);
    reportDungeon(GameScene::getCurrentMapName(), "first");
    return true;
}

void SetEnterDungeonFlag::loadParams_() {}

}  // namespace uking::action
