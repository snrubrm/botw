#pragma once

#include "Game/AI/Action/actionActorAreaInOutSendMessage.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerAreaInOutSendMessage : public ActorAreaInOutSendMessage {
    SEAD_RTTI_OVERRIDE(PlayerAreaInOutSendMessage, ActorAreaInOutSendMessage)
public:
    explicit PlayerAreaInOutSendMessage(const InitArg& arg);
    ~PlayerAreaInOutSendMessage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // 0x710021d4e8 / 0x710021d54c (declared only): set / clear the payload flag and send the
    // message to the transceiver at +0x180 of the unnamed global 0x71025d1760.
    void m32(const ksys::act::ActorConstDataAccess& accessor) override;
    void m33(const ksys::act::ActorConstDataAccess& accessor) override;
    bool m34(const ksys::act::ActorConstDataAccess& accessor) override;

    // static_param at offset 0x68
    const int* mMessageSet_s{};
    Unk_71023b0898 _70{mActor, 0x8000083};
};
KSYS_CHECK_SIZE_NX150(PlayerAreaInOutSendMessage, 0xb0);

}  // namespace uking::action
