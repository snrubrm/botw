#pragma once

#include "Game/AI/AI/aiPreyRoot.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// vtable 0x7102426440 (D0 in this TU; m2/m3 are Unk_7102450648's)
class Unk_7102426440 : public Unk_7102450648 {
public:
    explicit Unk_7102426440(u32 type) : Unk_7102450648(type) {}
};

class SunazarashiRoot : public PreyRoot {
    SEAD_RTTI_OVERRIDE(SunazarashiRoot, PreyRoot)
public:
    explicit SunazarashiRoot(const InitArg& arg);
    ~SunazarashiRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool m39() override;
    void m41() override;
    void m42() override;
    void m43() override;
    void m44() override;

    // Unnamed in the binary (0x71005af91c): while towed ("牽引"), tracks the smallest angle between the
    // controller's direction and the contacts; true when the clash speed is exceeded after the angle
    // dropped under ClashAngle.
    bool sub_71005AF91C();

protected:
    // static_param at offset 0x208
    const float* mStunNoiseLevel_s{};
    // static_param at offset 0x210
    const float* mClashSpeed_s{};
    // static_param at offset 0x218
    const float* mClashAngle_s{};
    // static_param at offset 0x220
    const bool* mEnableHangAlways_s{};
    // map_unit_param at offset 0x228
    const bool* mForbidSystemDeleteDistance_m{};
    // aitree_variable at offset 0x230
    sead::Vector3f* mSunazarashiReturnPos_a{};
    Unk_7102426440 _238{0x1800017};
    bool _278 = false;
    bool _279 = false;
    f32 _27c = 0.0f;
    f32 _280 = sead::Mathf::pi();
    sead::Vector3f _284 = sead::Vector3f::zero;
    f32 _290 = 0.0f;
    f32 _294 = 0.0f;
    f32 _298 = 0.0f;
    f32 _29c = 0.0f;
    f32 _2a0 = 0.0f;
};
KSYS_CHECK_SIZE_NX150(SunazarashiRoot, 0x2a8);

}  // namespace uking::ai
