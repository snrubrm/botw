#include "Game/AI/Action/actionBoomerangMove.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

// 0x71000cb200 (placeholder name): an empty variadic function (a stripped debug-print; BoomerangMove::calc_ calls it
// with ("", &vector, "%f", double)). Byte-identical to xlink2::UserInstance::printLogFadeOrKill.
void sub_71000CB200(const char*, const sead::Vector3f*, const char*, ...) {}

namespace uking::action {

BoomerangMove::BoomerangMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BoomerangMove::~BoomerangMove() = default;

bool BoomerangMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BoomerangMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BoomerangMove::leave_() {
    auto* actor = mActor;
    ksys::phys::RigidBody* body = nullptr;
    if (auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(actor)) {
        auto* weapon_body = static_cast<ksys::phys::RigidBody*>(weapon->m221());
        if (weapon_body && (weapon_body->isAddingBodyToWorld() || weapon_body->isAddedToWorld()))
            body = weapon_body;
    }
    if (!body)
        body = actor->getMainBody();
    if (body) {
        body->setContactNone();
        body->setGravityFactor(1.0f);
    }
    actor = mActor;
    if (auto* chemical = actor->getChemicalStuff())
        chemical->_14c = _ec;
    ksys::act::disableAttClient(actor, mCatchAttentionName_s);
}

void BoomerangMove::loadParams_() {
    getStaticParam(&mPreCurveTimer_s, "PreCurveTimer");
    getStaticParam(&mRadSpeed_s, "RadSpeed");
    getStaticParam(&mCurveSpeedRate_s, "CurveSpeedRate");
    getStaticParam(&mStraightSpeedRate_s, "StraightSpeedRate");
    getStaticParam(&mCurvePredictFrame_s, "CurvePredictFrame");
    getStaticParam(&mCurveCheckYDist_s, "CurveCheckYDist");
    getStaticParam(&mStraightPredictFrame_s, "StraightPredictFrame");
    getStaticParam(&mStraightCheckYDist_s, "StraightCheckYDist");
    getStaticParam(&mFlyLimitTime_s, "FlyLimitTime");
    getStaticParam(&mCatchAttentionName_s, "CatchAttentionName");
    getStaticParam(&mTargetOffset_s, "TargetOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void BoomerangMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
