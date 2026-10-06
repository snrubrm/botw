#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102451120.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// Placeholder name (vtable 0x710241c6c0; own RTTI, checkDerived 0x710055e77c; `call` 0x710055d7c8,
// D0 0x710055e8a4). SandwormRoot::_250.
class Unk_710241c6c0 : public dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_710241c6c0, dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) override;

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

protected:
    // static_param at offset 0x1d8
    const float* mSandOffset_s{};
    // static_param at offset 0x1e0
    const float* mWeakPointDamageRate_s{};
    Unk_710240dd68 _1e8;
    ksys::act::Actor* _238 = mActor;
    u64 _240 = 0;
    u32 _248 = 0;
    Unk_710241c6c0 _250;
    Unk_7102451120 _278;
    u32 _288 = 0;
};
KSYS_CHECK_SIZE_NX150(SandwormRoot, 0x290);

}  // namespace uking::ai
