#pragma once

#include <container/seadSafeArray.h>
#include <math/seadMatrix.h>

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BowChildArrowRain : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BowChildArrowRain, ksys::act::ai::Action)
public:
    explicit BowChildArrowRain(const InitArg& arg);
    ~BowChildArrowRain() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;
    // 0x71000ce328 (placeholder name): false while one of the 24 actors bound by the parent SiteBoss is in its calc
    // state.
    bool sub_71000CE328();
    // 0x71000cd2a8 (placeholder name): moves _d8 to the next bound actor of the parent SiteBoss (stepping by
    // +1 / -1 by the parity of ID, skipping ID) and writes its position when it is in its calc state.
    bool sub_71000CD2A8(sead::Vector3f* pos);
    // 0x71000cd040 (placeholder name): updates _12c._3d8 for the 24 bound actors of the parent SiteBoss.
    void sub_71000CD040();
    // 0x71000cdeec (placeholder name): moves the main body to `pos` (or _120 unless `use_pos`) with the
    // rotation _dc turned by XRotateAngle about the x axis.
    void sub_71000CDEEC(const sead::Vector3f& pos, bool use_pos);
    // 0x71000ce0c0 (placeholder name): sends a shot (message 0x8000056) to every bound actor of the parent
    // SiteBoss that has just entered range, starting the slot countdowns the first time.
    void sub_71000CE0C0();

    // static_param at offset 0x20
    const int* mRainMax_s{};
    // static_param at offset 0x28
    const float* mMoveSpeed_s{};
    // static_param at offset 0x30
    const float* mMoveHeight_s{};
    // static_param at offset 0x38
    const float* mWaitTime_s{};
    // static_param at offset 0x40
    const float* mMoveCountNum_s{};
    // static_param at offset 0x48
    const float* mMoveRange_s{};
    // static_param at offset 0x50
    const float* mMoveOffsetBase_s{};
    // static_param at offset 0x58
    const float* mRotateRate_s{};
    // static_param at offset 0x60
    const float* mRotateStepMax_s{};
    // static_param at offset 0x68
    const float* mAngleToTarget_s{};
    // static_param at offset 0x70
    const float* mTargetOffsetBase_s{};
    // static_param at offset 0x78
    const float* mRainScale_s{};
    // static_param at offset 0x80
    const float* mToTargetTime_s{};
    // dynamic_param at offset 0x88
    int* mID_d{};
    // dynamic_param at offset 0x90
    float* mXRotateAngle_d{};
    // dynamic_param at offset 0x98
    bool* mIsIgnoreHightOffset_d{};
    // dynamic_param at offset 0xa0
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0xa8
    sead::Vector3f* mMoveTargetPos_d{};
    // dynamic_param at offset 0xb0
    ksys::act::BaseProcLink* mParentActor_d{};

    s32 _b8 = 0;
    s32 _bc = 0;
    f32 _c0 = 0;
    f32 _c4 = 0;
    f32 _c8 = 0;
    f32 _cc = 0;
    bool _d0 = false;
    bool _d1 = false;
    bool _d2 = false;
    s32 _d4 = 0;
    s32 _d8 = 0;
    sead::Matrix33f _dc;
    // Frame countdowns of the five arrow rain slots (calc_ fires one when it reaches 0).
    sead::SafeArray<s32, 5> _100{};
    u8 _114[0xc];
    sead::Vector3f _120;
    // Placeholder layout of the block at 0x12c (0x408 bytes, zero-initialised as a whole).
    struct Unk12c {
        // A shot for each bound actor of the parent SiteBoss (0x71000ce750), sent with message 0x8000056.
        struct Shot {
            bool has_target;
            sead::Vector3f from;
            sead::Vector3f target;
            sead::Vector3f to;
        };
        Shot _0[24];
        sead::Vector3f _3c0{0, 0, 0};
        sead::Vector3f _3cc{0, 0, 0};
        // Per bound actor of the parent SiteBoss (0x71000cd040): `entered` is set for one frame when it comes
        // within one frame's movement of this actor, `inside` while it is.
        struct BoundActorState {
            bool entered;
            bool inside;
        };
        BoundActorState _3d8[24]{};
    };
    Unk12c _12c{};

    // 0x71000ce750 (placeholder name): fills `shot` from this actor towards TargetPos (randomised by TargetOffsetBase
    // after the second shot).
    void sub_71000CE750(Unk12c::Shot* shot);
};

}  // namespace uking::action
