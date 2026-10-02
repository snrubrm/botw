#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::act {
class SiteBoss;
}

namespace uking::ai {

class SiteBossRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossRoot(const InitArg& arg);
    ~SiteBossRoot() override;
    bool hasPreDeleteCb() override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void onPreDelete() override;
    bool handleMessage_(const ksys::Message& message) override;

    virtual void m34(act::SiteBoss* boss);
    virtual bool m35(act::SiteBoss* boss);

    void x();

protected:
    // static_param at offset 0x38
    const int* mOffFlagIndexAtClipping_s{};
    // static_param at offset 0x40
    const int* mAddAttackPower_s{};
    // static_param at offset 0x48
    const int* mForceRecoverHitMax_s{};
    // static_param at offset 0x50
    const int* mForceRecoverDamageMax_s{};
    // static_param at offset 0x58
    const int* mAddForceRecoverHitNum_s{};
    // static_param at offset 0x60
    const int* mAddForceRecoverDamage_s{};
    // static_param at offset 0x68
    const int* mBlownOffAtWeakPointHitNum_s{};
    // static_param at offset 0x70
    const float* mDemoPlayHPRate_s{};
    // static_param at offset 0x78
    const float* mWeakPointDamageRate_s{};
    // static_param at offset 0x80
    const bool* mIsRemainBoss_s{};
    // static_param at offset 0x88
    sead::SafeString mDemoName_s{};
    // static_param at offset 0x98
    sead::SafeString mNormalEntryName_s{};
    // static_param at offset 0xa8
    sead::SafeString mAtDownEntryName_s{};
    // static_param at offset 0xb8
    sead::SafeString mIsPlayed_DemoFlagName_s{};
    // map_unit_param at offset 0xc8
    sead::SafeString mUniqueNameMessageLabel_m{};
    bool _d8 = false;
    bool _d9 = false;
    bool _da = false;
    ksys::Timer _dc{};
    u32 _e8 = 0;
    u32 _ec = 0;
    f32 _f0 = 0;
    s32 _f4 = 0;
};
KSYS_CHECK_SIZE_NX150(SiteBossRoot, 0xf8);

}  // namespace uking::ai
