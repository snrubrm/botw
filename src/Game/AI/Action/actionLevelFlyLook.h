#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LevelFlyLook : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LevelFlyLook, ksys::act::ai::Action)
public:
    explicit LevelFlyLook(const InitArg& arg);
    ~LevelFlyLook() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual float m32();
    virtual bool m33(float x);

    // static_param at offset 0x20
    const float* mHeight_s{};
    // static_param at offset 0x28
    const float* mSpeed_s{};
    // static_param at offset 0x30
    const float* mRotSpeed_s{};
    // static_param at offset 0x38
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x40
    const float* mRotRatio_s{};
    // static_param at offset 0x48
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    float _60{};
    float _64{};
    sead::Vector3f _68;
    sead::Vector3f _74;
    sead::Vector3f _80;
    float _8c{};
    float _90{};
    float _94{};
    float _98{};
    float _9c{};
    float _a0{};
    float _a4{};
};

}  // namespace uking::action
