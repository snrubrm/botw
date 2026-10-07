#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

// Accessor-based wrappers in the Enemy TU (0x710001a79c-0x710001abb4; lane4 s44; placeholder names, the CSV has none):
// they cast the accessor's proc to an Enemy (false without one). Own file: the AI callers are in other TUs.

// inline-only in the original; name is a guess (same helper as in acc::Weapon / acc::Armor).
static ksys::act::BaseProc* getProcIfActor(ksys::act::BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<ksys::act::Actor>(proc))
        return proc;
    return nullptr;
}

static inline uking::act::Enemy* getEnemy(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = static_cast<ksys::act::Actor*>(getProcIfActor(accessor.getProc()));
    return sead::DynamicCast<uking::act::Enemy>(actor);
}

// 0x710001a79c: `other` has the enemy's target link (`_c48._8`) as its proc.
bool sub_710001A79C(const ksys::act::ActorConstDataAccess& accessor, const ksys::act::ActorConstDataAccess& other) {
    auto* enemy = getEnemy(accessor);
    return enemy ? other.hasProc(enemy->_c48._8) : false;
}

// 0x710001a8a0: `link` is the enemy's target link.
bool sub_710001A8A0(const ksys::act::ActorConstDataAccess& accessor, const ksys::act::BaseProcLink& link) {
    auto* enemy = getEnemy(accessor);
    return enemy ? link == enemy->_c48._8 : false;
}

// 0x710001a9a4: `proc` is the proc of the enemy's target link.
bool sub_710001A9A4(const ksys::act::ActorConstDataAccess& accessor, ksys::act::BaseProc* proc) {
    auto* enemy = getEnemy(accessor);
    return enemy ? enemy->_c48._8.hasProcById(proc) : false;
}

// 0x710001aaa8: the enemy has the part actor `name`.
bool sub_710001AAA8(const ksys::act::ActorConstDataAccess& accessor, const sead::SafeString& name) {
    auto* enemy = getEnemy(accessor);
    return enemy ? enemy->_1128.getActorPartsActor(name).hasProc() : false;
}

void sub_71002D36C8(uking::act::Enemy* enemy, const sead::SafeString& name) {
    if (!enemy || !enemy->_1128.getActorPartsActor(name).hasProc())
        return;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&enemy->_1128.getActorPartsActor(name), &accessor);
    accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}
