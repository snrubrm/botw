#include "Game/AI/Behavior/behaviorSetLocalBoneOffsetRandom.h"

namespace uking::behavior {

SetLocalBoneOffsetRandom::SetLocalBoneOffsetRandom(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

void SetLocalBoneOffsetRandom::m7() {}

void SetLocalBoneOffsetRandom::loadParams() {
    getStaticParam(&mBoneName_s, "BoneName");
    getStaticParam(&mTransOffsetMax_s, "TransOffsetMax");
    getStaticParam(&mTransOffsetMin_s, "TransOffsetMin");
    getStaticParam(&mRotOffsetMax_s, "RotOffsetMax");
    getStaticParam(&mRotOffsetMin_s, "RotOffsetMin");
}

}  // namespace uking::behavior
