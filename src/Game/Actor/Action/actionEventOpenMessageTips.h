#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventOpenMessageTips : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventOpenMessageTips, ksys::act::ai::Action)
public:
    explicit EventOpenMessageTips(const InitArg& arg);
    ~EventOpenMessageTips() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mTipsType_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mMessageId_d{};
    // Set once the tips screen was requested / seen open.
    bool mRequested = false;
    bool mOpened = false;
    u8 _3a[0x6];

};
KSYS_CHECK_SIZE_NX150(EventOpenMessageTips, 0x40);

}  // namespace uking::action
