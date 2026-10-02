#pragma once

#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

// vtable 0x71023fd380 (IncredibleAction damage callback; no RTTI of its own)
class Unk_71023fd380 : public uking::dmg::DamageCallback {
public:
    explicit Unk_71023fd380(ksys::act::Actor* actor) { _28.acquire(actor, false); }
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    ksys::act::BaseProcLink _28;
    bool _38 = false;
};

namespace uking::ai {

class IncredibleAction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(IncredibleAction, ksys::act::ai::Ai)
public:
    explicit IncredibleAction(const InitArg& arg);
    ~IncredibleAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_7100448C0C(bool);

protected:
    // static_param at offset 0x38
    const bool* mIsInvincible_s{};
    // static_param at offset 0x40
    const bool* mIsUnmoving_s{};
    // static_param at offset 0x48
    const bool* mIsNoCollide_s{};
    // static_param at offset 0x50
    const bool* mIsUseIncredibleActionDCCallback_s{};
    Unk_71023fd380 _58{mActor};
};

}  // namespace uking::ai
