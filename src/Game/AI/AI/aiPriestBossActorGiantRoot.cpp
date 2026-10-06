#include "Game/AI/AI/aiPriestBossActorGiantRoot.h"
#include <cmath>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

// NON_MATCHING: the original keeps `_9c = 2` and `_a0 = 0` as two 32-bit stores (we merge them into one
// 64-bit store).
PriestBossActorGiantRoot::PriestBossActorGiantRoot(const InitArg& arg) : PriestBossActorRoot(arg) {}

PriestBossActorGiantRoot::~PriestBossActorGiantRoot() = default;

bool PriestBossActorGiantRoot::init_(sead::Heap* heap) {
    return PriestBossActorRoot::init_(heap);
}

void PriestBossActorGiantRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorRoot::enter_(params);
}

// NON_MATCHING: the original copies `_9c` through a stack slot (str / ldr) for the first test only
void PriestBossActorGiantRoot::calc_() {
    PriestBossActorRoot::calc_();
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }

    const sead::Vector3f pos = sub_71005D9330(mActor);
    _dc.update();
    *mIsActive_a = _9c != State::_2;
    if (_9c != State::_7) {
        *mFacePos_a = pos;
        if (_9c == State::_8)
            child->setDynamicParam(pos, "TargetPos");
    }
    m47();
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
