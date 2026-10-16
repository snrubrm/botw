#pragma once

#include <prim/seadBitFlag.h>

#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

#include "Game/Actor/AI/aiEnemyRoot.h"
#include "Game/Actor/aiUnk_7102357210.h"
#include "Game/Actor/aiUnk_7102451120.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormRRoot;

// Placeholder name (vtable 0x710241c878; inherits DamageCallback's RTTI; `call` 0x710055fbec,
// D0 0x710055fce0). SandwormRRoot::_258.
class Unk_710241c878 : public act::DamageCallback {
public:
    explicit Unk_710241c878(SandwormRRoot* owner) : mOwner(owner) {}

    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6) override;

    SandwormRRoot* mOwner;
};
KSYS_CHECK_SIZE_NX150(Unk_710241c878, 0x30);

class SandwormRRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(SandwormRRoot, EnemyRoot)
public:
    explicit SandwormRRoot(const InitArg& arg);
    ~SandwormRRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void calc_() override;

    // 0x710055f3e0 (unnamed in the CSV): the same life gauge update as SandwormRoot::sub_710055E304.
    void sub_710055F3E0();

    virtual void m45(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6,
                     act::DamageManager* damage_mgr);

protected:
    // static_param at offset 0x1d8
    const float* mSandOffset_s{};
    // static_param at offset 0x1e0
    const float* mWeakPointDamageRate_s{};
    // static_param at offset 0x1e8
    const float* mWeakChimicalDamageRate_s{};
    Unk_710240dd68 _1f0;
    // calc_ updates it with Unk_7100d3bce4::sub_7100D3BCE4 and restarts it at 8 (as SandwormRoot::_238).
    ksys::act::Unk_7100d3bce4 _240{mActor, 0.0f};
    Unk_710241c878 _258{this};
    Unk_7102451120 _288;
    u32 _298 = 0;
    sead::BitFlag8 _29c;  // bit i: the actor has weapon i (set by enter_ for tagged actors)
};
KSYS_CHECK_SIZE_NX150(SandwormRRoot, 0x2a0);

}  // namespace uking::ai
