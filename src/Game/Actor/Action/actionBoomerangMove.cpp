#include "Game/Actor/Action/actionBoomerangMove.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/System/VFR.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
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

void BoomerangMove::sub_71000CB538(f32 gravity_factor) {
    auto* actor = mActor;
    ksys::phys::RigidBody* body = nullptr;
    if (auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(actor)) {
        auto* weapon_body = static_cast<ksys::phys::RigidBody*>(weapon->m221());
        if (weapon_body && (weapon_body->isAddingBodyToWorld() || weapon_body->isAddedToWorld()))
            body = weapon_body;
    }
    if (!body)
        body = actor->getMainBody();
    if (body)
        body->setGravityFactor(gravity_factor);
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

// NON_MATCHING: accessor teardown branches and fallback vector register allocation.
sead::Vector3f BoomerangMove::m32() {
    sead::Vector3f result;
    bool found = false;
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        ksys::act::ActorLinkConstDataAccess access;
        if (ksys::act::acquireActor(&weapon->_fb8, &access)) {
            const sead::Vector3f offset = *mTargetOffset_s;
            result.setRotated(access.getActorMtx(), offset);
            if (result.y >= 0.0f)
                result.y = result.y < _e8 ? _e8 : result.y;
            result += access.getActorMtx().getTranslation();
            found = true;
        }
    }
    if (!found) {
        result = _a0;
        if (result.y >= 0.0f)
            result.y = result.y < _e8 ? _e8 : result.y;
        result += *mTargetPos_d;
    }
    return result;
}

void sub_71000CB074(sead::Vector3f* dir, sead::Vector3f* target, f32 rate) {
    if (*dir == sead::Vector3f(0, 0, 0) || *target == sead::Vector3f(0, 0, 0)) {
        ksys::VFR::lerp(dir, *target, rate);
        return;
    }
    ksys::util::sub_71011EE6FC(dir, target, ksys::VFR::getLerpFactor(rate));
}

}  // namespace uking::action
