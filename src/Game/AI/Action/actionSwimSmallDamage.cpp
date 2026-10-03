#include "Game/AI/Action/actionSwimSmallDamage.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SwimSmallDamage::SwimSmallDamage(const InitArg& arg) : SmallDamage(arg) {}

SwimSmallDamage::~SwimSmallDamage() = default;

void SwimSmallDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamage::enter_(params);
    _b8.sub_710072AD1C(mActor->getCharacterController());
}

void SwimSmallDamage::leave_() {
    SmallDamage::leave_();
}

void SwimSmallDamage::loadParams_() {
    TakeHitImpactForce::loadParams_();
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mASName_s, "ASName");
}

void SwimSmallDamage::m38() {
    f32 depth = 0.0f;
    if (mActor->get68f()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }
    if (depth + *mFloatRadius_s >= *mInWaterDepth_s + *mFloatDepth_s)
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    else
        SmallDamage::m38();
}

}  // namespace uking::action
