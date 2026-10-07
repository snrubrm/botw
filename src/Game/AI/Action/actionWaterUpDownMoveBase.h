#pragma once

#include "Game/AI/aiUnk_7100700620.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

class WaterUpDownMoveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WaterUpDownMoveBase, ksys::act::ai::Action)
public:
    explicit WaterUpDownMoveBase(const InitArg& arg);
    ~WaterUpDownMoveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // Called by calc_ when the AS event query (type 0x2f) fired; the event name holds the target depth.
    virtual void m32(ksys::as::ASList::Unk4* query);
    virtual void m33(ksys::phys::CharacterController* controller);
    virtual void m34(ksys::phys::CharacterController* controller);

    // 0x71002b390c (placeholder name): sets up the up/down movement towards `target_depth`
    // (4 parameters of the spline stored in _60.._70).
    void sub_71002B390C(f32 target_depth, f32 duration);
    // 0x71002b3acc and 0x71002b3f78 (placeholder names): the velocity update of m33 / m34.
    void sub_71002B3ACC(ksys::phys::CharacterController* controller);
    void sub_71002B3F78(ksys::phys::CharacterController* controller);

    // 0x71002b37f8 (placeholder name): the height of the water surface below the actor (0 if none).
    f32 sub_71002B37F8();

    // static_param at offset 0x20
    const float* mInWaterDepth_s{};
    // static_param at offset 0x28
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x30
    const float* mRotReduceRatio_s{};
    // static_param at offset 0x38
    const float* mAccRatio_s{};
    // static_param at offset 0x40
    const float* mWaterFloatRadius_s{};
    // static_param at offset 0x48
    const float* mWaterFloatCycleTime_s{};
    // static_param at offset 0x50
    sead::SafeString mASName_s{};
    f32 _60 = 0.0f;
    f32 _64 = 0.0f;
    f32 _68 = 0.0f;
    f32 _6c = 0.0f;
    f32 _70 = 0.0f;
    ksys::act::CCAccessor _74;
    Unk_7100700620 _7c;
};
KSYS_CHECK_SIZE_NX150(WaterUpDownMoveBase, 0x88);

}  // namespace uking::action
