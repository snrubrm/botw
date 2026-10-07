#include "Game/AI/Action/actionWaterUpDownMoveBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include <prim/seadStringUtil.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"

// Existing water-float utility, 0x71005df820; output is the vertical velocity.
void sub_71005DF820(f32* out, f32 vel_y, f32 depth, f32 float_depth, f32 in_water_depth,
                   f32 radius, f32 cycle_time, f32 change_speed);

namespace uking::action {

WaterUpDownMoveBase::WaterUpDownMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaterUpDownMoveBase::~WaterUpDownMoveBase() = default;

bool WaterUpDownMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterUpDownMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    mFlags.reset(Flag::Changeable);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _74.changeMotionType(controller, ksys::act::MotionType::Hover);
    f32 depth;
    if (mActor->getDepthInWater() > 0.0f)
        depth = mActor->getDepthInWater();
    else
        depth = sub_71002B37F8() - mActor->getMtx().m[1][3];
    _6c = depth - *mInWaterDepth_s;
    _7c._0 = -1.0f;
    _7c._4 = 0.5f;
    _7c.sub_7100700634(mActor);
}

f32 WaterUpDownMoveBase::sub_71002B37F8() {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    sead::Vector3f start;
    mActor->getMtx().getTranslation(start);
    sead::Vector3f end = start;
    end.y -= 10.0f;
    query.setStart(start);
    query.setEnd(end);
    query.enableLayer(ksys::phys::ContactLayer::EntityWater);
    f32 y = 0.0f;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        sead::Vector3f hit;
        query.getHitPosition(&hit);
        y = hit.y;
    }
    return y;
}

void WaterUpDownMoveBase::leave_() {
    _74.resetMotionType(mActor->getCharacterController());
}

void WaterUpDownMoveBase::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mWaterFloatRadius_s, "WaterFloatRadius");
    getStaticParam(&mWaterFloatCycleTime_s, "WaterFloatCycleTime");
    getStaticParam(&mASName_s, "ASName");
}

void WaterUpDownMoveBase::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    auto* as_list = mActor->getASList();
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD5B0(mActor, 0x2f, &query, 0, 0))
        m32(&query);
    if (as_list->x(0x2f, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true))
        m33(controller);
    else
        m34(controller);
    if (isFinishedAS(0, 0))
        setFinished();
    _7c.sub_7100700640(mActor);
}

void WaterUpDownMoveBase::m32(ksys::as::ASList::Unk4* query) {
    f32 depth = 0.0f;
    sead::StringUtil::tryParseF32(&depth, query->name);
    sub_71002B390C(depth, query->_10);
}

// NON_MATCHING: same spline coefficients; floating-point operations and loads are scheduled differently.
void WaterUpDownMoveBase::sub_71002B390C(f32 target_depth, f32 duration) {
    f32 depth;
    if (mActor->getDepthInWater() > 0.0f)
        depth = mActor->getDepthInWater();
    else
        depth = sub_71002B37F8() - mActor->getMtx().m[1][3];
    const f32 distance = depth - *mInWaterDepth_s - target_depth;
    _60 = distance / sead::Mathf::max(1.0f, duration);
    const f32 velocity = mActor->getVelocity().y;
    _64 = *mAccRatio_s * sead::Mathf::abs(_60 - velocity);
    const f32 height = mActor->getMtx().m[1][3];
    _68 = distance + height;
    _6c = target_depth;

    const f32 acceleration = *mAccRatio_s;
    const f32 reduction = 1.0f - *mPosReduceRatio_s;
    const f32 deceleration_time = *mPosReduceRatio_s > 0.0f ? 1.0f / reduction : 0.0f;
    const f32 acceleration_time = sead::Mathf::min(duration, 1.0f / acceleration);
    const f32 final_time = acceleration_time + deceleration_time > duration ?
        duration - acceleration_time : deceleration_time;
    const f32 sign = distance >= 0.0f ? 1.0f : -1.0f;
    const f32 signed_velocity = velocity * sign;
    const f32 time_squared = acceleration_time * acceleration_time;
    const f32 speed =
        (2.0f * sead::Mathf::abs(distance) + time_squared * (signed_velocity * acceleration) -
         (signed_velocity + signed_velocity) * acceleration_time) /
        ((duration + duration - (acceleration_time + acceleration_time) +
          time_squared * acceleration) - reduction * (final_time * final_time));
    const f32 rate = acceleration * (speed - signed_velocity);
    const f32 travel = (duration - acceleration_time - final_time) * speed +
        (signed_velocity * acceleration_time + time_squared * (rate * 0.5f));
    _60 = sign * speed;
    _64 = sead::Mathf::abs(rate);
    _70 = height + (distance >= 0.0f ? travel : -travel);
}

void WaterUpDownMoveBase::m33(ksys::phys::CharacterController* controller) {
    sub_71002B3ACC(controller);
    sub_7100738660(controller, *mRotReduceRatio_s);
}

void WaterUpDownMoveBase::m34(ksys::phys::CharacterController* controller) {
    sub_71002B3F78(controller);
    sub_7100738660(controller, *mRotReduceRatio_s);
}

// NON_MATCHING: the original scales an x/y load pair; this build pairs y/z and forms &velocity.y earlier.
void WaterUpDownMoveBase::sub_71002B3F78(ksys::phys::CharacterController* controller) {
    if (!(_6c > 0.0f)) {
        sub_71007377D4(controller, *mPosReduceRatio_s);
        return;
    }
    sead::Vector3f velocity;
    controller->sub_7100F5F598(&velocity);
    velocity = velocity * (1.0f / 30.0f);
    f32 depth = 0.0f;
    if (mActor->get68f().load()) {
        const f32 height = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - height;
    }
    sub_71005DF820(&velocity.y, velocity.y, depth, _6c, *mInWaterDepth_s,
                   *mWaterFloatRadius_s, *mWaterFloatCycleTime_s, -1.0f);
    const f32 x_ratio = *mPosReduceRatio_s;
    if (x_ratio >= 0.0f)
        velocity.x *= std::pow(x_ratio, ksys::VFR::instance()->getDeltaFrame());
    else
        velocity.x *= -std::pow(-x_ratio, ksys::VFR::instance()->getDeltaFrame());
    const f32 z_ratio = *mPosReduceRatio_s;
    if (z_ratio >= 0.0f)
        velocity.z *= std::pow(z_ratio, ksys::VFR::instance()->getDeltaFrame());
    else
        velocity.z *= -std::pow(-z_ratio, ksys::VFR::instance()->getDeltaFrame());
    sub_7100737710(controller, velocity);
}

}  // namespace uking::action
