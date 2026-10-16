#pragma once

#include "Game/Actor/AI/aiEnemyRoot.h"
#include "Game/Actor/aiUnk_7102357210.h"
#include "Game/Actor/aiUnk_7102451120.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::ai {

// Placeholder name (vtable 0x710241c6c0; own RTTI, checkDerived 0x710055e77c; `call` 0x710055d7c8,
// D0 0x710055e8a4). SandwormRoot::_250.
class Unk_710241c6c0 : public act::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_710241c6c0, act::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6) override;

    f32 _24 = 1.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_710241c6c0, 0x28);

class SandwormRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(SandwormRoot, EnemyRoot)
public:
    explicit SandwormRoot(const InitArg& arg);
    ~SandwormRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void calc_() override;

    // 0x710055e304 (unnamed in the CSV; called at the end of calc_): shows the life gauge while the player is within
    // the Sandworm GParamList ShowLifeGageDist (hides it beyond ShowLifeGageDist + ShowLifeGageOffset).
    void sub_710055E304();

protected:
    // static_param at offset 0x1d8
    const float* mSandOffset_s{};
    // static_param at offset 0x1e0
    const float* mWeakPointDamageRate_s{};
    Unk_710240dd68 _1e8;
    // calc_ updates it with Unk_7100d3bce4::sub_7100D3BCE4 (0x710055e090) and restarts it at 8.
    ksys::act::Unk_7100d3bce4 _238{mActor, 0.0f};
    Unk_710241c6c0 _250;
    Unk_7102451120 _278;
    u32 _288 = 0;
};
KSYS_CHECK_SIZE_NX150(SandwormRoot, 0x290);

}  // namespace uking::ai
