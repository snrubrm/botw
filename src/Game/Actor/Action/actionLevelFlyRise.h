#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LevelFlyRise : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LevelFlyRise, ksys::act::ai::Action)
public:
    explicit LevelFlyRise(const InitArg& arg);
    ~LevelFlyRise() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mHeight_s{};
    // static_param at offset 0x28
    const float* mSpeed_s{};
    // static_param at offset 0x30
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x38
    const float* mRotRatio_s{};
    // static_param at offset 0x40
    sead::SafeString mASName_s{};
    ksys::VFRValue _50;
    sead::Matrix33f _5c;
    sead::Vector3f _80;
    f32 _8c = 0.0f;
    f32 _90 = 0.0f;
    f32 _94 = 0.0f;
    f32 _98 = 0.0f;
    ksys::act::CCAccessor _9c;
    u8 _a4[0x4];
};
KSYS_CHECK_SIZE_NX150(LevelFlyRise, 0xa8);

}  // namespace uking::action
