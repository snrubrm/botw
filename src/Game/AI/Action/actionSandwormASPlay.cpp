#include "Game/AI/Action/actionSandwormASPlay.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actSandworm.h"
#include "Game/AI/aiUnk_7102451120.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

// Declaration-only native helper; source namespace unknown (also declared in actionSandwormJumpTackle.cpp).
void sub_7100720330(ksys::act::Actor* actor);

namespace uking::action {

SandwormASPlay::SandwormASPlay(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

SandwormASPlay::~SandwormASPlay() = default;

bool SandwormASPlay::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void SandwormASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    auto* actor = mActor;
    const int delay = *mChangeOffsetDelay_s;
    if (delay >= 1) {
        _90 = ksys::Timer(delay, delay);
    } else if (auto* sandworm = sead::DynamicCast<act::Sandworm>(actor)) {
        sandworm->_15b0 = *mTargetSandOffset_s;
        sandworm->_1638 = true;
        sandworm->_15ac = *mSandOffsetSpeed_s;
        sandworm->_1638 = true;
    }
    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
    else
        mFlags.reset(Flag::Changeable);
    if (!mTransBoneName_s.isEmpty()) {
        if (auto* as_list = actor->getASList())
            as_list->sub_710115BAF8(mTransBoneName_s);
    }
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void SandwormASPlay::leave_() {
    auto* actor = mActor;
    if (*mIsUseAtEvent_s) {
        sub_7100720254(actor);
        sub_7100720330(actor);
        sub_71007208EC(actor);
    }
    if (*mChangeOffsetDelay_s >= 1 && !(_90.value <= sead::Mathf::epsilon())) {
        if (auto* sandworm = sead::DynamicCast<act::Sandworm>(actor)) {
            sandworm->_15b0 = *mTargetSandOffset_s;
            sandworm->_1638 = true;
            sandworm->_15ac = *mSandOffsetSpeed_s;
            sandworm->_1638 = true;
        }
    }
    if (!mTransBoneName_s.isEmpty()) {
        if (auto* as_list = actor->getASList())
            as_list->sub_710115CD0C();
    }
    ActionWithPosAngReduce::leave_();
}

void SandwormASPlay::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mChangeOffsetDelay_s, "ChangeOffsetDelay");
    getStaticParam(&mTargetSandOffset_s, "TargetSandOffset");
    getStaticParam(&mSandOffsetSpeed_s, "SandOffsetSpeed");
    getStaticParam(&mWaitASFinish_s, "WaitASFinish");
    getStaticParam(&mWaitSandOffset_s, "WaitSandOffset");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsUseAtEvent_s, "IsUseAtEvent");
    getStaticParam(&mIsUseTossAt_s, "IsUseTossAt");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mTransBoneName_s, "TransBoneName");
}

void SandwormASPlay::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
