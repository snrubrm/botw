#include "Game/AI/AI/aiBeamExplodeEitherHit.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

BeamExplodeEitherHit::BeamExplodeEitherHit(const InitArg& arg) : BeamExplode(arg) {}

BeamExplodeEitherHit::~BeamExplodeEitherHit() = default;

bool BeamExplodeEitherHit::init_(sead::Heap* heap) {
    return BeamExplode::init_(heap);
}

void BeamExplodeEitherHit::enter_(ksys::act::ai::InlineParamPack* params) {
    BeamExplode::enter_(params);
    *mIsReflectThrownBullet_a = false;
}

void BeamExplodeEitherHit::calc_() {
    BeamExplode::calc_();
}

void BeamExplodeEitherHit::leave_() {
    BeamExplode::leave_();
}

void BeamExplodeEitherHit::loadParams_() {
    BeamExplode::loadParams_();
    getAITreeVariable(&mIsReflectThrownBullet_a, "IsReflectThrownBullet");
}

void BeamExplodeEitherHit::m35() {
    ksys::act::ai::InlineParamPack params;
    params.addBool(*mIsReflectThrownBullet_a, "IsPlayerAttack", -1);
    changeChild("爆発", &params);
}

}  // namespace uking::ai
