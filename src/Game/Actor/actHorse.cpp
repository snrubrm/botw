#include "Game/Actor/actHorse.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/Ecosystem/ecoSystem.h"

namespace uking::act {

Horse::Horse(const CreateArg& arg) : HorseBase(arg) {}

// NON_MATCHING: member types incomplete (DamageManager, Unk_710244dd20)
Horse::~Horse() = default;

void Horse::onPreDeleteStart_(PrepareArg& arg) {
    HorseBase::onPreDeleteStart_(arg);
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
