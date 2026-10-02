#pragma once

#include "Game/AI/Action/actionActorAreaInOutSendMessage.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyAreaInOutSendMessage : public ActorAreaInOutSendMessage {
    SEAD_RTTI_OVERRIDE(EnemyAreaInOutSendMessage, ActorAreaInOutSendMessage)
public:
    explicit EnemyAreaInOutSendMessage(const InitArg& arg);
    ~EnemyAreaInOutSendMessage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    void m32(const ksys::act::ActorConstDataAccess& accessor) override;
    void m33(const ksys::act::ActorConstDataAccess& accessor) override;
    sead::Buffer<Payload>* m6() override { return &_70; }

    // static_param at offset 0x68
    const int* mMessageID_s{};
    sead::Buffer<Payload> _70;
};
KSYS_CHECK_SIZE_NX150(EnemyAreaInOutSendMessage, 0x80);

}  // namespace uking::action
