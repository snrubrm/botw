#include "Game/Actor/Action/actionAvoidingCloseMoveBase.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: store ordering/merging of the zero-initialised members (original merges 0x88-0x97 into one stp)
AvoidingCloseMoveBase::AvoidingCloseMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AvoidingCloseMoveBase::~AvoidingCloseMoveBase() = default;

bool AvoidingCloseMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the timer stores merge as (value) + (previous, rate) in the original, (value, previous) + (rate) in ours
void AvoidingCloseMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _58.x = 0.0f;
    _58.y = 0.0f;
    _58.z = 0.0f;
    sub_7100741034(&_64, actor);
    _88 = sead::Mathf::clampMax(actor->getAngVelocity().length(), *mParams.mRotSpd_s);
    mFlags.set(Flag::Changeable);
    _8c.reset(6.0f);
}

void AvoidingCloseMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void AvoidingCloseMoveBase::loadParams_() {
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mSpeed_s, "Speed");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getStaticParam(&mParams.mFinRadius_s, "FinRadius");
    getStaticParam(&mParams.mFinRotate_s, "FinRotate");
    getStaticParam(&mParams.mBaseRotRatio_s, "BaseRotRatio");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void AvoidingCloseMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

ksys::act::Unk_7100d78e50* AvoidingCloseMoveBase::m33(int idx) {
    return nullptr;
}

bool AvoidingCloseMoveBase::m34(ksys::act::Unk_7100d78e50* entry) {
    return false;
}

f32 AvoidingCloseMoveBase::m35() {
    return *mParams.mSpeed_s;
}

void AvoidingCloseMoveBase::m36(const sead::Matrix34f& mtx) {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5FC8C(mtx);
}

bool AvoidingCloseMoveBase::m37(ksys::phys::CharacterController* controller, f32 speed,
                            const sead::Vector3f& dir) {
    return true;
}

bool AvoidingCloseMoveBase::m39() {
    auto* actor = mActor;
    if (!actor)
        return false;

    sead::Vector3f dir;
    actor->getMtx().getBase(dir, 2);
    dir.normalize();
    if (!isLandedMaybe(actor, false))
        return false;
    return dir.dot(sub_71007A471C(actor, 0)->_c) < 0.0f;
}

int AvoidingCloseMoveBase::m38(f32 distance) {
    auto* actor = mActor;
    if (!actor)
        return 1;

    sead::Vector3f dir;
    dir = actor->getVelocity();
    dir.y = 0.0f;
    dir.normalize();
    sead::Vector3f front;
    actor->getMtx().getBase(front, 2);
    front.normalize();
    if (front.dot(dir) >= 0.9659258f) {
        bool flag = false;
        if (sub_710072FEC4(actor, dir, sead::Mathf::min(distance, 2.0f), nullptr, false, &flag))
            return 0;
        return flag ? 2 : 1;
    }
    return 1;
}

}  // namespace uking::action
