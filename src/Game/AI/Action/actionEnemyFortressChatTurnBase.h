#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyFortressChatTurnBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EnemyFortressChatTurnBase, ksys::act::ai::Action)
public:
    explicit EnemyFortressChatTurnBase(const InitArg& arg);
    ~EnemyFortressChatTurnBase() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool handleAck_(const ksys::MessageAck* ack) override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32(ksys::act::BaseProcLink* link);
    // Whether the acknowledgement is the one of this action's message.
    virtual bool m33(const ksys::MessageAck* ack);

    // static_param at offset 0x20
    const int* mTryNum_s{};
    // dynamic_param at offset 0x28
    ksys::act::BaseProcLink* mTargetActor_d{};
    // aitree_variable at offset 0x30
    void* mRegistedActorUnit_a{};
    u32 _38 = 0;
    u32 _3c = 0;
    u32 _40 = 0;
    s32 _44[32];
};
KSYS_CHECK_SIZE_NX150(EnemyFortressChatTurnBase, 0xc8);

}  // namespace uking::action
