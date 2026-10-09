#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "Game/Actor/actUnk_7102366570.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actAiAi.h"

class Unk_71023f83e8;
class Unk_71023f94f8;

namespace uking::ai {

// Returns the root AI's "IsAnnihilateDungeonEnemy" map unit parameter (false if missing).
bool sub_71004282EC(ksys::act::Actor* actor);

// Placeholder name (vtable 0x71023f94c0; D1 is the base's, D0 0x7100428da0). GuardianMiniRoot::_398.
// NON_MATCHING: the implicit deleting destructor calls the existing out-of-line base cleanup.
class Unk_71023f94c0 : public Unk_7102366570 {
public:
    // 0x7100428c74 (declaration only)
    void call(ksys::act::Actor* actor) override;

    bool _20 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71023f94c0, 0x28);

class GuardianMiniRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(GuardianMiniRoot, EnemyRoot)
public:
    explicit GuardianMiniRoot(const InitArg& arg);
    ~GuardianMiniRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void m37() override;
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
    bool _208 = false;
    bool _209 = false;
    bool _20a = false;
    f32 _20c = 0;
    f32 _210 = 0;
    f32 _214 = 0;
    s32 _218 = 0;
    bool _21c = true;
    u32 _220 = 0;
    Unk_7102450498 _228;
    Unk_71023f83e8* _278 = nullptr;
    Unk_71023f94f8* _280 = nullptr;
    ksys::act::BoneHandle _288;
    // Three pairs (ELink, SLink) of xlink handles (the six {pointer, id} pairs initialised by the constructor).
    Unk_71012419b4 _330[3];
    u8 _390[3];
    bool _393[3];
    Unk_71023f94c0 _398;

    // 0x71004262d4 (placeholder name): kills the ELink and fades the SLink event of the three handle pairs.
    void stopXLinks();
    void sub_71004267E4();
    bool sub_710042699C();
    void sub_7100427338();
    void sub_7100427574();
    void sub_7100427940();
};

}  // namespace uking::ai
