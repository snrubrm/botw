#pragma once

#include "Game/AI/AI/aiMessageReceiveCheckBasic.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MessageReceiveCheckEveryFrame : public MessageReceiveCheckBasic {
    SEAD_RTTI_OVERRIDE(MessageReceiveCheckEveryFrame, MessageReceiveCheckBasic)
public:
    explicit MessageReceiveCheckEveryFrame(const InitArg& arg);
    ~MessageReceiveCheckEveryFrame() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;
    bool m35() override;

protected:
    // static_param at offset 0x40
    const int* mMsgType_s{};
};

}  // namespace uking::ai
