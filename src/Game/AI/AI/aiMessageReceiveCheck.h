#pragma once

#include "Game/AI/AI/aiMessageReceiveCheckBasic.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MessageReceiveCheck : public MessageReceiveCheckBasic {
    SEAD_RTTI_OVERRIDE(MessageReceiveCheck, MessageReceiveCheckBasic)
public:
    explicit MessageReceiveCheck(const InitArg& arg);
    ~MessageReceiveCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void handlePendingChildChange_() override;

    bool m34() override;
    void m36() override;

protected:
    // static_param at offset 0x40
    const int* mMsgType_s{};
    Unk_71023f5f90 _48;
    Unk_710235aba0 _80{mActor, 0x8000040};
};

}  // namespace uking::ai
