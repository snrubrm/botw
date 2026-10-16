#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::act {
class NPC;
}  // namespace uking::act

namespace uking::action {

class NPCTalk : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCTalk, ksys::act::ai::Action)
public:
    explicit NPCTalk(const InitArg& arg);
    ~NPCTalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // 0x7100203f04 (placeholder name): plays RideWait while riding, else the talk animation _78 (looped unless it
    // contains "Talk").
    void sub_7100203F04();
    // 0x71002027d0 (placeholder name): the talk animation for the actor's AS posture parameter 0x3b.
    const char* sub_71002027D0();
    // 0x7100203b38 (placeholder name): switches AS parameter 0x38 to the NPC's posture name (_8a8); false without
    // an NPC.
    bool sub_7100203B38();
    // 0x7100203808 (placeholder name): sets AS parameters 0x37 / 0x38 to the NPC's posture group and name; true if
    // the group changed.
    bool sub_7100203808();

    // static_param at offset 0x20
    const int* mIsRemainOpeningDialog_s{};
    // static_param at offset 0x28
    const int* mMinTalkTime_s{};
    // dynamic_param at offset 0x30
    bool* mIsCloseMessageDialog_d{};
    // dynamic_param at offset 0x38
    bool* mIsBecomingSpeaker_d{};
    // dynamic_param at offset 0x40
    bool* mIsOverWriteLabelActorName_d{};
    // dynamic_param at offset 0x48
    sead::SafeString mMessageId_d{};
    // dynamic_param at offset 0x58
    sead::SafeString mASName_d{};
    u64 _68 = 0;
    s32 _70 = 0;
    sead::SafeString _78{};
    sead::SafeString _88{};
    sead::FixedSafeString<32> _98;
    struct S {
        u64 _0 = 0;
        s32 _8 = 0;
        uking::act::NPC* _10 = nullptr;
    } _d0;
};
KSYS_CHECK_SIZE_NX150(NPCTalk, 0xe8);

}  // namespace uking::action
