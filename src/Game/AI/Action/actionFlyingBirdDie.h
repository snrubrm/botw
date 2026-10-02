#pragma once

#include "Game/AI/Action/actionFlyingCharacterDamageBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class FlyingBirdDie : public FlyingCharacterDamageBase {
    SEAD_RTTI_OVERRIDE(FlyingBirdDie, FlyingCharacterDamageBase)
public:
    explicit FlyingBirdDie(const InitArg& arg);
    ~FlyingBirdDie() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32() override;
    bool m38() override;

    // static_param at offset 0xf8
    const float* mEnableHitGroundCheckTimer_s{};
    // static_param at offset 0x100
    const bool* mIsChangeStateFallOnce_s{};
    ksys::Timer _108;
    bool _114 = false;
};

}  // namespace uking::action
