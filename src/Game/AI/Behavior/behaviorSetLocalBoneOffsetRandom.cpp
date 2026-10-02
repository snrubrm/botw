#include "Game/AI/Behavior/behaviorSetLocalBoneOffsetRandom.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

SetLocalBoneOffsetRandom::SetLocalBoneOffsetRandom(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

void SetLocalBoneOffsetRandom::m7() {}

void SetLocalBoneOffsetRandom::m8() {
    mActor->boneHandleStuff(&_58, false);
}

void SetLocalBoneOffsetRandom::m9() {
    mActor->sub_71011DA868(&_58);
}

void SetLocalBoneOffsetRandom::loadParams() {
    getStaticParam(&mBoneName_s, "BoneName");
    getStaticParam(&mTransOffsetMax_s, "TransOffsetMax");
    getStaticParam(&mTransOffsetMin_s, "TransOffsetMin");
    getStaticParam(&mRotOffsetMax_s, "RotOffsetMax");
    getStaticParam(&mRotOffsetMin_s, "RotOffsetMin");
}

}  // namespace uking::behavior
