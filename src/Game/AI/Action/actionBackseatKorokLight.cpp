#include "Game/AI/Action/actionBackseatKorokLight.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

BackseatKorokLight::BackseatKorokLight(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BackseatKorokLight::~BackseatKorokLight() = default;

bool BackseatKorokLight::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BackseatKorokLight::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!actor->isCalc()) {
        const sead::Vector3f& pos = actor->getMtx().getTranslation();
        const f32 x = pos.x;
        const f32 z = pos.z;
        const sead::Vector3f& player = getPlayerPosition();
        const f32 dx = x - player.x;
        const f32 dz = z - player.z;
        const f32 dist_sq = dx * dx + dz * dz;
        _a1 = dist_sq < *mDisappearDist_s * *mDisappearDist_s;
        if (dist_sq > *mAppearDist_s * *mAppearDist_s) {
            _a2 = true;
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
        } else {
            _a2 = false;
        }
    }
    _a4 = mActor->getMtx().getTranslation();
    if (_a0)
        playAS(mGroundWaitASName_s.cstr(), false, 0, 0, -1.0f);
    else
        playAS(mFlyWaitASName_s.cstr(), false, 0, 0, -1.0f);
}

void BackseatKorokLight::leave_() {
    ksys::act::ai::Action::leave_();
}

void BackseatKorokLight::loadParams_() {
    getStaticParam(&mAppearDist_s, "AppearDist");
    getStaticParam(&mDisappearDist_s, "DisappearDist");
    getStaticParam(&mGroundWaitASName_s, "GroundWaitASName");
    getStaticParam(&mGroundAppearASName_s, "GroundAppearASName");
    getStaticParam(&mGroundDisappearASName_s, "GroundDisappearASName");
    getStaticParam(&mFlyWaitASName_s, "FlyWaitASName");
    getStaticParam(&mFlyAppearASName_s, "FlyAppearASName");
    getStaticParam(&mFlyDisappearASName_s, "FlyDisappearASName");
    getMapUnitParam(&mPlacementType_m, "PlacementType");
}

void BackseatKorokLight::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
