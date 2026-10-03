#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FriendCallAction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(FriendCallAction, ksys::act::ai::Ai)
public:
    explicit FriendCallAction(const InitArg& arg);
    ~FriendCallAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;
    bool handleAck_(const ksys::MessageAck& ack) override;

    void changeToCallOut();
    // 0x71003ddbbc (placeholder name)
    void changeToAwait();
    // 0x71003ddc94 (placeholder name)
    void changeToAction();

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mNearDistH_s{};
    // static_param at offset 0x48
    const float* mNearDistVMax_s{};
    // static_param at offset 0x50
    const float* mNearDistVMin_s{};
    // dynamic_param at offset 0x58
    ksys::act::BaseProcLink* mTargetActor_d{};
    Unk_710236f520 _60{mActor, 0x8000007};
    Unk_7102450588 _90;
    bool _e0 = false;
};
KSYS_CHECK_SIZE_NX150(FriendCallAction, 0xe8);

}  // namespace uking::ai
