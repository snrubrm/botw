#include "Game/Actor/Behavior/behaviorSetPlayerLargeAttackDeathDCCB.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actBaseProcAccessor.h"

namespace uking::behavior {

SetPlayerLargeAttackDeathDCCB::SetPlayerLargeAttackDeathDCCB(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetPlayerLargeAttackDeathDCCB::~SetPlayerLargeAttackDeathDCCB() = default;

bool SetPlayerLargeAttackDeathDCCB::init_(sead::Heap* heap) {
    return SetDamageCallback::init_(heap);
}

void SetPlayerLargeAttackDeathDCCB::calc() {
    SetDamageCallback::calc();
}

void SetPlayerLargeAttackDeathDCCB::enter() {
    SetDamageCallback::enter();
}

void SetPlayerLargeAttackDeathDCCB::leave() {
    SetDamageCallback::leave();
}

void SetPlayerLargeAttackDeathDCCB::loadParams() {
    SetDamageCallback::loadParams();
}

uking::act::DamageCallback* SetPlayerLargeAttackDeathDCCB::m14() {
    return &_30;
}

void Unk_7102439db0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::act::DamageCallbackInfo* a6) {
    if (*a5 < 15)
        return;
    auto* manager = sead::DynamicCast<act::DamageManager>(mDamageManager);
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
