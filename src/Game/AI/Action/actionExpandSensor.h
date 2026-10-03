#pragma once

#include <math/seadVector.h>
#include "Game/AI/aiUnk_71010C3588.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ExpandSensor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ExpandSensor, ksys::act::ai::Action)
public:
    explicit ExpandSensor(const InitArg& arg);
    ~ExpandSensor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    struct Params {
        // static_param at offset 0x20
        const int* mAtkAttrType_s{};
        // static_param at offset 0x28
        const int* mAtkType_s{};
        // static_param at offset 0x30
        const float* mOffLength_s{};
        // static_param at offset 0x38
        const float* mOnLength_s{};
    };
    Params mParams;
    /* 0x40 */ Unk_710250c260 _40;
    /* 0xb0 */ sead::Vector3f _b0 = sead::Vector3f::zero;
    /* 0xbc */ sead::Vector3f _bc = sead::Vector3f::zero;
    /* 0xc8 */ sead::Vector3f _c8 = sead::Vector3f::zero;
    /* 0xd4 */ f32 _d4 = 1.0f;
    /* 0xd8 */ bool _d8 = false;
    bool _d9 = false;
};

}  // namespace uking::action
