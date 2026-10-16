#include "Game/Actor/actGuardianComponent.h"
#include "Game/Actor/actGuardian.h"
#include <basis/seadNew.h>
#include "Game/Actor/aiUnk_710072BA90.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::act {

// 0x710003c2dc (shared with Unk_710235b408's) / D0 0x710003c2e0: empty.
GuardianComponentBind::~GuardianComponentBind() = default;

// 0x710003c2dc / D0 0x710003c2e4: empty.
Unk_710235b408::~Unk_710235b408() = default;

ksys::act::BaseProc* GuardianComponent::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) GuardianComponent(arg);
}

GuardianComponent::GuardianComponent(const CreateArg& arg) : DynamicActor(arg) {
    if (getName().findIndex("Cannon") != -1)
        _ba0 = 0;
    else if (getName().findIndex("WeakPoint") != -1)
        _ba0 = 1;
    else if (getName().findIndex("BrokenLeg") != -1)
        _ba0 = 3;
    else if (getName().findIndex("Leg") != -1)
        _ba0 = 2;
    else if (getName().findIndex("Propeller") != -1)
        _ba0 = 4;
}

GuardianComponent::~GuardianComponent() = default;

bool GuardianComponent::canWakeUp_() {
    if (!Actor::canWakeUp_())
        return false;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_b90, &accessor);
    return accessor.isStateCalc();
}

void Unk_710235b700::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, DamageCallbackInfo* a6) {
    auto* owner = mOwner;
    if (auto* guardian = owner->sub_710003D2B4())
        guardian->sub_710003B564(a1, a2, a3, a4, a5, a6, sub_710072BA90(owner), owner->_ba0);
}

Guardian* GuardianComponent::sub_710003D2B4() {
    return sead::DynamicCast<Guardian>(_b90.getProc(nullptr, nullptr));
}

ksys::act::Actor* GuardianComponent::m31() {
    return sub_710003D2B4();
}

bool GuardianComponent::m55() {
    return true;
}

bool GuardianComponent::shouldUnload(s32* reason) {
    return false;
}

}  // namespace uking::act
