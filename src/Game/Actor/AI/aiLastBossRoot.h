#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::act {
class LastBoss;
}

namespace uking::ai {

class LastBossRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LastBossRoot, ksys::act::ai::Ai)
public:
    explicit LastBossRoot(const InitArg& arg);
    ~LastBossRoot() override;

    bool hasPreDeleteCb() override;
    void onPreDelete() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    // 0x710047a374 (placeholder name; CSV calc_x): whether calc_ should switch to the reaction child (death,
    // just guard, damage reactions, or an active ShockWave part attack).
    bool sub_710047A374(act::LastBoss* boss);
    // 0x7100479f74 (placeholder name; CSV calc_x_0): picks the barrier / damage / wait animation.
    void sub_7100479F74(act::LastBoss* boss, bool update_wait);

protected:
    // static_param at offset 0x38
    const int* mForceRecoverHitMax_s{};
    // static_param at offset 0x40
    const int* mForceRecoverDamageMax_s{};
    // static_param at offset 0x48
    const int* mAddForceRecoverHitNum_s{};
    // static_param at offset 0x50
    const int* mAddForceRecoverDamage_s{};
    // static_param at offset 0x58
    const float* mAuraHPRate_s{};
    // static_param at offset 0x60
    sead::SafeString mAuraDemoName_s{};
    // static_param at offset 0x70
    sead::SafeString mAuraEntryName_s{};
    // static_param at offset 0x80
    sead::SafeString mAuraWallEntry_s{};
    // static_param at offset 0x90
    sead::SafeString mAuraDemoDownEntry_s{};
    sead::SafeString _a0;
    u32 _b0 = 0;
    bool _b4 = false;
    bool _b5 = false;
    bool _b6 = false;
    ksys::Timer _b8;
    ksys::Timer _c4;
    ksys::Timer _d0;
    u32 _dc = 0;
};
KSYS_CHECK_SIZE_NX150(LastBossRoot, 0xe0);

}  // namespace uking::ai
