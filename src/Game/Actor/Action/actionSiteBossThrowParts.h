#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossThrowParts : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossThrowParts, ksys::act::ai::Action)
public:
    explicit SiteBossThrowParts(const InitArg& arg);
    ~SiteBossThrowParts() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

protected:
    void calc_() override;
    virtual const sead::Vector3f* m32() { return mIgniteOffset_s; }
    virtual const sead::Vector3f* m33() { return mIgniteRotate_s; }
    virtual const sead::SafeString& m34();
    virtual void m35();

    // 0x710026e3b0 (not decompiled; 1.7 KB): throws the parts actor.
    void sub_710026E3B0(bool a1);

    // static_param at offset 0x20
    const float* mIgniteSpeed_s{};
    // static_param at offset 0x28
    const float* mMaxNoiseDist_s{};
    // static_param at offset 0x30
    const float* mOffsetHeight_s{};
    // static_param at offset 0x38
    const float* mPredictionFrame_s{};
    // static_param at offset 0x40
    const bool* mIsCalcNextPos_s{};
    // static_param at offset 0x48
    const bool* mIsCheckPlayerAround_s{};
    // static_param at offset 0x50
    sead::SafeString mBaseNode_s{};
    // static_param at offset 0x60
    sead::SafeString mPartsName_s{};
    // static_param at offset 0x70
    sead::SafeString mASName_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mIgniteOffset_s{};
    // static_param at offset 0x88
    const sead::Vector3f* mIgniteRotate_s{};
    // static_param at offset 0x90
    const sead::Vector3f* mIgniteRotSpeed_s{};
    // static_param at offset 0x98
    const sead::Vector3f* mDirMinAngle_s{};
    // static_param at offset 0xa0
    const sead::Vector3f* mDirMaxAngle_s{};
    // dynamic_param at offset 0xa8
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0xb0
    ksys::act::BaseProcHandle** mIgniteBaseProcHandle_d{};
    sead::Vector3f _b8;
};

KSYS_CHECK_SIZE_NX150(SiteBossThrowParts, 0xc8);

}  // namespace uking::action
