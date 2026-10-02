#pragma once

#include <math/seadVector.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraLockOnBase : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraLockOnBase, CameraAction)
public:
    // Placeholder (initialised member by member in the ctor, copied by m52): a position followed by
    // three values (the last two angles in degrees).
    struct Unk88 {
        sead::Vector3f _0 = sead::Vector3f::zero;
        f32 _c = 0;
        f32 _10 = angleStuff(0.0f);
        f32 _14 = angleStuff(0.0f);
    };

    explicit CameraLockOnBase(const InitArg& arg);
    ~CameraLockOnBase() override;

protected:
    bool m32(sead::Heap* heap) override;
    void m36() override;

    virtual bool m42(sead::Heap* heap);
    virtual void m43();
    virtual float m44();
    virtual float m45();
    // 0x71007864a8 (declared only): updates the angles from `polar`.
    virtual void m46(act::Unk_7100922700* polar, bool b);
    virtual void* m47() { return nullptr; }
    virtual void* m48() { return nullptr; }
    virtual void* m49() { return nullptr; }
    virtual void* m50() { return nullptr; }
    virtual bool m51();
    virtual void m52();
    virtual void m53() {}
    virtual void m54() {}
    virtual bool m55() { return false; }
    virtual void m56() {}
    virtual void m57() {}
    virtual int m58() { return 0; }
    virtual int m59() { return -1; }
    virtual bool m60(int idx) { return false; }

    sead::Vector3f _4c = sead::Vector3f::zero;
    sead::Vector3f _58 = sead::Vector3f::zero;
    sead::Vector3f _64 = sead::Vector3f::zero;
    sead::Vector3f _70 = sead::Vector3f::zero;
    sead::Vector3f _7c = sead::Vector3f::zero;
    Unk88 _88;
    Unk88 _a0;
    f32 _b8 = 0;
    f32 _bc = 0;
    f32 _c0 = 0;
    f32 _c4 = 0;
    f32 _c8 = 0;
    f32 _cc = 0;
    f32 _d0 = 0;
    f32 _d4 = 0;
    f32 _d8 = 0;
    f32 _dc = 0;
    f32 _e0 = 0;
    f32 _e4 = 0;
    f32 _e8 = 0;
    f32 _ec = 0;
    f32 _f0 = 0;
    s32 _f4 = -1;
    s32 _f8 = -1;
    // static_param at offset 0x100
    const float* mDistMin_s{};
    // static_param at offset 0x108
    const float* mDistMax_s{};
    // static_param at offset 0x110
    const float* mAtOffsetVNear_s{};
    // static_param at offset 0x118
    const float* mAtOffsetVFar_s{};
    // static_param at offset 0x120
    const float* mAtCus_s{};
    // static_param at offset 0x128
    const float* mAtOffsetCus_s{};
    // static_param at offset 0x130
    const float* mLatVDiffEffect_s{};
    // static_param at offset 0x138
    const float* mLatOffsetNear_s{};
    // static_param at offset 0x140
    const float* mLatOffsetFar_s{};
    // static_param at offset 0x148
    const float* mLatMin_s{};
    // static_param at offset 0x150
    const float* mLatMax_s{};
    // static_param at offset 0x158
    const float* mLatCus_s{};
    // static_param at offset 0x160
    const float* mLngNear_s{};
    // static_param at offset 0x168
    const float* mLngFar_s{};
    // static_param at offset 0x170
    const float* mLngMax_s{};
    // static_param at offset 0x178
    const float* mLngCus_s{};
    // static_param at offset 0x180
    const float* mRadiusNear_s{};
    // static_param at offset 0x188
    const float* mRadiusFar_s{};
    // static_param at offset 0x190
    const float* mRadiusCus_s{};
    // static_param at offset 0x198
    const float* mFovyNear_s{};
    // static_param at offset 0x1a0
    const float* mFovyFar_s{};
    // static_param at offset 0x1a8
    const float* mFovyCus_s{};
    f32 _1b0 = 0;
    f32 _1b4 = 0;
    f32 _1b8 = 0;
    u8 _1bc = 0;
    u8 _1bd = 0;
    u8 _1be = 2;
};

}  // namespace uking::action
