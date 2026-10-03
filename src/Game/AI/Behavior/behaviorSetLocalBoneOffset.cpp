#include "Game/AI/Behavior/behaviorSetLocalBoneOffset.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

SetLocalBoneOffset::SetLocalBoneOffset(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetLocalBoneOffset::~SetLocalBoneOffset() = default;

bool SetLocalBoneOffset::m6(sead::Heap* heap) {
    const sead::Vector3f& trans = *mTransOffset_s;
    const sead::Vector3f& rot = *mRotOffset_s;
    const sead::SafeString& name = mBoneName_s;
    _48.setName(name);
    _48._68.makeRT(rot, trans);
    return true;
}

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
