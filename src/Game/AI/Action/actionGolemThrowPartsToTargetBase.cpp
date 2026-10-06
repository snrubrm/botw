#include "Game/AI/Action/actionGolemThrowPartsToTargetBase.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

GolemThrowPartsToTargetBase::GolemThrowPartsToTargetBase(const InitArg& arg) : ActionWithAS(arg) {}

GolemThrowPartsToTargetBase::~GolemThrowPartsToTargetBase() = default;

bool GolemThrowPartsToTargetBase::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void GolemThrowPartsToTargetBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    setDamageCallbackTiming(mActor, 4, &_f0);
    mFlags.reset(Flag::Changeable);
}

void GolemThrowPartsToTargetBase::leave_() {
    sub_710018D8DC();
    sub_71005DA114(mActor, &_f0);
    ActionWithPosAngReduce::leave_();
}

void GolemThrowPartsToTargetBase::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mTgtBodyName_s, "TgtBodyName");
    getStaticParam(&mChmObjectName_s, "ChmObjectName");
    _60.sub_71005E1BE8(this, 0);
    _a0.sub_71005E1BE8(this, 1);
    _e0 = false;
    _e1 = false;
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

void GolemThrowPartsToTargetBase::calc_() {
    ActionWithAS::calc_();
    sub_710018D8DC();
    if (auto* as_list = mActor->getASList()) {
        if (as_list->x(71, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
            sub_710018D998();
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

// NON_MATCHING: the original tests the three out/in pointers with cset/and (non-short-circuit) and only body with cbz; the natural short-circuit form branches per pointer.
void GolemThrowPartsToTargetBase::m32(sead::Vector3f* linear_velocity,
                                      sead::Vector3f* angular_velocity, sead::Matrix34f* mtx,
                                      ksys::phys::RigidBody* body) {
    if (body && linear_velocity && angular_velocity && mtx) {
        body->getTransform(mtx);
        *angular_velocity = body->getAngularVelocity() * (1.0f / 30.0f);
        *linear_velocity = body->getLinearVelocity() * (1.0f / 30.0f);
    }
}

}  // namespace uking::action
