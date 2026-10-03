#include "Game/AI/AI/aiFlyInsectRoam.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

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
