#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ReflectableEscape : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ReflectableEscape, ksys::act::ai::Ai)
public:
    explicit ReflectableEscape(const InitArg& arg);
    ~ReflectableEscape() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mEscapeDist_s{};
    // static_param at offset 0x40
    const float* mNearDist_s{};
    // static_param at offset 0x48
    const float* mEscapeTimer_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    f32 _58 = 0;
    u32 _5c = 0;
    f32 _60 = 0;
    f32 _64 = 0;
    u32 _68 = 0;
    u32 _6c = 0;
};
KSYS_CHECK_SIZE_NX150(ReflectableEscape, 0x70);

}  // namespace uking::ai
