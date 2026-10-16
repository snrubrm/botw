#include "Game/Actor/actGuardianComponent.h"
#include "Game/Actor/actGuardian.h"
#include <basis/seadNew.h>
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/aiUnk_7102451120.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
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

void GuardianComponent::m63() {
    if (auto* awareness = getAwareness())
        awareness->enable();
    if (auto* physics = getPhysics()) {
        const s32 idx = physics->findContactPointInfo("Ground");
        _bb0 = idx < 0 ? nullptr : physics->getContactPointInfoAt(idx);
        if (_bb0) {
            _bb0->setAllLayerMask2();
            _bb0->set2c(1);
        }
    }
    DynamicActor::m63();
    _ba8->m9();
}

void GuardianComponent::updatePositionMaybe() {
    if (auto* guardian = sub_710003D2B4()) {
        auto* life = guardian->getLife();
        if (life && *life <= 0)
            sub_710073DE08(this);
    }
    if (!mActorFlags2.isOn(ActorFlag2::_40) && _ba8)
        _ba8->m12();
    DynamicActor::updatePositionMaybe();
}

// NON_MATCHING: the two inlined indexOf loops keep their -1 result in a register set before the loop.
// Adds the owning Guardian to `actors` when this component is in it.
void GuardianComponent::m147(sead::PtrArray<ksys::act::Actor>* actors) {
    ksys::act::Actor* guardian = sub_710003D2B4();
    if (actors->indexOf(this) >= 0 && actors->indexOf(guardian) < 0)
        actors->pushBack(guardian);
}

// NON_MATCHING: block order (the original places the null return last).
// The owning Guardian's (CSV m136).
ksys::act::LifeRecoverInfo* GuardianComponent::getLifeRecoverInfo() {
    return sub_710003D2B4() ? sub_710003D2B4()->getLifeRecoverInfo() : nullptr;
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
