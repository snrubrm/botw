#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

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

    void sub_710053C804(sead::Vector3f* out, const sead::Vector3f& target, f32 dist);
    // 0x710053d0b8: whether the target is within 60 degrees ahead and the escape point _58 lies within
    // 60 degrees of the target direction (on the XZ plane).
    bool sub_710053D0B8();

protected:
    // static_param at offset 0x38
    const float* mEscapeDist_s{};
    // static_param at offset 0x40
    const float* mNearDist_s{};
    // static_param at offset 0x48
    const float* mEscapeTimer_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    sead::Vector3f _58{0, 0, 0};
    ksys::Timer _64;
};
KSYS_CHECK_SIZE_NX150(ReflectableEscape, 0x70);

}  // namespace uking::ai
