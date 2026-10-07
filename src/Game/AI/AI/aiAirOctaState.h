#pragma once

#include <container/seadRingBuffer.h>
#include <prim/seadBitFlag.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "Game/AI/AI/aiEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class AirOctaState : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(AirOctaState, EnemyRoot)
public:
    explicit AirOctaState(const InitArg& arg);
    ~AirOctaState() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    void m37() override;
    void m38() override;
    void m39() override;

    void changeToWait(bool a1);
    void sub_71002FDF9C();
    // 0x71002fedd0 (placeholder name): the player got on the board: sets the flags 0x320 and, while waiting, moves to the
    // player's position.
    void sub_71002FEDD0();
    // 0x71002fec08 (placeholder name): forces the notice reaction towards the player while waiting.
    void sub_71002FEC08();

protected:
    // The user data of the message 0x80000c8 (placeholder; only the members that are used).
    struct Payload {
        s32 kind;
        u8 _4[0x14 - 4];
        union {
            f32 value;
            s32 mode;
        };
    };

    // 0x71002fe490 (placeholder name): message kind 6: adds `payload->value` to the height offset of the octas.
    void sub_71002FE490(const Payload* payload);
    // 0x71002fe55c (placeholder name): message kind 11: changes to "オクタの数が減った" while waiting.
    void sub_71002FE55C(const Payload* payload);
    // 0x71002fe668 (placeholder name; declared only): message kind 2: the player is at `distance`.
    void sub_71002FE668(f32 distance);
    // 0x71002fe954 (placeholder name; declared only): the check of message kind 7 with the two angle limits.
    bool sub_71002FE954(f32 a, f32 b);

    // static_param at offset 0x1d8
    const float* mRopeGravityFactor_s{};
    // static_param at offset 0x1e0
    const float* mBalloonMassRatio_s{};
    // static_param at offset 0x1e8
    const float* mWindForceScale_s{};
    // aitree_variable at offset 0x1f0
    void* mAirOctaDataMgr_a{};
    sead::Vector3f _1f8 = sead::Vector3f::zero;
    sead::Vector3f _204{0, 0, 0};
    u32 _210 = 0;
    ksys::act::BaseProcLink _218;
    ksys::act::BaseProcLink _228;
    sead::Matrix33f _238;  // init_: sub_710073FA90(&_238, actor)
    // NON_MATCHING (ctor): the original zero-initialises the whole buffer (0x18 bytes) before its
    // constructor body runs.
    sead::FixedRingBuffer<s32, 1> _260;
    sead::BitFlag32 _278;
};
KSYS_CHECK_SIZE_NX150(AirOctaState, 0x280);

}  // namespace uking::ai
