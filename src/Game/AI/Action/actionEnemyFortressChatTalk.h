#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyFortressChatTalk : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EnemyFortressChatTalk, ksys::act::ai::Action)
public:
    explicit EnemyFortressChatTalk(const InitArg& arg);
    ~EnemyFortressChatTalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool handleAck_(const ksys::MessageAck* ack) override;

protected:
    void calc_() override;
    virtual void m32();
    // Whether the acknowledgement is the one of this action's message.
    virtual bool m33(const ksys::MessageAck* ack);

    // 0x7100108da4: a random registered actor that is not the target and is in the calc state
    // (the dummy link if there is none).
    ksys::act::BaseProcLink& sub_7100108DA4();
    // 0x7100108ec8: as above, and the actor is an Enemy with the flag 0x1000 set.
    ksys::act::BaseProcLink& sub_7100108EC8();

    // static_param at offset 0x20
    const int* mTryNum_s{};
    // static_param at offset 0x28
    const int* mTimeOut_s{};
    // dynamic_param at offset 0x30
    ksys::act::BaseProcLink* mTargetActor_d{};
    // aitree_variable at offset 0x38
    void* mRegistedActorUnit_a{};
    Unk_7102379b00 _40;
    Unk_7102379b30 _90;
    s32 _e0 = 0;
    f32 _e4 = 0.0f;
    bool _e8 = false;
    bool _e9 = false;
};
KSYS_CHECK_SIZE_NX150(EnemyFortressChatTalk, 0xf0);

}  // namespace uking::action
