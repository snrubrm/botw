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
