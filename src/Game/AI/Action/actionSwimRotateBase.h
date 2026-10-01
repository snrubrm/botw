#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/Action/actionWaterFloatBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class SwimRotateBase : public WaterFloatBase {
    SEAD_RTTI_OVERRIDE(SwimRotateBase, WaterFloatBase)
public:
    explicit SwimRotateBase(const InitArg& arg);
    ~SwimRotateBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x60
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x68
    const float* mRotSpeed_s{};
    // static_param at offset 0x70
    const float* mRotRatio_s{};
    sead::Matrix33f _78;
    ksys::VFRValue _9c;
};

KSYS_CHECK_SIZE_NX150(SwimRotateBase, 0xa8);

}  // namespace uking::action
