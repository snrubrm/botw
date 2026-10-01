#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class NPCAttentionAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCAttentionAI, ksys::act::ai::Ai)
public:
    explicit NPCAttentionAI(const InitArg& arg);
    ~NPCAttentionAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

    virtual void m34();

protected:
    // static_param at offset 0x38
    const int* mDurationTime_s{};
    void* _40{};
    // static_param at offset 0x48
    const float* mTurnAngleDiff_s{};
    // static_param at offset 0x50
    const bool* mIsUseSight_s{};
    void* _58{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _68;
    f32 _74 = 0;
};
KSYS_CHECK_SIZE_NX150(NPCAttentionAI, 0x78);

}  // namespace uking::ai
