#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRideChaseBattleMoveBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseRideChaseBattleMoveBase, ksys::act::ai::Ai)
public:
    explicit HorseRideChaseBattleMoveBase(const InitArg& arg);
    ~HorseRideChaseBattleMoveBase() override;
    bool handleMessage_(const ksys::Message* message) override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    virtual void m34(int gear) = 0;
    virtual void m35() = 0;
    virtual bool m36() = 0;

protected:
    // static_param at offset 0x38
    const float* mSlowDownDist_s{};
    // static_param at offset 0x40
    const float* mSpeedUpDist_s{};
    // static_param at offset 0x48
    const float* mBaseDist_s{};
    // static_param at offset 0x50
    const float* mOutDist_s{};
    Unk_71023fbec8 _58;
};

}  // namespace uking::ai
