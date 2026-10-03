#include "Game/AI/AI/aiNPCTalkBalloon.h"
#include "Game/Actor/actNPCBase.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

NPCTalkBalloon::NPCTalkBalloon(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NPCTalkBalloon::~NPCTalkBalloon() {
    ;
}

void NPCTalkBalloon::enter_(ksys::act::ai::InlineParamPack* params) {
    _60 = false;
    const f32 duration = *mDurationTime_s * 30.0f;
    _64 = ksys::Timer(duration, duration);
    const f32 delay = *mDelayFrame_s;
    _70 = ksys::Timer(delay, delay);
    _80 = sead::SafeString();
    if (auto* npc = sead::DynamicCast<act::NPCBase>(mActor))
        _80 = npc->_c18;
    sub_71004E1684();
}

void NPCTalkBalloon::sub_71004E1684() {
    sead::Vector3f dir = *mTargetPos_d - mActor->getMtx().getTranslation();
    dir.y = 0.0f;
    dir.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, sead::Vector3f::ez, dir, sead::Vector3f::ey);
    const sead::Vector3f rot{0.0f, angle * axis.y, 0.0f};

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(rot, "TargetRot", -1);
    changeChild("振り向く", &pack);
}

void NPCTalkBalloon::leave_() {
    if (auto* ui = ui::UI::instance()) {
        if (ui->sub_71010A5B0C(mActor))
            ui->sub_71010A6BEC(mActor, false);
    }
}

void NPCTalkBalloon::loadParams_() {
    getStaticParam(&mDurationTime_s, "DurationTime");
    getStaticParam(&mDelayFrame_s, "DelayFrame");
    getDynamicParam(&mMessageId_d, "MessageId");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
