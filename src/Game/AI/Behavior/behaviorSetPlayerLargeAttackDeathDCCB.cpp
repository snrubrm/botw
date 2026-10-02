#include "Game/AI/Behavior/behaviorSetPlayerLargeAttackDeathDCCB.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::behavior {

SetPlayerLargeAttackDeathDCCB::SetPlayerLargeAttackDeathDCCB(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetPlayerLargeAttackDeathDCCB::~SetPlayerLargeAttackDeathDCCB() = default;

bool SetPlayerLargeAttackDeathDCCB::m6(sead::Heap* heap) {
    return SetDamageCallback::m6(heap);
}

void SetPlayerLargeAttackDeathDCCB::m7() {
    SetDamageCallback::m7();
}

void SetPlayerLargeAttackDeathDCCB::m8() {
    SetDamageCallback::m8();
}

void SetPlayerLargeAttackDeathDCCB::m9() {
    SetDamageCallback::m9();
}

void SetPlayerLargeAttackDeathDCCB::loadParams() {
    SetDamageCallback::loadParams();
}

uking::dmg::DamageCallback* SetPlayerLargeAttackDeathDCCB::m14() {
    return &_30;
}

void Unk_7102439db0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 < 15)
        return;
    auto* manager = sead::DynamicCast<dmg::DamageManager>(mDamageManager);
    if (!manager)
        return;
    ksys::act::acc::PlayerBase accessor;
    ksys::act::acquireActor(manager->getAttacker(), &accessor);
    if (accessor.x_26()) {
        *a1 = 1;
        *a5 = 30;
    }
}

}  // namespace uking::behavior
