#include "Game/AI/AI/aiPriestBossActorGiantRoot.h"
#include <cmath>
#include <random/seadGlobalRandom.h>

namespace uking::ai {

PriestBossActorGiantRoot::PriestBossActorGiantRoot(const InitArg& arg) : PriestBossActorRoot(arg) {}

PriestBossActorGiantRoot::~PriestBossActorGiantRoot() = default;

bool PriestBossActorGiantRoot::init_(sead::Heap* heap) {
    return PriestBossActorRoot::init_(heap);
}

void PriestBossActorGiantRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorRoot::enter_(params);
}

void PriestBossActorGiantRoot::leave_() {
    PriestBossActorRoot::leave_();
    *mIsActive_a = false;
}

void PriestBossActorGiantRoot::loadParams_() {
    PriestBossActorRoot::loadParams_();
    getStaticParam(&mFreqIronBallAttack_s, "FreqIronBallAttack");
    getStaticParam(&mFreqBigEarthReleaseAttack_s, "FreqBigEarthReleaseAttack");
    getStaticParam(&mFreqEyeBeamAttack_s, "FreqEyeBeamAttack");
    getStaticParam(&mFreqStageRotation_s, "FreqStageRotation");
    getStaticParam(&mFloatDistFromPlayer_s, "FloatDistFromPlayer");
    getStaticParam(&mIsFreeMoving_s, "IsFreeMoving");
    getAITreeVariable(&mKeepDistFromGround_a, "KeepDistFromGround");
    getAITreeVariable(&mIsActive_a, "IsActive");
    getAITreeVariable(&mIsArrivedAtDestination_a, "IsArrivedAtDestination");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
    getAITreeVariable(&mFacePos_a, "FacePos");
}

const char* PriestBossActorGiantRoot::m36() {
    return "第三段階";
}

// NON_MATCHING: the original's two uses of the by-value attack (the switch and the counter index) get
// separate stack slots, in the opposite order (two inline helpers with by-value parameters: the
// switch's slot above the index's); a single helper shares one slot
f32 PriestBossActorGiantRoot::getWeight(Attack attack) {
    f32 freq = 0.0f;
    switch (attack) {
    case Attack::_3:
        freq = *mFreqIronBallAttack_s;
        break;
    case Attack::_4:
        freq = *mFreqBigEarthReleaseAttack_s;
        break;
    case Attack::_5:
        freq = *mFreqEyeBeamAttack_s;
        break;
    case Attack::_7:
        freq = *mFreqStageRotation_s;
        break;
    default:
        break;
    }
    f32 weight = 0.0f;
    weight += freq * sead::GlobalRandom::instance()->getF32();
    weight += std::pow(0.9f, f32(_b0[attack]));
    return weight * 0.5f;
}

f32 PriestBossActorGiantRoot::m37() {
    return 0.0f;
}

f32 PriestBossActorGiantRoot::m38() {
    return 0.01f;
}

f32 PriestBossActorGiantRoot::m39() {
    return 0.0f;
}

f32 PriestBossActorGiantRoot::m40() {
    return getWeight(Attack::_3);
}

f32 PriestBossActorGiantRoot::m42() {
    return getWeight(Attack::_5);
}

f32 PriestBossActorGiantRoot::m44() {
    if (_dc.value <= sead::Mathf::epsilon() && _98 != 4)
        return getWeight(Attack::_7);
    return 0.0f;
}

f32 PriestBossActorGiantRoot::m43() {
    return 0.0f;
}

f32 PriestBossActorGiantRoot::m45() {
    return 0.0f;
}

}  // namespace uking::ai
