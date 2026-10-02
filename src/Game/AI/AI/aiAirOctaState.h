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

    void m37() override;
    void m38() override;
    void m39() override;

    void sub_71002FD098(bool a1);
    void sub_71002FDF9C();

protected:
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
