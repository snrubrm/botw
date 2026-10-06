#include "Game/AI/Action/actionExplode.h"
#include "KingSystem/System/VFR.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"

namespace uking::action {

Explode::Explode(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Explode::~Explode() {
    if (_60) {
        delete _60;
        _60 = nullptr;
    }
}

bool Explode::init_(sead::Heap* heap) {
    _60 = new (heap) ksys::act::AttackSensor(mActor);
    return _60 != nullptr;
}

void Explode::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Explode::leave_() {
    if (_58)
        sub_71007A2D34(_58);
    if (*mIsDelete_s)
        return;
    if (auto* physics = mActor->getPhysics()) {
        physics->sub_7100FBADDC();
        physics->sub_7100FBB29C();
    }
}

void Explode::loadParams_() {
    getStaticParam(&mSizeUpTime_s, "SizeUpTime");
    getStaticParam(&mExplodeTime_s, "ExplodeTime");
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mUseDefaultEffect_s, "UseDefaultEffect");
    getStaticParam(&mIsDelete_s, "IsDelete");
    getStaticParam(&mIsDamageGuarantee_s, "IsDamageGuarantee");
    getStaticParam(&mIsVanish_s, "IsVanish");
}

// NON_MATCHING: the original loads mActor through the pre-indexed _68 pointer (`ldur x20, [x8, #-0x60]`), ours with `ldr x20, [x19, #8]`
void Explode::calc_() {
    if (!_58) {
        setFailed();
        return;
    }

    if (_68.value <= sead::Mathf::epsilon()) {
        auto* actor = mActor;
        sub_71007A2D34(_58);
        if (actor->getConnectedCalcParent())
            actor->resetConnectedCalcParent(false);
        if (*mIsDelete_s)
            callDeleteAndCreateDropAndEmit(actor, 0);
        setFinished();
        return;
    }

    _68.update();
    ksys::VFR::chase(&_78, _74, _7c);
    _58->setRadius(_78);
}

ksys::phys::SphereRigidBody* Explode::m32() {
    auto* set = mActor->getPhysics()->findBodyByName(*sub_71007A24BC());
    if (!set)
        return nullptr;
    return sead::DynamicCast<ksys::phys::SphereRigidBody>(set->findBodyByHavokName("AtkExplode"));
}

void Explode::m33() {
    _58 = m32();
    if (!_58)
        return;

    m34(_60);
    _58->setUserTag(_60);
    _74 = _58->getRadius();
    f32 step = _74;
    if (*mSizeUpTime_s != 0)
        step = _74 / *mSizeUpTime_s;
    _7c = step;
    _58->setTransform(mActor->getMtx());
    _78 = 0.001f;
    _58->setRadius(0.001f);
    sub_71007A2B64(_58, nullptr);
}

u32 Explode::sub_710012B058() {
    u32 type;
    switch (*mAttackIntensity_s) {
    case 1:
        type = 1;
        break;
    case 2:
        type = 2;
        break;
    case 3:
        type = 4;
        break;
    default:
        type = 0;
        break;
    }
    if (*mIsDamageGuarantee_s)
        type |= 0x10000000;
    return type;
}

}  // namespace uking::action
