#pragma once

#include "Game/AI/AI/aiPriestBossActorEnemyRoot.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// Placeholder name (vtable 0x7102415ae8; inherits DamageCallback's RTTI; `call` 0x710052d3d4,
// D0 0x710052d7d8). PriestBossShadowCloneEnemyRoot::_230.
class Unk_7102415ae8 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};
KSYS_CHECK_SIZE_NX150(Unk_7102415ae8, 0x28);

class PriestBossShadowCloneEnemyRoot : public PriestBossActorEnemyRoot {
    SEAD_RTTI_OVERRIDE(PriestBossShadowCloneEnemyRoot, PriestBossActorEnemyRoot)
public:
    explicit PriestBossShadowCloneEnemyRoot(const InitArg& arg);
    ~PriestBossShadowCloneEnemyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m45() override;

    void sub_710052D6E8();

protected:
    Unk_7102415ae8 _230;
    Unk_71023b1860 _258{mActor, 0x80000d5};
};
KSYS_CHECK_SIZE_NX150(PriestBossShadowCloneEnemyRoot, 0x290);

}  // namespace uking::ai
