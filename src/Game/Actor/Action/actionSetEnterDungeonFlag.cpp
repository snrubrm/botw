#include "Game/Actor/Action/actionSetEnterDungeonFlag.h"
#include "Game/Scene/gameStageInfo.h"
#include "Game/gamePlayReport.h"
#include "Game/Scene/gameScene.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::action {

SetEnterDungeonFlag::SetEnterDungeonFlag(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetEnterDungeonFlag::~SetEnterDungeonFlag() = default;

bool SetEnterDungeonFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool SetEnterDungeonFlag::oneShot_() {
    ksys::gdt::setDungeonEntered(uking::StageInfo::getCurrentMapName(), true);
    reportDungeon(uking::StageInfo::getCurrentMapName(), "first");
    return true;
}

void SetEnterDungeonFlag::loadParams_() {}

}  // namespace uking::action
