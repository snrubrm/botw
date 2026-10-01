#include "Game/AI/AI/aiSetTargetPosToPlayer.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SetTargetPosToPlayer::SetTargetPosToPlayer(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SetTargetPosToPlayer::~SetTargetPosToPlayer() = default;

bool SetTargetPosToPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SetTargetPosToPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    _74 = 0;
    sead::Vector3f pos;
    if (!sub_71005694B4(&pos))
        mActor->getMtx().getTranslation(pos);

    ksys::act::ai::InlineParamPack child_params;
    child_params.addVec3(pos, "TargetPos", -1);
    changeChild("子アクション", &child_params);
}

void SetTargetPosToPlayer::calc_() {
    _68.update();
    if (*mUpdateTargetInterval_s < 0)
        return;

    if (_68.value <= sead::Mathf::epsilon()) {
        sead::Vector3f pos;
        if (sub_71005694B4(&pos))
            getCurrentChild()->setDynamicParam(pos, "TargetPos");
    }
}

void SetTargetPosToPlayer::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SetTargetPosToPlayer::loadParams_() {
    getStaticParam(&mUpdateTargetInterval_s, "UpdateTargetInterval");
    getStaticParam(&mMaxUpdateNum_s, "MaxUpdateNum");
    getStaticParam(&mAddLength_s, "AddLength");
    getStaticParam(&mHeightOffset_s, "HeightOffset");
    getStaticParam(&mRandRange_s, "RandRange");
    getStaticParam(&mRandRate_s, "RandRate");
}

}  // namespace uking::ai
