#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include "Game/AI/AI/aiEnemyRoot.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

class Unk_7102450fa8;

namespace uking::ai {

class PriestBossActorEnemyRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(PriestBossActorEnemyRoot, EnemyRoot)
public:
    explicit PriestBossActorEnemyRoot(const InitArg& arg);
    ~PriestBossActorEnemyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void calc_() override;

    void m34(ksys::act::ai::InlineParamPack* params) override;
    bool m35() override;
    virtual bool m45();
    virtual bool m46();
    virtual bool m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual bool m51();
    virtual bool m52();
    virtual bool m53();

    void sub_7100507440(bool a1);
    Unk_7102450fa8* sub_7100506A40();

protected:
    // Bit indices of _228 (a SEAD_ENUM in the original: the index goes through a stack round trip).
    SEAD_ENUM(Flag, _0, _1, _2, _3)

    void sub_7100506DB0();

    // static_param at offset 0x1d8
    const bool* mIsReactionOnDead_s{};
    // aitree_variable at offset 0x1e0
    void* mPriestBossMetaAIUnit_a{};
    u32 _1e8 = 4;
    Unk_7102411178 _1f0{mActor, 0x80000dc};
    sead::BitFlag32 _228;
    bool _22c = false;
};
KSYS_CHECK_SIZE_NX150(PriestBossActorEnemyRoot, 0x230);

}  // namespace uking::ai
