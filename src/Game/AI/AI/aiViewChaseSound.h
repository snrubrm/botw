#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ViewChaseSound : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ViewChaseSound, ksys::act::ai::Ai)
public:
    explicit ViewChaseSound(const InitArg& arg);
    ~ViewChaseSound() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71005e4268: casts a ray down from the target position, then changes to the "直線追跡" child
    void sub_71005E4268();
    // 0x71005e4150: casts a ray down from the target position, then changes to the "追跡" child
    void sub_71005E4150();
    // 0x71005e39e8: casts a ray down from the target position, then changes to the "回転" child
    void sub_71005E39E8();
    // static_param at offset 0x38
    const float* mTurnDir_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
