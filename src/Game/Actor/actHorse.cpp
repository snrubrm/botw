#include "Game/Actor/actHorse.h"
#include <basis/seadNew.h>
#include "Game/Actor/actRideable.h"
#include "KingSystem/Ecosystem/ecoSystem.h"

// Declaration only; the original helper's source owner and namespace are unknown.
void sub_7100D2D424(uking::dmg::DamageManagerBase* manager);

namespace uking::act {

Horse::Horse(const CreateArg& arg) : HorseBase(arg) {}

ksys::act::BaseProc* Horse::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Horse(arg);
}

// NON_MATCHING: member types incomplete (DamageManager, Unk_710244dd20)
Horse::~Horse() = default;

void Horse::onPreDeleteStart_(PrepareArg& arg) {
    HorseBase::onPreDeleteStart_(arg);
}

void Horse::preDelete2_(const PreDeleteArg& arg) {
    HorseBase::preDelete2_(arg);
    _c58.free();
    _cd8.m6();
    _f50.sub_71006ECD08();
    sub_7100D2D424(&_d20);
    // called through a pointer in the original (not devirtualised)
    (&_d20)->preDelete1();
    (&_d20)->preDelete2();
}

// NON_MATCHING: operands of the `and` swapped (the original ANDs the loaded bits with the mask), as in
// HorseBase::sub_7100E6BE40
void Horse::onEnterSleep_() {
    HorseBase::onEnterSleep_();
    if (_11a8.isOnBit(Flag(Flag::_0))) {
        _d20.removeDamageCallback(&_1170);
        _11a8.resetBit(Flag(Flag::_0));
    }
}

// NON_MATCHING: the original calls m10 virtually (probably an inline member of Unk_71025ae680)
void Horse::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    if (sub_7100E68270())
        return;
    if ((_1028._a & 3) == 0)
        _1028.m10();
    _1028._a &= ~0x24;
    m149();
}

void Horse::m73() {
    _1028.m7();
}

bool Horse::m50() {
    if (Actor::m50())
        return true;
    if (auto* rideable = getHorseOptionsMaybe()) {
        auto* actor = rideable->sub_7100E8B6E0();
        if (actor && actor->m50())
            return true;
    }
    return false;
}

void Horse::loadReduceAncientEnemyDamageInfo() {
    ksys::eco::StatusEffectInfo info;
    const int level = (_b70 >> 9 & 1) + (_b70 >> 10 & 1);
    ksys::eco::Ecosystem::instance()->getStatusEffectInfo(
        ksys::eco::StatusEffect_ReduceAncientEnemyDamge, level, &info);
    _d20._74 = info.val._s32;
}

bool Horse::m81(const ksys::Message& message) {
    if (HorseBase::m81(message))
        return true;
    return _1028.m8(message);
}

}  // namespace uking::act
