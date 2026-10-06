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
    void calc_() override;
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

    void siteBossStuff();
    void sub_7100478B7C();
    // 0x7100478f78: the non-virtual twin of m39 (same body; called by SiteBossRecognizeRoot).
    void sub_7100478F78(sead::Vector3f* pos);

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

// 0x71025ba278: read by m40 / m41, never written (a debug switch?). Placeholder name.
extern bool sUnk_71025ba278;
KSYS_CHECK_SIZE_NX150(SiteBossRecognizeRootBase, 0x68);

}  // namespace uking::ai
