#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DirectToWindDirection : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DirectToWindDirection, ksys::act::ai::Action)
public:
    explicit DirectToWindDirection(const InitArg& arg);
    ~DirectToWindDirection() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpeed_s{};
    // static_param at offset 0x28
    const float* mRotMax_s{};
    // static_param at offset 0x30
    const sead::Vector3f* mFrontDir_s{};
    // static_param at offset 0x38
    const sead::Vector3f* mUpDir_s{};
    u64 _40 = 0;
    sead::Vector3f _48 = sead::Vector3f::zero;
    f32 _54 = 0.0f;
    sead::Vector3f _58 = sead::Vector3f::zero;
    u8 _64[0x4];

};
KSYS_CHECK_SIZE_NX150(DirectToWindDirection, 0x68);

}  // namespace uking::action
