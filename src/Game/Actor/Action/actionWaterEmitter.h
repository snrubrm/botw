#pragma once

#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaterEmitter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WaterEmitter, ksys::act::ai::Action)
public:
    explicit WaterEmitter(const InitArg& arg);
    ~WaterEmitter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mEffectType_s{};
    // static_param at offset 0x28
    const float* mRadius_s{};
    // static_param at offset 0x30
    const float* mSpeed_s{};
    // static_param at offset 0x38
    const float* mInterval_s{};
    // static_param at offset 0x40
    sead::SafeString mBindNodeName_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mOffset_s{};
    // static_param at offset 0x58
    const sead::Vector3f* mVelocityDir_s{};
    u64 _60 = 0;
    f32 _68 = 0.0f;
    u8 _6c[0x4];
    gsys::BoneAccessKeyEx _70;
};
KSYS_CHECK_SIZE_NX150(WaterEmitter, 0xa8);

}  // namespace uking::action
