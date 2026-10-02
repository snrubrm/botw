#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102451120.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormRRoot;

// Placeholder name (vtable 0x710241c878; inherits DamageCallback's RTTI; `call` 0x710055fbec,
// D0 0x710055fce0). SandwormRRoot::_258.
class Unk_710241c878 : public dmg::DamageCallback {
public:
    explicit Unk_710241c878(SandwormRRoot* owner) : mOwner(owner) {}

    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

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

    virtual void m45(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6,
                     dmg::DamageManager* damage_mgr);

protected:
    // static_param at offset 0x1d8
    const float* mSandOffset_s{};
    // static_param at offset 0x1e0
    const float* mWeakPointDamageRate_s{};
    // static_param at offset 0x1e8
    const float* mWeakChimicalDamageRate_s{};
    Unk_710240dd68 _1f0;
    ksys::act::Actor* _240 = mActor;
    u64 _248 = 0;
    u32 _250 = 0;
    Unk_710241c878 _258{this};
    Unk_7102451120 _288;
    u32 _298 = 0;
    bool _29c = false;
};
KSYS_CHECK_SIZE_NX150(SandwormRRoot, 0x2a0);

}  // namespace uking::ai
