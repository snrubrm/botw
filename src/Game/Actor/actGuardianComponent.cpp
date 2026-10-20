#include "Game/Actor/actGuardianComponent.h"
#include "Game/Actor/actGuardian.h"
#include <basis/seadNew.h>
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/aiUnk_7102451120.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/gameStasisMgr.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::act {

// 0x710003c2dc (shared with Unk_710235b408's) / D0 0x710003c2e0: empty.
GuardianComponentBind::~GuardianComponentBind() = default;

// 0x710003c2dc / D0 0x710003c2e4: empty.
Unk_710235b408::~Unk_710235b408() = default;

bool Unk_710235b408::m6(sead::Heap*) {
    return true;
}

void Unk_710235b408::m7(const ksys::act::BaseProc::PreDeleteArg&) {}

void Unk_710235b408::m8(ksys::act::BaseProc*) {}

// Follows the owning Guardian's matrix.
void Unk_710235b408::m9() {
    if (auto* guardian = _8->sub_710003D2B4())
        _8->setMatrix(guardian->getMtx(), &sead::Vector3f::ones);
}

void Unk_710235b408::m13() {}

// NON_MATCHING: the original writes _28 and the key through the new pointer without reloading mBind.
bool GuardianWeakPointPart::m6(sead::Heap* heap) {
    if (!mBind) {
        mBind = new (heap) ksys::act::ModelBindInfo;
        mBind->_28 = "Body";
        mBind->_30.getKey() = {};
        mBind->_68 = sead::Matrix34f::ident;
        mBind->_98 = 3;
        _8->sub_71011DA824(mBind);
    }
    return true;
}

void GuardianWeakPointPart::m7(const ksys::act::BaseProc::PreDeleteArg&) {
    if (mBind) {
        _8->sub_71011DA834(mBind);
        delete mBind;
        mBind = nullptr;
    }
}

void GuardianWeakPointPart::m8(ksys::act::BaseProc* proc) {
    if (mBind)
        mBind->x(proc);
}

// Follows the owning Guardian's matrix.
void GuardianWeakPointPart::m9() {
    if (auto* guardian = _8->sub_710003D2B4())
        _8->setMatrix(guardian->getMtx(), &sead::Vector3f::ones);
}

void GuardianWeakPointPart::m13() {}

void Unk_710235b5e8::m7(const ksys::act::BaseProc::PreDeleteArg&) {
    if (_30) {
        ksys::phys::Constraint::destroy(_30);
        _30 = nullptr;
    }
    if (_38) {
        ksys::phys::Constraint::destroy(_38);
        _38 = nullptr;
    }
}

void Unk_710235b5e8::m10() {}

// NON_MATCHING: the original loads _8 once after getTransform and keeps it for the nullsub_4648 call.
void Unk_710235b5e8::m13() {
    _8->mMtx = _20->getTransform();
    _8->nullsub_4648();
}

// Fixes both leg bodies while the Guardian is in state 12.
void Unk_710235b5e8::m11() {
    if (auto* guardian = _8->sub_710003D2B4()) {
        if (_28)
            _28->changeMotionType(guardian->_14d8 == 12 ? ksys::phys::MotionType::Fixed :
                                                          ksys::phys::MotionType::Dynamic);
        if (_20)
            _20->changeMotionType(guardian->_14d8 == 12 ? ksys::phys::MotionType::Fixed :
                                                          ksys::phys::MotionType::Dynamic);
    }
}

Unk_710235b660::~Unk_710235b660() = default;

void Unk_710235b660::m7(const ksys::act::BaseProc::PreDeleteArg&) {}

void Unk_710235b660::m13() {}

void Unk_710235b660::m14() {}

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

void GuardianComponent::m36(const sead::Vector3f&, const sead::Vector3f&, bool, bool, bool) {}

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

// CSV m69. While linked to its Guardian, mirrors the Guardian's stasis flag 0x10 and state 12 (into the damage
// manager) and runs the bind's m11; without a Guardian, flags the drop data and deletes itself.
void GuardianComponent::calcMaybe() {
    DynamicActor::calcMaybe();
    if (!_b90.hasProc()) {
        if (auto* drop = sead::DynamicCast<ksys::act::DropData>(getDropData()))
            drop->_c |= 1;
        if (!isDeletedOrDeleting())
            deleteAndEmit(0);
        return;
    }

    Guardian* guardian = sub_710003D2B4();
    if (guardian && guardian->getStasisFlags().getDirect() & 0x10)
        sub_71011D0204(0x10);
    else
        sub_71011D0228(0x10);
    auto* damage_mgr = getDamageMgr();
    if (guardian && damage_mgr)
        damage_mgr->mField_34 = guardian->_14d8 == 12;
    mActorFlags2.set(ActorFlag2::_1000000);
    if (_ba8)
        _ba8->m11();
}

// NON_MATCHING: the original tests 0x3000006 before 0x3000005; our switch lowering tests them in ascending order.
// CSV m81. Stasis messages 0x3000003 / 0x3000004 go to the owning Guardian (unless the Guardian flag bit 7
// is set); 0x3000005 / 0x3000006 set / clear the damage callback's bit 0.
bool GuardianComponent::m81(const ksys::Message& message) {
    switch (message.getType()) {
    case 0x3000003:
    case 0x3000004:
        if (auto* guardian = sub_710003D2B4()) {
            if (guardian->sub_71000380A8()) {
                ksys::act::ActorSystem::instance()->getStasisMessageSender()->sendMessage(
                    guardian, message.getType(), true);
            }
        }
        return true;
    case 0x3000006:
        mDamageCallback._30 &= ~1;
        return true;
    case 0x3000005:
        mDamageCallback._30 |= 1;
        return true;
    default:
        break;
    }
    return DynamicActor::m81(message);
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
