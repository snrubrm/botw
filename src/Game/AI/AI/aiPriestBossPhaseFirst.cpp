#include "Game/AI/AI/aiPriestBossPhaseFirst.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Damage/dmgDamageManagerBase.h"

namespace uking::ai {

// 0x7100529e70
bool PriestBossPhaseFirst::sub_7100529E70(const ksys::act::ActorConstDataAccess& accessor) {
    ksys::act::BaseProcLink link;
    accessor.linkAcquire(&link);
    if (!link.hasProc())
        return false;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(link.getProc(nullptr, nullptr));
    if (!actor)
        return false;
    auto* damage = actor->getDamageMgr();
    return damage && s32(damage->getDamage()) > 0;
}

// NON_MATCHING: natural life division and damage-query inlining differ from the original.
// 0x710052a1c0
void PriestBossPhaseFirst::calc_() {
    PriestBossPhase::calc_();
    ksys::act::ActorConstDataAccess accessor;
    if (!sub_7100525B18(0, &accessor) || !accessor.isStateCalc())
        return;
    const s32 life = accessor.getLife();
    const s32 max_life = accessor.getMaxLife();
    using UnitFlag = Unk_7102450fa8::Flag;
    if (!_7c && f32(life) / f32(max_life) <= 0.5f) {
        _7c = true;
        sub_7100525A88()->_78.setBit(UnitFlag(UnitFlag::_16));
    } else {
        sub_7100525A88()->_78.resetBit(UnitFlag(UnitFlag::_16));
    }
    auto* unit = sub_7100525A88();
    if (sub_7100528C48()) {
        unit->_78.setBit(UnitFlag(UnitFlag::_7));
    } else {
        if (!unit->_78.isOnBit(UnitFlag(UnitFlag::_9))) {
            unit->_78.resetBit(UnitFlag(UnitFlag::_8));
            if (unit->_78.isOnBit(UnitFlag(UnitFlag::_9)))
                unit->_78.resetBit(UnitFlag(UnitFlag::_9));
        }
        unit->_78.resetBit(UnitFlag(UnitFlag::_7));
    }
    if (!sub_7100525A88()->_78.isOnBit(UnitFlag(UnitFlag::_10)) &&
        sub_7100529E70(accessor) &&
        sub_7100525A88()->_78.isOnBit(UnitFlag(UnitFlag::_8))) {
        unit = sub_7100525A88();
        unit->_78.resetBit(UnitFlag(UnitFlag::_8));
        if (unit->_78.isOnBit(UnitFlag(UnitFlag::_9)))
            unit->_78.resetBit(UnitFlag(UnitFlag::_9));
    }
}

PriestBossPhaseFirst::PriestBossPhaseFirst(const InitArg& arg) : PriestBossPhase(arg) {}

PriestBossPhaseFirst::~PriestBossPhaseFirst() = default;

bool PriestBossPhaseFirst::init_(sead::Heap* heap) {
    return PriestBossPhase::init_(heap);
}

void PriestBossPhaseFirst::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossPhase::enter_(params);
    ksys::act::ActorConstDataAccess accessor;
    if (sub_7100525B18(0, &accessor))
        accessor.wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
    else
        setFailed();
    _7c = false;
}

void PriestBossPhaseFirst::leave_() {
    PriestBossPhase::leave_();
    ksys::act::ActorConstDataAccess accessor;
    if (sub_7100525B18(0, &accessor))
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

void PriestBossPhaseFirst::loadParams_() {
    PriestBossPhase::loadParams_();
}

void PriestBossPhaseFirst::m39() {
    ksys::act::ActorConstDataAccess accessor;
    if (sub_7100525B18(0, &accessor))
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

bool PriestBossPhaseFirst::m37(f32* ratio) {
    ksys::act::BaseProcLink link;
    if (!sub_7100525BC0(0, &link))
        return false;

    auto* actor = sead::DynamicCast<ksys::act::Actor>(link.getProc(nullptr, nullptr));
    if (!actor || !actor->isAwakeMaybe())
        return false;

    auto* life = actor->getLife();
    const f32 life_value = life ? f32(*life) : 1.0f;
    *ratio = life_value / f32(actor->getMaxLife());
    return true;
}

bool PriestBossPhaseFirst::m36() {
    ksys::act::ActorConstDataAccess accessor;
    if (sub_7100525B18(0, &accessor))
        return accessor.getLife() == 0;
    return PriestBossPhase::m36();
}

}  // namespace uking::ai
