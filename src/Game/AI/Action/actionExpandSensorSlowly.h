#pragma once

#include <math/seadVector.h>
#include "Game/AI/aiUnk_71010C3588.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ExpandSensorSlowly : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ExpandSensorSlowly, ksys::act::ai::Action)
public:
    explicit ExpandSensorSlowly(const InitArg& arg);
    ~ExpandSensorSlowly() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710005a348 (declared only): the body of leave_ is out of line in the original.
    void sub_710005A348();
    void calc_() override;

    // static_param at offset 0x20
    const int* mAtkAttrType_s{};
    // static_param at offset 0x28
    const int* mAtkType_s{};
    // static_param at offset 0x30
    const float* mOffLength_s{};
    // static_param at offset 0x38
    const float* mOnLength_s{};
    // static_param at offset 0x40
    const float* mAtExpandStep_s{};
    /* 0x48 */ Unk_710250c260 _48;
    /* 0xb8 */ sead::Vector3f _b8 = sead::Vector3f::zero;
    /* 0xc4 */ sead::Vector3f _c4 = sead::Vector3f::zero;
    /* 0xd0 */ sead::Vector3f _d0 = sead::Vector3f::zero;
    /* 0xdc */ sead::Vector3f _dc{1, 1, 1};
    /* 0xe8 */ bool _e8 = false;
    bool _e9 = false;
};

}  // namespace uking::action
