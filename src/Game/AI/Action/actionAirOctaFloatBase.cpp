#include "Game/AI/Action/actionAirOctaFloatBase.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/AI/AirOcta/AirOctaDataMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

AirOctaFloatBase::AirOctaFloatBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirOctaFloatBase::~AirOctaFloatBase() = default;

bool AirOctaFloatBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AirOctaFloatBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = sead::GlobalRandom::instance()->getF32() * sead::Mathf::pi();
    _44 = 0.0f;
    _1c0 &= ~1;
    _70.setName("Neck");
    _118.setName("Head_2");
    mActor->boneHandleStuff(&_70, false);
    mActor->boneHandleStuff(&_118, false);
}

void AirOctaFloatBase::leave_() {
    mActor->sub_71011DA868(&_70);
    mActor->sub_71011DA868(&_118);
}

void AirOctaFloatBase::loadParams_() {
    getStaticParam(&mAmplitude_s, "Amplitude");
    getStaticParam(&mGoalDistance_s, "GoalDistance");
    getStaticParam(&mGoalInSuccessEnd_s, "GoalInSuccessEnd");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

void AirOctaFloatBase::calc_() {
    m32();
    sub_7100088400();
    sub_71000885B0();
    sub_71000886B8();
    _40 += ksys::VFR::instance()->getDeltaTime();
}

AirOctaDataMgr* AirOctaFloatBase::sub_7100088DA8() {
    return sead::DynamicCast<AirOctaDataMgr>(*mAirOctaDataMgr_a);
}

// NON_MATCHING: block layout of the `_44 >= 1.0f` branch and where &_1c0 is computed differ.
bool AirOctaFloatBase::sub_7100088400() {
    auto* manager = sead::DynamicCast<AirOctaDataMgr>(*mAirOctaDataMgr_a);
    if (!manager)
        return false;
    const f32 delta_time = ksys::VFR::instance()->getDeltaTime();
    if ((manager->vec_F8 - mActor->getMtx().getTranslation()).length() <= *mGoalDistance_s) {
        _44 += delta_time;
        if (_44 >= 1.0f) {
            _1c0 |= 1;
            if (*mGoalInSuccessEnd_s)
                setFinished();
        }
    } else {
        _44 = 0.0f;
        _1c0 &= ~1;
    }
    return _1c0 & 1;
}

void AirOctaFloatBase::sub_71000885B0() {
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    sead::Vector3f velocity;
    body->getAngularVelocity(&velocity);
    velocity *= 0.65f;
    sead::Vector3f min, max;
    m33(&min, &max);
    velocity.x = sead::Mathf::clamp2(min.x, velocity.x, max.x);
    velocity.y = sead::Mathf::clamp2(min.y, velocity.y, max.y);
    velocity.z = sead::Mathf::clamp2(min.z, velocity.z, max.z);
    body->setAngularVelocity(velocity);
}

void AirOctaFloatBase::m33(sead::Vector3f* min, sead::Vector3f* max) {
    min->set(-3.0f, -3.0f, -3.0f);
    max->set(3.0f, 3.0f, 3.0f);
}

f32 AirOctaFloatBase::m34() {
    return *mAmplitude_s;
}

}  // namespace uking::action
