#include "Game/AI/AI/aiSandwormNormalBase.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SandwormNormalBase::SandwormNormalBase(const InitArg& arg) : EnemyNormal(arg) {}

SandwormNormalBase::~SandwormNormalBase() = default;

bool SandwormNormalBase::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void SandwormNormalBase::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
    _3f0 = getCurrentChild();

    auto* actor = mActor;
    auto* awareness = actor->getAwareness();
    if (!awareness)
        return;

    _3f8 = 0;
    for (int i = 0; i < 4; ++i) {
        if (awareness->_260[i] && awareness->_260[i]->_50)
            _3f8 |= 1 << i;
    }

    awareness = actor->getAwareness();
    if (!awareness)
        return;
    if (*mSealedSight_s)
        awareness->sub_7100D7EAE4(0);
    if (*mSealedHearing_s)
        awareness->sub_7100D7EAE4(1);
    if (*mSealedTerror_s)
        awareness->sub_7100D7EAE4(2);
    if (*mSealedWorry_s)
        awareness->sub_7100D7EAE4(3);
}

void SandwormNormalBase::calc_() {
    EnemyNormal::calc_();
    auto* child = getCurrentChild();
    if (_3f0 == child)
        return;
    if (auto* awareness = mActor->getAwareness()) {
        if (*mSealedSight_s)
            awareness->sub_7100D7EAE4(0);
        if (*mSealedHearing_s)
            awareness->sub_7100D7EAE4(1);
        if (*mSealedTerror_s)
            awareness->sub_7100D7EAE4(2);
        if (*mSealedWorry_s)
            awareness->sub_7100D7EAE4(3);
    }
    _3f0 = child;
}

void SandwormNormalBase::leave_() {
    EnemyNormal::leave_();
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return;
    if (*mSealedSight_s && _3f8 & 1)
        awareness->sub_7100D7EAE4(0);
    if (*mSealedHearing_s && _3f8 & 2)
        awareness->sub_7100D7EAE4(1);
    if (*mSealedTerror_s && _3f8 & 4)
        awareness->sub_7100D7EAE4(2);
    if (*mSealedWorry_s && _3f8 & 8)
        awareness->sub_7100D7EAE4(3);
}

void SandwormNormalBase::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mSealedSight_s, "SealedSight");
    getStaticParam(&mSealedHearing_s, "SealedHearing");
    getStaticParam(&mSealedTerror_s, "SealedTerror");
    getStaticParam(&mSealedWorry_s, "SealedWorry");
}

}  // namespace uking::ai
