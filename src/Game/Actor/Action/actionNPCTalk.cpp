#include "Game/Actor/Action/actionNPCTalk.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actHorseRideInfo.h"

namespace uking::action {

// NON_MATCHING: the original sinks the three stores after the FixedSafeString (0xd0-0xe8) in front of
// its final vtable store and loads the vtable after the terminator byte store
NPCTalk::NPCTalk(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTalk::~NPCTalk() = default;

bool NPCTalk::init_(sead::Heap* heap) {
    _d0._10 = sead::DynamicCast<act::NPC>(mActor);
    return true;
}

void NPCTalk::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCTalk::leave_() {
    mActor->getASList()->x_2(66, 14, false, false);
    if (_d0._10) {
        _d0._10->_fe8 &= ~0x8000;
        _d0._10->_fe8 &= ~0x40000000;
    }
}

void NPCTalk::loadParams_() {
    getStaticParam(&mIsRemainOpeningDialog_s, "IsRemainOpeningDialog");
    getStaticParam(&mMinTalkTime_s, "MinTalkTime");
    getDynamicParam(&mIsCloseMessageDialog_d, "IsCloseMessageDialog");
    getDynamicParam(&mIsBecomingSpeaker_d, "IsBecomingSpeaker");
    getDynamicParam(&mIsOverWriteLabelActorName_d, "IsOverWriteLabelActorName");
    getDynamicParam(&mMessageId_d, "MessageId");
    getDynamicParam(&mASName_d, "ASName");
}

void NPCTalk::calc_() {
    ksys::act::ai::Action::calc_();
}

const char* NPCTalk::sub_71002027D0() {
    sead::SafeString posture = mActor->getASList()->sub_710115ECF4(0x3b, 1);
    if (posture == "" || posture == "Crouch")
        return "Talk";
    if (posture == "SitOnObject")
        return "Talk_SitChair";
    if (posture == "Sit")
        return "Talk_Rest";
    return "Talk";
}

bool NPCTalk::sub_7100203808() {
    if (!_d0._10)
        return false;
    const char* param_37 = mActor->getASList()->sub_710115ECF4(0x37, 1);
    const sead::SafeString param_38 = mActor->getASList()->sub_710115ECF4(0x38, 1);
    const sead::SafeString group = _d0._10->_8b8 ? _d0._10->_8a8 : sead::SafeString("Normal");
    const sead::SafeString name = _d0._10->_8a8;
    bool changed = false;
    if (group != param_37) {
        mActor->getASList()->x_2(0x42, 9, true, false);
        changed = true;
    } else if (!mActor->getASList()->x(22, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        mActor->getASList()->x_2(0x42, 9, false, false);
    }
    if (name != param_38) {
        mActor->getASList()->x_2(0x42, 11, true, false);
        mActor->getASList()->x_2(0x42, 0x20, false, true);
    } else if (!mActor->getASList()->x(22, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true) ||
               param_38 != param_37) {
        mActor->getASList()->x_2(0x42, 11, false, false);
    }
    mActor->getASList()->goLimpFromHeadShotMaybe(0x37, group, 0);
    mActor->getASList()->goLimpFromHeadShotMaybe(0x38, name, 0);
    return changed;
}

bool NPCTalk::sub_7100203B38() {
    if (!_d0._10)
        return false;
    const char* param_37 = mActor->getASList()->sub_710115ECF4(0x37, 1);
    const char* param_38 = mActor->getASList()->sub_710115ECF4(0x38, 1);
    const sead::SafeString name = _d0._10->_8a8;
    if (name != param_38) {
        mActor->getASList()->x_2(0x42, 11, true, false);
        mActor->getASList()->x_2(0x42, 0x20, false, true);
    } else if (!mActor->getASList()->x(22, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true) ||
               sead::SafeString(param_38) != param_37) {
        mActor->getASList()->x_2(0x42, 11, false, false);
    }
    mActor->getASList()->goLimpFromHeadShotMaybe(0x38, name, 0);
    return true;
}

void NPCTalk::sub_7100203F04() {
    if (mActor->getPlayerRideInfo() && mActor->getPlayerRideInfo()->_30 & 1) {
        playAS("RideWait", true, 0, 0, -1.0f);
        return;
    }
    if (_78.isEmpty())
        return;
    const bool loop = _78.findIndex("Talk") == -1;
    playAS(_78.cstr(), loop, 0, 0, -1.0f);
    mActor->getASList()->x_2(0x42, 14, false, false);
}

}  // namespace uking::action
