#include "Game/Actor/Query/queryIsOnEnterDungeonFlag.h"
#include "Game/Scene/gameStageInfo.h"
#include <evfl/Query.h>
#include "Game/Scene/gameScene.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::query {

IsOnEnterDungeonFlag::IsOnEnterDungeonFlag(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsOnEnterDungeonFlag::~IsOnEnterDungeonFlag() = default;

int IsOnEnterDungeonFlag::doQuery() {
    return ksys::gdt::isDungeonEntered(uking::StageInfo::getCurrentMapName(), false);
}

void IsOnEnterDungeonFlag::loadParams(const evfl::QueryArg& arg) {}

void IsOnEnterDungeonFlag::loadParams() {}

}  // namespace uking::query
