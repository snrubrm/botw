#include "Game/AI/AI/aiStoneOctarockBattle.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

StoneOctarockBattle::StoneOctarockBattle(const InitArg& arg) : ShootingEnemyBattle(arg) {}

StoneOctarockBattle::~StoneOctarockBattle() = default;

bool StoneOctarockBattle::init_(sead::Heap* heap) {
    return ShootingEnemyBattle::init_(heap);
}

void StoneOctarockBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ShootingEnemyBattle::enter_(params);
}

void StoneOctarockBattle::calc_() {
    ShootingEnemyBattle::calc_();
}

void StoneOctarockBattle::leave_() {
    ShootingEnemyBattle::leave_();
}

void StoneOctarockBattle::loadParams_() {
    ShootingEnemyBattle::loadParams_();
}

// NON_MATCHING: regalloc (the original rematerialises the filter address instead of keeping it in x20)
bool StoneOctarockBattle::m39() {
    if (ShootingEnemyBattle::m39())
        return true;

    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;
    auto* sensor = awareness->_260[0];
    if (!sensor || !sensor->_8.isBufferReady() || sensor->_8.size() < 1)
        return false;
    auto* entry = ksys::act::sub_7100D78E30(&sensor->_8, 0);
    if (entry->_a0 == 0 || entry->_a0 == 1)
        return false;

    Unk_7102451538 filter;
    if (!awareness->_260[0])
        return false;
    return ksys::act::sub_7100D7EEE8(&awareness->_260[0]->_8, &filter) != nullptr;
}

}  // namespace uking::ai
