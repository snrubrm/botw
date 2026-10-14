#include "Game/Actor/AI/aiPriestBossMakeClone.h"
#include "Game/Actor/aiUnk_7102450fa8.h"

namespace uking::ai {

PriestBossMakeClone::PriestBossMakeClone(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossMakeClone::~PriestBossMakeClone() = default;

bool PriestBossMakeClone::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossMakeClone::enter_(ksys::act::ai::InlineParamPack* params) {
    mCloneRecords.clear();
    _54 = sUnk_71025c8cf8;
    _60 = sead::Vector3f::zero;
    _6c = sead::Vector3f::zero;
    mRespawnStarted = false;
    mRespawnTimer = 0.0f;
    mState = 0;
    sub_7100524660(true);
}

void PriestBossMakeClone::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossMakeClone::loadParams_() {
    getStaticParam(&mRespawnFrame_s, "RespawnFrame");
    getStaticParam(&mBackStepDistance_s, "BackStepDistance");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
