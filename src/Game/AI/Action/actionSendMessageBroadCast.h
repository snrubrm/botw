#pragma once
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "Game/AI/aiUnk_7102357d20.h"

#include "Game/AI/Action/actionSendMessage.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SendMessageBroadCast : public SendMessage {
    SEAD_RTTI_OVERRIDE(SendMessageBroadCast, SendMessage)
public:
    explicit SendMessageBroadCast(const InitArg& arg);
    ~SendMessageBroadCast() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    void doSendMessage() override;

    // static_param at offset 0x28
    const int* mMsgType_s{};
    ksys::act::BaseProcLink _30;
    Unk_710235aba0 _40{mActor, 0x8000040};
};

}  // namespace uking::action
