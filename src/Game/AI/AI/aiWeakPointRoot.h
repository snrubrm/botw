#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

// Placeholder name (vtable 0x710242fcf0; inherits DamageCallback's RTTI; D0 0x71005ef28c, `call`
// 0x71005edb04). WeakPointRoot::_70.
class Unk_710242fcf0 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    bool _24 = false;
    bool _25 = false;
    u8 _26[2];  // not initialised by the owner's ctor
    bool _28 = false;
    bool _29 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_710242fcf0, 0x30);

class WeakPointRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WeakPointRoot, ksys::act::ai::Ai)
public:
    explicit WeakPointRoot(const InitArg& arg);
    ~WeakPointRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    virtual s32 m34(dmg::DamageManagerBase* mgr);
    virtual s32 m35(dmg::DamageManagerBase* mgr);

protected:
    // static_param at offset 0x38
    const int* mOwnerDamage_s{};
    // static_param at offset 0x40
    const bool* mIsBreakable_s{};
    // static_param at offset 0x48
    const bool* mIsSyncDamage_s{};
    // static_param at offset 0x50
    const bool* mIsShowCriticalEffect_s{};
    // static_param at offset 0x58
    const bool* mIsNoReaction_s{};
    ksys::act::BaseProcLink _60;
    Unk_710242fcf0 _70;
    Unk_71023afc10 _a0;
    Unk_71023afbe0 _d8;
    Unk_710242fd28 _110;
    Unk_710242fd58 _148;
};
KSYS_CHECK_SIZE_NX150(WeakPointRoot, 0x180);

}  // namespace uking::ai
