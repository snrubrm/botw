#include "Game/AI/AI/aiFlyInsectRoam.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"
#include <cfloat>
#include <utility>

namespace uking::ai {

FlyInsectRoam::FlyInsectRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FlyInsectRoam::~FlyInsectRoam() = default;

bool FlyInsectRoam::init_(sead::Heap* heap) {
    _9c = *mTerritoryRadius_s + *mTerritoryRadiusRand_s * sead::GlobalRandom::instance()->getF32();
    return true;
}

void FlyInsectRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    _a0 = false;
    sub_71003D38B4();
    _90 = ksys::Timer(30, 30);
}

void FlyInsectRoam::calc_() {
    _90.update();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("着地"))
            _90 = ksys::Timer(30, 30);
        else if (child->isFailed())
            _a0 = true;
        sub_71003D38B4();
        return;
    }

    if (!child->isChangeable() || !*mIsEnableOnLand_s || !isCurrentChild("徘徊飛行"))
        return;
    if (!(_90.value <= sead::Mathf::epsilon()))
        return;

    auto* actor = mActor;
    if (isLandedMaybe(actor, false) || isBgGroundHit(actor, false) || sub_71003D3F7C()) {
        _a0 = true;
        changeChild("着地");
    }
}

// NON_MATCHING: vector homes, random-range arithmetic and saved registers differ.
void FlyInsectRoam::sub_71003D38B4() {
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    sead::Vector3f direction = mActor->getMtx().getBase(2);
    const f32 radius = _9c;
    if (_a0) {
        if (isLandedMaybe(mActor, false) || isBgGroundHit(mActor, false)) {
            sead::Vector3f gravity;
            sub_710072DC50(&gravity, mActor);
            const f32 length = gravity.length();
            sead::Vector3f up = -gravity;
            if (length > 0.0f)
                up *= 1.0f / length;
            if (length < FLT_EPSILON)
                up = sead::Vector3f::ey;
            if (sub_71007A47C4(mActor) > 0) {
                ksys::util::sub_71011EFA00(&direction, sub_71007A471C(mActor, 0)->_c, up);
            } else {
                sub_71007A49F0(mActor);
                ksys::util::sub_71011EFA00(&direction, sub_71007A4948(mActor, 0)->_c, up);
            }
        } else {
            ksys::util::sub_71011EF010(&direction, ksys::util::sub_71011EF0CC(3.1415927f));
        }
    } else {
        const sead::Vector3f offset = position - *mTargetPos_d;
        const f32 distance = sead::Mathf::sqrt(offset.x * offset.x + offset.z * offset.z);
        if (distance > radius) {
            direction = -offset;
        } else {
            f32 angle;
            if (!(distance > radius * 0.5f)) {
                const f32 range = *mMaxRotRand_s;
                angle = ksys::util::sub_71011EF0CC((range + range) *
                            sead::GlobalRandom::instance()->getF32() - range);
            } else {
                angle = ksys::util::sub_71011EF0CC(*mMaxRotRandOuter_s *
                            sead::GlobalRandom::instance()->getF32() + 0.17453292f);
                if (!(offset.z * direction.x - offset.x * direction.z > 0.0f))
                    angle = -angle;
            }
            ksys::util::sub_71011EF010(&direction, angle);
        }
    }
    direction.normalize();
    const f32 distance = *mRePathDist_s + *mRePathDistRand_s *
                         sead::GlobalRandom::instance()->getF32();
    sead::Vector3f target = direction * distance + position;
    sead::Vector3f offset = target - *mTargetPos_d;
    const f32 target_distance = offset.normalize();
    if (target_distance > radius)
        target = offset * (radius * 0.8f) + *mTargetPos_d;
    f32 low = mTargetPos_d->y + *mMinHeight_s;
    f32 high = mTargetPos_d->y + *mMaxHeight_s;
    if (low > high)
        std::swap(low, high);
    low = sead::Mathf::max(low, position.y - *mRePathYDistRand_s);
    high = sead::Mathf::min(high, position.y + *mRePathYDistRand_s);
    target.y = low;
    if (low != high) {
        if (low > high)
            std::swap(low, high);
        target.y = sead::GlobalRandom::instance()->getF32Range(low, high);
    }
    _a0 = false;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("徘徊飛行", &pack);
}

bool FlyInsectRoam::sub_71003D3F7C() {
    if (auto* controller = mActor->getCharacterController()) {
        if (auto* info = controller->sub_7100F635D8()) {
            auto end = info->end();
            auto it = info->begin();
            for (; it != end; ++it) {
                if ((*it)->material_mask_b.getMaterial() == ksys::phys::Material::Wood)
                    return true;
            }
        }
    }
    return false;
}

void FlyInsectRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FlyInsectRoam::loadParams_() {
    getStaticParam(&mTerritoryRadius_s, "TerritoryRadius");
    getStaticParam(&mTerritoryRadiusRand_s, "TerritoryRadiusRand");
    getStaticParam(&mMinHeight_s, "MinHeight");
    getStaticParam(&mMaxHeight_s, "MaxHeight");
    getStaticParam(&mRePathDist_s, "RePathDist");
    getStaticParam(&mRePathDistRand_s, "RePathDistRand");
    getStaticParam(&mRePathYDistRand_s, "RePathYDistRand");
    getStaticParam(&mMaxRotRand_s, "MaxRotRand");
    getStaticParam(&mMaxRotRandOuter_s, "MaxRotRandOuter");
    getStaticParam(&mIsEnableOnLand_s, "IsEnableOnLand");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
