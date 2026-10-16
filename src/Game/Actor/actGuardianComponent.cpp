#include "Game/Actor/actGuardianComponent.h"
#include "Game/Actor/actGuardian.h"
#include <basis/seadNew.h>
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/aiUnk_7102451120.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::act {

// 0x710003c2dc (shared with Unk_710235b408's) / D0 0x710003c2e0: empty.
GuardianComponentBind::~GuardianComponentBind() = default;

// 0x710003c2dc / D0 0x710003c2e4: empty.
Unk_710235b408::~Unk_710235b408() = default;

bool Unk_710235b408::m6() {
    return true;
}

void Unk_710235b408::m7(const ksys::act::BaseProc::PreDeleteArg&) {}

void Unk_710235b408::m8() {}

// Follows the owning Guardian's matrix.
void Unk_710235b408::m9() {
    if (auto* guardian = _8->sub_710003D2B4())
        _8->setMatrix(guardian->getMtx(), &sead::Vector3f::ones);
}

void Unk_710235b408::m13() {}

void GuardianComponentBind::m9() {}

void GuardianComponentBind::m10() {}

void GuardianComponentBind::m11() {}

void GuardianComponentBind::m12() {}

void GuardianComponentBind::m14() {}

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

void GuardianComponent::preDelete2_(const PreDeleteArg& arg) {
    sub_71005DA114(this, &mDamageCallback);
    if (_ba8) {
        _ba8->m7(arg);
        delete _ba8;
        _ba8 = nullptr;
    }
    DynamicActor::preDelete2_(arg);
}

void GuardianComponent::initMaybe() {
    DynamicActor::initMaybe();
    sub_71005DDA44(this);
    _ba8->m10();
    setDamageCallbackTiming(this, 0, &mDamageCallback);
}

void GuardianComponent::updateMtxFromPhysics() {
    _ba8->m13();
}

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
