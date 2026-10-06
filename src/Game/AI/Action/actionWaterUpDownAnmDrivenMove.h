#pragma once

#include "Game/AI/aiUnk_7100700620.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace ksys::phys {
class CharacterController;
}

namespace uking::action {

class WaterUpDownAnmDrivenMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WaterUpDownAnmDrivenMove, ksys::act::ai::Action)
public:
    explicit WaterUpDownAnmDrivenMove(const InitArg& arg);
    ~WaterUpDownAnmDrivenMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32(ksys::phys::CharacterController* controller);

    // static_param at offset 0x20
    const float* mInWaterDepth_s{};
    // static_param at offset 0x28
    const float* mTargetDepth_s{};
    // static_param at offset 0x30
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x38
    const float* mRotReduceRatio_s{};
    // static_param at offset 0x40
    sead::SafeString mASName_s{};
    f32 _50 = 1.0f;
    ksys::act::CCAccessor _54;
    Unk_7100700620 _5c;
};
KSYS_CHECK_SIZE_NX150(WaterUpDownAnmDrivenMove, 0x68);

}  // namespace uking::action
