#include "Game/AI/Action/actionBrightBowSlowFall.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

BrightBowSlowFall::BrightBowSlowFall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BrightBowSlowFall::~BrightBowSlowFall() = default;

bool BrightBowSlowFall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BrightBowSlowFall::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!actor)
        return;
    auto* body = actor->getMainBody();
    if (!body)
        return;
    sead::Matrix34f matrix = sead::Matrix34f::ident;
    ksys::util::sub_71011EFCA8(&matrix, *mInitRotate_s);
    matrix.setTranslation(actor->getMtx().getTranslation());
    actor->mMtx = matrix;
    actor->nullsub_4648();
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EF51C(&axis, &angle, mActor->getMainBody()->getTransform(), matrix,
                             sead::Vector3f::ey);
    if (angle > 0.1f)
        body->setTransform(matrix);
    _c8 = false;
    _c9 = false;
    _cc = 0.0f;
    _d0 = 0.0f;
    _bc = actor->getMtx().getTranslation();
}

void BrightBowSlowFall::leave_() {
    _90.fadeXLink();
}

void BrightBowSlowFall::loadParams_() {
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mFloatWaveCycle_s, "FloatWaveCycle");
    getStaticParam(&mFloatWaveWidth_s, "FloatWaveWidth");
    getStaticParam(&mFloatHeight_s, "FloatHeight");
    getStaticParam(&mFloatSpring_s, "FloatSpring");
    getStaticParam(&mFloatDamper_s, "FloatDamper");
    getStaticParam(&mFallBrakeHeight_s, "FallBrakeHeight");
    getStaticParam(&mFallBrake_s, "FallBrake");
    getStaticParam(&mAttractionRange_s, "AttractionRange");
    getStaticParam(&mAttractionRate_s, "AttractionRate");
    getStaticParam(&mTailEffectKeyName_s, "TailEffectKeyName");
    getStaticParam(&mInitRotate_s, "InitRotate");
    getStaticParam(&mRotateSpeed_s, "RotateSpeed");
}

void BrightBowSlowFall::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
