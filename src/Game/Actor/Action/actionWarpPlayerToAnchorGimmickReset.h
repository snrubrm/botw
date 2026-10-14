#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpPlayerToAnchorGimmickReset : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpPlayerToAnchorGimmickReset, ksys::act::ai::Action)
public:
    explicit WarpPlayerToAnchorGimmickReset(const InitArg& arg);
    ~WarpPlayerToAnchorGimmickReset() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mWaitFrameAfterReset_s{};
    // map_unit_param at offset 0x28
    sead::SafeString mAnchorName_m{};
    // map_unit_param at offset 0x38
    sead::SafeString mAnchorUniqueName_m{};
    sead::Vector3f _48 = sead::Vector3f::zero;
    bool _54 = false;
    u8 _55[0x3];
    f32 _58 = 0.0f;
    u8 _5c[0x4];
};
KSYS_CHECK_SIZE_NX150(WarpPlayerToAnchorGimmickReset, 0x60);

}  // namespace uking::action
