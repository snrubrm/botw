#include "Game/AI/AI/aiNPCAttentionAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Resource/Actor/resResourceAwareness.h"

namespace uking::ai {

NPCAttentionAI::NPCAttentionAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCAttentionAI::~NPCAttentionAI() = default;

bool NPCAttentionAI::init_(sead::Heap* heap) {
    _74 = *mIsUseSight_s ? mActor->getParam()->getRes().mAwareness->sight_angle.ref() :
                           *mTurnAngleDiff_s;
    return true;
}

void NPCAttentionAI::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 time = *mDurationTime_s * 30;
    _68 = ksys::Timer(time, time);
    if (sub_710072DDB8(*mTargetPos_d, mActor->getMtx(), _74))
        m34();
    else
        sub_71004C0C38();
}

void NPCAttentionAI::sub_71004C0C38() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(sead::Vector3f::zero, "TargetRot", -1);
    changeChild("振り向く", &pack);
}

void NPCAttentionAI::calc_() {
    if (isCurrentChild("振り向く")) {
        if (getCurrentChild()->isFinished())
            m34();
    } else if (isCurrentChild("注目")) {
        if (!sub_710072DDB8(*mTargetPos_d, mActor->getMtx(), _74))
            sub_71004C0C38();
    }

    if (*mDurationTime_s != -1) {
        if (!(_68.value <= sead::Mathf::epsilon()))
            _68.update();
        else
            setFinished();
    }
}

void NPCAttentionAI::loadParams_() {
    getStaticParam(&mDurationTime_s, "DurationTime");
    getStaticParam(&mTurnAngleDiff_s, "TurnAngleDiff");
    getStaticParam(&mIsUseSight_s, "IsUseSight");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NPCAttentionAI::m34() {
    changeChild("注目");
}

}  // namespace uking::ai
