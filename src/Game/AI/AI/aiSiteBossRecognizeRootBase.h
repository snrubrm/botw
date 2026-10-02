#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossRecognizeRootBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossRecognizeRootBase, ksys::act::ai::Ai)
public:
    explicit SiteBossRecognizeRootBase(const InitArg& arg);
    ~SiteBossRecognizeRootBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34(bool on);
    virtual bool m35();
    virtual bool m36();
    virtual void m37();
    virtual void m38(ksys::act::ai::InlineParamPack* params);
    virtual void m39(sead::Vector3f* pos);
    virtual void m40();
    virtual bool m41();

protected:
    // static_param at offset 0x38
    const int* mAttackNum_s{};
    // static_param at offset 0x40
    const int* mAttackRandNum_s{};
    // static_param at offset 0x48
    const float* mWarpStartDist_s{};
    // static_param at offset 0x50
    const float* mForceWarpRetryDist_s{};
    // dynamic_param at offset 0x58
    bool* mIsAttackPatternFixed_d{};
    s32 _60 = 0;
    s32 _64 = 0;
};
KSYS_CHECK_SIZE_NX150(SiteBossRecognizeRootBase, 0x68);

}  // namespace uking::ai
