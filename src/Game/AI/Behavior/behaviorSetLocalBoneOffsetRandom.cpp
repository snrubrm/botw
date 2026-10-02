#include "Game/AI/Behavior/behaviorSetLocalBoneOffsetRandom.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

SetLocalBoneOffsetRandom::SetLocalBoneOffsetRandom(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetLocalBoneOffsetRandom::~SetLocalBoneOffsetRandom() = default;

// NON_MATCHING: register allocation / frame layout (the original computes &mBoneName_s up front and
// spills the x translation at sp+0xc)
bool SetLocalBoneOffsetRandom::m6(sead::Heap* heap) {
    sead::Vector3f trans;
    trans.x = sead::GlobalRandom::instance()->getF32Range(mTransOffsetMin_s->x, mTransOffsetMax_s->x);
    trans.y = sead::GlobalRandom::instance()->getF32Range(mTransOffsetMin_s->y, mTransOffsetMax_s->y);
    trans.z = sead::GlobalRandom::instance()->getF32Range(mTransOffsetMin_s->z, mTransOffsetMax_s->z);
    sead::Vector3f rot;
    rot.x = sead::GlobalRandom::instance()->getF32Range(mRotOffsetMin_s->x, mRotOffsetMax_s->x);
    rot.y = sead::GlobalRandom::instance()->getF32Range(mRotOffsetMin_s->y, mRotOffsetMax_s->y);
    rot.z = sead::GlobalRandom::instance()->getF32Range(mRotOffsetMin_s->z, mRotOffsetMax_s->z);
    _58.setName(mBoneName_s);
    _58._68.makeRT(rot, trans);
    return true;
}

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
