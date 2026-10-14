#include "Game/Actor/AI/aiNPCTalkBalloon.h"
#include "Game/Actor/actNPCBase.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
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

// NON_MATCHING: block layout of the 注目 branch (checkAS / x_7 / timer chain) and the message split
void NPCTalkBalloon::calc_() {
    if (_60 && !(_64.value <= sead::Mathf::epsilon()))
        _64.update();

    if (isCurrentChild("振り向く")) {
        if (getCurrentChild()->isFinished()) {
            ksys::act::ai::InlineParamPack pack;
            if (_80.isEmpty())
                pack.addString("Wait", "DynASName", -1);
            else
                pack.addString(_80, "DynASName", -1);
            changeChild("注目", &pack);
        }
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    } else if (isCurrentChild("注目")) {
        if (!_60) {
            _70.update();
            if (_70.value > sead::Mathf::epsilon())
                return;
            auto* ui = ui::UI::instance();
            if (!ui)
                return;
            const s32 index = mMessageId_d.rfindIndex(":");
            if (index < 1) {
                setFailed();
                return;
            }
            sead::FixedSafeString<64> message_set;
            message_set.copy(mMessageId_d, index);
            ui->sub_71010A6454(message_set, mMessageId_d.getPart(index + 1), mActor, 30.0f, false);
            _60 = true;
        } else if (checkAS(0, 0) ||
                   (mActor->getASList()->x_7(0, 0, &ksys::as::ASList::Unk2::sub_7101162FE8) &&
                    _64.value <= sead::Mathf::epsilon())) {
            setFinished();
        }
    }
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
