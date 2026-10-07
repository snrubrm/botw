#include "Game/AI/AI/aiPriestBossPhaseFourth.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

PriestBossPhaseFourth::PriestBossPhaseFourth(const InitArg& arg) : PriestBossPhase(arg) {}

PriestBossPhaseFourth::~PriestBossPhaseFourth() = default;

bool PriestBossPhaseFourth::init_(sead::Heap* heap) {
    return PriestBossPhase::init_(heap);
}

void PriestBossPhaseFourth::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossPhase::enter_(params);
}

void PriestBossPhaseFourth::leave_() {
    PriestBossPhase::leave_();
    auto* unit = sub_7100525A88();
    unit->_98 = 0;
    unit->_198 = 0;
    sub_7100525A88()->sub_7100719ED0();
}

// NON_MATCHING: the original flag-index wrapper emits temporary index stores.
void PriestBossPhaseFourth::calc_() {
    PriestBossPhase::calc_();
    auto* unit = sub_7100525A88();
    if (unit->_248[m38()]._0)
        return;
    _98._10 = getPlayerPosition();
    _98._328.setBit(0);
    _98.sub_710071CE44();
    _3c8.sub_710071C034();
    sub_710052A63C();
}

void PriestBossPhaseFourth::loadParams_() {
    PriestBossPhase::loadParams_();
    getStaticParam(&mSimAtkMax_s, "SimAtkMax");
    getStaticParam(&mBowEquipMax_s, "BowEquipMax");
    getStaticParam(&mRespawnSpan_s, "RespawnSpan");
}

bool PriestBossPhaseFourth::handleMessage_(const ksys::Message* message) {
    return _3c8.sub_710071C550(*message);
}

bool PriestBossPhaseFourth::m37(f32* x) {
    ksys::act::ActorConstDataAccess accessor;
    if (sub_7100525B18(1, &accessor) && accessor.isStateCalc()) {
        *x = accessor.getLife() / (accessor.getMaxLife() * 0.5f);
        return true;
    }
    return false;
}

}  // namespace uking::ai
