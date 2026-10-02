#include "Game/AI/AI/aiCircleMoveInFluid.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"

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

// NON_MATCHING: stack slots of the two inlined VFR core-index temporaries are swapped; operand order
// of the final add
void CircleMoveInFluid::m38() {
    const f32 add_x = *mSpeed_s / _b4 * *mAddAngleRateX_s;
    const f32 add_z = *mSpeed_s / _b8 * *mAddAngleRateZ_s;
    _bc += (_cc ? -add_x : add_x) * ksys::VFR::instance()->getDeltaFrame();
    _c0 += (_cc ? -add_z : add_z) * ksys::VFR::instance()->getDeltaFrame();

    _bc -= sead::Mathf::floor(_bc * (1.0f / sead::Mathf::pi2())) * sead::Mathf::pi2();
    if (_bc >= sead::Mathf::pi2())
        _bc = 0.0f;
    _c0 -= sead::Mathf::floor(_c0 * (1.0f / sead::Mathf::pi2())) * sead::Mathf::pi2();
    if (_c0 >= sead::Mathf::pi2())
        _c0 = 0.0f;

    const f32 diff = _c4 - _c8;
    const f32 abs_diff = sead::Mathf::abs(diff);
    if (abs_diff <= 0.01f) {
        _c8 = _c4;
    } else {
        const f32 limit = *mLimitSpeedMoveY_s;
        f32 step;
        if (abs_diff * 0.16f > limit)
            step = diff < 0.0f ? -limit : limit;
        else if (abs_diff * 0.16f < 0.01f)
            step = diff < 0.0f ? -0.01f : 0.01f;
        else
            step = diff * 0.16f;
        _c8 += step;
    }
}

}  // namespace uking::ai
