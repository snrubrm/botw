#include "Game/AI/AI/aiCircleMoveInFluid.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

CircleMoveInFluid::CircleMoveInFluid(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CircleMoveInFluid::~CircleMoveInFluid() = default;

bool CircleMoveInFluid::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CircleMoveInFluid::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CircleMoveInFluid::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CircleMoveInFluid::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRadiusX_s, "RadiusX");
    getStaticParam(&mRadiusZ_s, "RadiusZ");
    getStaticParam(&mMinRandRadiusRate_s, "MinRandRadiusRate");
    getStaticParam(&mMaxRandRadiusRate_s, "MaxRandRadiusRate");
    getStaticParam(&mAddAngleRateX_s, "AddAngleRateX");
    getStaticParam(&mAddAngleRateZ_s, "AddAngleRateZ");
    getStaticParam(&mRandRangeY_s, "RandRangeY");
    getStaticParam(&mRandRangeYOffest_s, "RandRangeYOffest");
    getStaticParam(&mLimitSpeedMoveY_s, "LimitSpeedMoveY");
    getStaticParam(&mChangeInterval_s, "ChangeInterval");
    getStaticParam(&mRandChangeInterval_s, "RandChangeInterval");
    getStaticParam(&mReverseMoveRate_s, "ReverseMoveRate");
    getStaticParam(&mIsSetSystemDeleteDistance_s, "IsSetSystemDeleteDistance");
}

void CircleMoveInFluid::m34() {
    mActor->getMtx().getTranslation(_a8);
}

void CircleMoveInFluid::m35(f32 a2, f32 a3, f32 a4) {
    _b4 = a2 * a4;
    _b8 = a3 * a4;
}

void CircleMoveInFluid::m36(sead::Vector3f* out) {
    out->set(_a8);
}

void CircleMoveInFluid::m37(sead::Vector3f* out) {
    if (!out)
        return;
    m36(out);
    out->x += sead::Mathf::cos(_bc) * _b4;
    out->y += _c8;
    out->z += sead::Mathf::sin(_c0) * _b8;
}

}  // namespace uking::ai
