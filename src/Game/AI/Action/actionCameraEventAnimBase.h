#pragma once

#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

class CameraEventAnimBase : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventAnimBase, CameraEvent)
public:
    explicit CameraEventAnimBase(const InitArg& arg);
    ~CameraEventAnimBase() override = default;

    bool handleMessage_(const ksys::Message* message) override;

protected:
    bool m39() override { return false; }
    void m45() override;
    void m46() override;

    virtual void m47();
    virtual void m48();
    virtual float m49();
    virtual void m50(sead::BufferedSafeString* out);
    virtual bool m51() { return false; }
    virtual u8 m52();
    virtual void m53();
    virtual const sead::SafeString& m54();
    virtual const sead::SafeString& m55();
    virtual u8 m56();
    virtual void m57();
    virtual u8 m58();
    virtual void m59();
    virtual bool m60();

    // 0x7100757a78 / 0x7100757c24 (non-virtual helpers, declared only).
    void sub_7100757A78();
    void sub_7100757C24();

    ksys::act::BaseProcLink _50;
    sead::Matrix34f _60 = sead::Matrix34f::ident;
    int _90 = 0;
    f32 _94;
    f32 _98;
    f32 _9c;
    f32 _a0 = 0;
    f32 _a4 = 0;
    f32 _a8 = 0;
    f32 _ac = 0;
    f32 _b0 = 0;
    f32 _b4 = 0;
    f32 _b8 = 0;
    act::Unk_7102459dd8 _c0;
    // dynamic_param at offset 0xe0
    sead::SafeString mSceneName_d;
    // dynamic_param at offset 0xf0
    sead::SafeString mCameraName_d;
    // dynamic2_param at offset 0x100
    float* mStartFrame_d{};
    // dynamic2_param at offset 0x108
    float* mEndFrame_d{};
    // dynamic2_param at offset 0x110
    float* mDOFStartFrame_d{};
    // dynamic2_param at offset 0x118
    float* mFocalLength_d{};
    // dynamic2_param at offset 0x120
    float* mAperture_d{};
    // dynamic2_param at offset 0x128
    float* mDOFBlurStart_d{};
    // dynamic2_param at offset 0x130
    float* mDOFEndFrame_d{};
    // dynamic2_param at offset 0x138
    float* mFocalLengthEnd_d{};
    // dynamic2_param at offset 0x140
    float* mApertureEnd_d{};
    // dynamic2_param at offset 0x148
    float* mDOFBlurEnd_d{};
    // dynamic2_param at offset 0x150
    float* mOverwriteAtDist_d{};
    // dynamic2_param at offset 0x158
    float* mInterpolateCount_d{};
    // dynamic2_param at offset 0x160
    bool* mDOFUse_d{};
    // dynamic2_param at offset 0x168
    bool* mOverwriteAt_d{};
    // dynamic2_param at offset 0x170
    bool* mBgCheck_d{};
    u8 _178 = 0;
    u8 _179 = 0;
    u8 _17a = 0;
};

}  // namespace uking::action
