#pragma once

#include <container/seadObjArray.h>
#include <math/seadVector.h>
#include "Game/Actor/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossMakeClone : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossMakeClone, ksys::act::ai::Ai)
public:
    explicit PriestBossMakeClone(const InitArg& arg);
    ~PriestBossMakeClone() override;

    bool init_(sead::Heap* heap) override;
    void calc_() override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x7100524660 (placeholder name; not decompiled)
    void sub_7100524660(s32 state);
    void sub_7100525270(s32 value);

protected:
    // static_param at offset 0x38
    const int* mRespawnFrame_s{};
    // static_param at offset 0x40
    const float* mBackStepDistance_s{};
    // aitree_variable at offset 0x48
    void* mPriestBossMetaAIUnit_a{};
    /* 0x50 */ s32 mState = 0;
    /* 0x54 */ sead::Vector3f _54 = sead::Vector3f::zero;
    /* 0x60 */ sead::Vector3f _60 = sead::Vector3f::zero;
    /* 0x6c */ sead::Vector3f _6c;
    /* 0x78 */ f32 mRespawnTimer = 0.0f;

    /* 0x80 */ sead::FixedObjArray<Unk_71023b1860, 3> mCloneRecords;
    /* 0x160 */ bool mRespawnStarted = false;
};

KSYS_CHECK_SIZE_NX150(PriestBossMakeClone, 0x168);

}  // namespace uking::ai
