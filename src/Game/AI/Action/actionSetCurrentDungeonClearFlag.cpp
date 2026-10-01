#include "Game/AI/Action/actionSetCurrentDungeonClearFlag.h"
#include "Game/gamePlayReport.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/System/StageInfo.h"

namespace uking::action {

SetCurrentDungeonClearFlag::SetCurrentDungeonClearFlag(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetCurrentDungeonClearFlag::~SetCurrentDungeonClearFlag() = default;

bool SetCurrentDungeonClearFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool SetCurrentDungeonClearFlag::oneShot_() {
    ksys::gdt::setDungeonCleared(ksys::StageInfo::getCurrentMapName(), true);
    reportDungeon(ksys::StageInfo::getCurrentMapName(), "clear");
    return true;
}

void SetCurrentDungeonClearFlag::loadParams_() {}

}  // namespace uking::action
