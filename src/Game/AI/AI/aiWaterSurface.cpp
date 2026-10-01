#include "Game/AI/AI/aiWaterSurface.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

WaterSurface::WaterSurface(const InitArg& arg) : WaterSurfaceBase(arg) {}

WaterSurface::~WaterSurface() = default;

bool WaterSurface::init_(sead::Heap* heap) {
    return WaterSurfaceBase::init_(heap);
}

void WaterSurface::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterSurfaceBase::enter_(params);
    m34();
}

void WaterSurface::calc_() {
    WaterSurfaceBase::calc_();
    m35();
}

void WaterSurface::leave_() {
    sub_71005ED864();
    WaterSurfaceBase::leave_();
}

void WaterSurface::loadParams_() {
    WaterSurfaceBase::loadParams_();
    getStaticParam(&mLinkTagType_s, "LinkTagType");
    getMapUnitParam(&mRiseLength_m, "RiseLength");
    getMapUnitParam(&mRiseSpeed_m, "RiseSpeed");
}

bool WaterSurface::sub_71005EC4BC() {
    auto* actor = mActor;
    switch (*mLinkTagType_s) {
    case 0:
        return actor->checkBasicSig();
    case 1:
        if (!actor->checkAxisYSignal() && !actor->checkNAxisYSignal())
            return false;
        return true;
    }
    return false;
}

bool WaterSurface::sub_71005EC520() {
    auto* actor = mActor;
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f target_pos = _68;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    target_pos.y += *mRiseLength_m;
    if ((target_pos - pos).length() < 0.05f)
        return false;

    params.addVec3(target_pos, "TargetPos", -1);
    params.addFloat(*mRiseSpeed_m, "Speed", -1);
    changeChild("水位変更", &params);
    sub_71005ED79C();
    return true;
}

bool WaterSurface::sub_71005EC6B0() {
    auto* actor = mActor;
    ksys::act::ai::InlineParamPack params;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    if ((_68 - pos).length() < 0.05f)
        return false;

    params.addVec3(_68, "TargetPos", -1);
    params.addFloat(*mRiseSpeed_m, "Speed", -1);
    changeChild("水位戻し", &params);
    sub_71005ED79C();
    return true;
}

void WaterSurface::sub_71005EC820() {
    changeChild("待機");
    sub_71005ED864();
}

void WaterSurface::m34() {
    auto* actor = mActor;
    bool has_link;
    switch (*mLinkTagType_s) {
    case 1:
        has_link =
            actor->hasPlacementLinkWithTypeAxisY() || actor->hasPlacementLinkWithType5AxisY();
        break;
    case 0:
        has_link = actor->hasPlacementLinkForBasicSig();
        break;
    default:
        has_link = false;
        break;
    }

    if (has_link) {
        if (sub_71005EC4BC()) {
            if (sub_71005EC520())
                return;
        } else {
            if (sub_71005EC6B0())
                return;
        }
    }
    sub_71005EC820();
}

void WaterSurface::m35() {
    auto* actor = mActor;
    bool has_link;
    switch (*mLinkTagType_s) {
    case 1:
        has_link =
            actor->hasPlacementLinkWithTypeAxisY() || actor->hasPlacementLinkWithType5AxisY();
        break;
    case 0:
        has_link = actor->hasPlacementLinkForBasicSig();
        break;
    default:
        has_link = false;
        break;
    }
    const bool on = has_link && sub_71005EC4BC();

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        sub_71005EC820();
        return;
    }

    if (on) {
        if (!isCurrentChild("水位変更"))
            sub_71005EC520();
    } else {
        if (!isCurrentChild("水位戻し"))
            sub_71005EC6B0();
    }
}

}  // namespace uking::ai
