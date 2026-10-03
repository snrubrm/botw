#include "Game/AI/AI/aiCircleMoveInFluid.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

CircleMoveInFluid::CircleMoveInFluid(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CircleMoveInFluid::~CircleMoveInFluid() = default;

bool CircleMoveInFluid::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CircleMoveInFluid::enter_(ksys::act::ai::InlineParamPack* params) {
    _c8 = 0;
    m34();
    sub_710034F850();
    if (*mParams.mIsSetSystemDeleteDistance_s) {
        f32 distance;
        if (auto* object = mActor->getMapObject())
            distance = ksys::map::PlacementMgr::instance()->getDeleteDistance(object);
        else
            distance = ksys::map::getActorTraverseDist(mActor->getName(), 1.0f) + 10.0f;
        const f32 radius = *mParams.mRadiusX_s > *mParams.mRadiusZ_s ? *mParams.mRadiusX_s : *mParams.mRadiusZ_s;
        const f32 rate = *mParams.mMaxRandRadiusRate_s;
        mActor->setDeleteDistance(distance + radius * rate);
    }
}

void CircleMoveInFluid::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        sub_710034F850();
    else
        child->isChangeable();

    if (!isCurrentChild("移動"))
        return;

    if (*mParams.mChangeInterval_s >= 0.0f) {
        _d0.update();
        if (_d0.value <= sead::Mathf::epsilon()) {
            const f32 range_y = *mParams.mRandRangeY_s;
            _c4 = sead::GlobalRandom::instance()->getF32Range(-range_y, range_y) +
                  *mParams.mRandRangeYOffest_s;
            const f32 interval = *mParams.mChangeInterval_s +
                                 *mParams.mRandChangeInterval_s * sead::GlobalRandom::instance()->getF32();
            _d0 = ksys::Timer(interval, interval);
        }
    }

    m38();
    sead::Vector3f target_pos;
    m37(&target_pos);
    child->setDynamicParam(target_pos, "TargetPos");
}

void CircleMoveInFluid::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CircleMoveInFluid::loadParams_() {
    getStaticParam(&mParams.mSpeed_s, "Speed");
    getStaticParam(&mParams.mRadiusX_s, "RadiusX");
    getStaticParam(&mParams.mRadiusZ_s, "RadiusZ");
    getStaticParam(&mParams.mMinRandRadiusRate_s, "MinRandRadiusRate");
    getStaticParam(&mParams.mMaxRandRadiusRate_s, "MaxRandRadiusRate");
    getStaticParam(&mParams.mAddAngleRateX_s, "AddAngleRateX");
    getStaticParam(&mParams.mAddAngleRateZ_s, "AddAngleRateZ");
    getStaticParam(&mParams.mRandRangeY_s, "RandRangeY");
    getStaticParam(&mParams.mRandRangeYOffest_s, "RandRangeYOffest");
    getStaticParam(&mParams.mLimitSpeedMoveY_s, "LimitSpeedMoveY");
    getStaticParam(&mParams.mChangeInterval_s, "ChangeInterval");
    getStaticParam(&mParams.mRandChangeInterval_s, "RandChangeInterval");
    getStaticParam(&mParams.mReverseMoveRate_s, "ReverseMoveRate");
    getStaticParam(&mParams.mIsSetSystemDeleteDistance_s, "IsSetSystemDeleteDistance");
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
// NON_MATCHING: register allocation (dir.x / dir.z in s9 / s8)
void CircleMoveInFluid::sub_710034F850() {
    sead::Vector3f center;
    m36(&center);

    const auto& mtx = mActor->getMtx();
    sead::Vector3f dir(mtx(0, 2), 0.0f, mtx(2, 2));
    dir.normalize();

    const f32 min_rate = sead::Mathf::clampMax(*mParams.mMinRandRadiusRate_s, *mParams.mMaxRandRadiusRate_s);
    m35(*mParams.mRadiusX_s, *mParams.mRadiusZ_s,
        sead::GlobalRandom::instance()->getF32Range(min_rate, *mParams.mMaxRandRadiusRate_s));
    _cc = sead::GlobalRandom::instance()->getF32() < *mParams.mReverseMoveRate_s;

    f32 angle = std::atan2(dir.x, dir.z);
    const f32 offset = sead::GlobalRandom::instance()->getF32Range(0.0f, sead::Mathf::pi() / 3);
    angle += (_cc ? -1.0f : 1.0f) * offset;
    angle -= sead::Mathf::floor(angle * (1.0f / sead::Mathf::pi2())) * sead::Mathf::pi2();
    if (angle >= sead::Mathf::pi2())
        angle = 0.0f;
    _bc = angle;
    _c0 = angle;

    const f32 range_y = *mParams.mRandRangeY_s;
    _c4 = sead::GlobalRandom::instance()->getF32Range(-range_y, range_y) + *mParams.mRandRangeYOffest_s;
    const f32 interval =
        *mParams.mChangeInterval_s + *mParams.mRandChangeInterval_s * sead::GlobalRandom::instance()->getF32();
    _d0 = ksys::Timer(interval, interval);

    m38();
    sead::Vector3f target_pos;
    m37(&target_pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target_pos, "TargetPos", -1);
    changeChild("移動", &params);
}

void CircleMoveInFluid::m38() {
    const f32 add_x = *mParams.mSpeed_s / _b4 * *mParams.mAddAngleRateX_s;
    const f32 add_z = *mParams.mSpeed_s / _b8 * *mParams.mAddAngleRateZ_s;
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
        const f32 limit = *mParams.mLimitSpeedMoveY_s;
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
