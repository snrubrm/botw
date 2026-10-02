#include "Game/AI/Behavior/behaviorSetLocalBoneOffset.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

SetLocalBoneOffset::SetLocalBoneOffset(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void SetLocalBoneOffset::m7() {}

void SetLocalBoneOffset::m8() {
    mActor->boneHandleStuff(&_48, false);
}

void SetLocalBoneOffset::m9() {
    mActor->sub_71011DA868(&_48);
}

void SetLocalBoneOffset::loadParams() {
    getStaticParam(&mBoneName_s, "BoneName");
    getStaticParam(&mTransOffset_s, "TransOffset");
    getStaticParam(&mRotOffset_s, "RotOffset");
}

}  // namespace uking::behavior
