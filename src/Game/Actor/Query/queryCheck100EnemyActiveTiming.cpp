#include "Game/Actor/Query/queryCheck100EnemyActiveTiming.h"
#include "Game/Scene/gameStageInfo.h"
#include <evfl/Query.h>
#include "KingSystem/AOC/aocManager.h"
#include "Game/Scene/gameScene.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::query {

Check100EnemyActiveTiming::Check100EnemyActiveTiming(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

Check100EnemyActiveTiming::~Check100EnemyActiveTiming() = default;

int Check100EnemyActiveTiming::doQuery() {
    if (uking::StageInfo::getCurrentMapType() != "MainField")
        return 0;
    if (!ksys::aoc::Manager::instance()->hasAoc2())
        return 0;
    if (ksys::gdt::getFlag_100enemy_Activated())
        return 0;
    if (!ksys::gdt::getFlag_IsGet_Weapon_Sword_070())
        return 0;
    if (ksys::gdt::getFlag_IsPlayed_Demo146_0())
        return 0;
    sead::Vector3f pos = sead::Vector3f::zero;
    if (!ksys::act::ActorSystem::instance()->getPlayerPosition(&pos))
        return 0;
    return ksys::eco::Ecosystem::instance()->getFieldMapArea(pos.x, pos.z) == 14 ? 2 : 1;
}

void Check100EnemyActiveTiming::loadParams(const evfl::QueryArg& arg) {}

void Check100EnemyActiveTiming::loadParams() {}

}  // namespace uking::query
