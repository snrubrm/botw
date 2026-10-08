#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// Returns the root AI's "IsAnnihilateDungeonEnemy" map unit parameter (false if missing).
bool sub_71004282EC(ksys::act::Actor* actor);

class GuardianMiniRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(GuardianMiniRoot, EnemyRoot)
public:
    explicit GuardianMiniRoot(const InitArg& arg);
    ~GuardianMiniRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    // static_param at offset 0x1d8
    const float* mNeckRotRatio_s{};
    // static_param at offset 0x1e0
    const int* mJustGuardNumForBreak_s{};
    // static_param at offset 0x1e8
    const float* mRotStopSpeed_s{};
    // aitree_variable at offset 0x1f0
    int* mDamagedCount_a{};
    // aitree_variable at offset 0x1f8
    bool* mIsTransformedGuardianMini_a{};
    // aitree_variable at offset 0x200
    int* mGuardianMiniChanceTimeState_a{};
    // The members from 0x208 to 0x228 are not modelled yet (see the constructor 0x7100426060).
    u8 _208[4];
    f32 _20c;
    f32 _210;
    f32 _214;
    s32 _218;
    bool _21c;
    u8 _21d[0x228 - 0x21d];
    Unk_7102450498 _228;
    // The members from 0x278 to 0x288 are not modelled yet (see the constructor 0x7100426060).
    u8 _278[0x288 - 0x278];
    ksys::act::BoneHandle _288;
    // Three pairs (ELink, SLink) of xlink handles (the six {pointer, id} pairs initialised by the constructor).
    Unk_71012419b4 _330[3];
    u8 _390[3];
    bool _393[3];
    u8 _396[0x3c0 - 0x396];

    // 0x71004262d4 (placeholder name): kills the ELink and fades the SLink event of the three handle pairs.
    void stopXLinks();
};

}  // namespace uking::ai
