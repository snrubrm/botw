#pragma once

#include <math/seadVector.h>
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class GuardianMini2ndBattleAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMini2ndBattleAttack, ksys::act::ai::Ai)
public:
    explicit GuardianMini2ndBattleAttack(const InitArg& arg);
    ~GuardianMini2ndBattleAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_7100412CDC();
    void sub_7100412DE8();

    // vtable 0x71023f78a8 (no RTTI of its own)
    class Unk_71023f78a8 : public dmg::DamageCallback {
    public:
        explicit Unk_71023f78a8(GuardianMini2ndBattleAttack* owner) : mOwner(owner) {}
        void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                  dmg::DamageCallbackInfo* a6) override;

        GuardianMini2ndBattleAttack* mOwner;
    };

    // vtable 0x71023f78e0 (no RTTI of its own)
    class Unk_71023f78e0 : public dmg::DamageCallback {
    public:
        explicit Unk_71023f78e0(GuardianMini2ndBattleAttack* owner) : mOwner(owner) {}
        void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                  dmg::DamageCallbackInfo* a6) override;

        GuardianMini2ndBattleAttack* mOwner;
    };

protected:
    // static_param at offset 0x38
    sead::SafeString mAscendingCurrentName_s{};
    // static_param at offset 0x48
    const int* mAscendingCurrentTime_s{};
    // aitree_variable at offset 0x50
    int* mGuardianMiniChanceTimeState_a{};
    sead::Vector3f _58{0, 0, 0};
    ksys::act::BaseProcLink _68;
    ksys::Timer _78{0, 0};
    Unk_71023f78a8 _88{this};
    Unk_71023f78e0 _b8{this};
};
KSYS_CHECK_SIZE_NX150(GuardianMini2ndBattleAttack, 0xe8);

}  // namespace uking::ai
