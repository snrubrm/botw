#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class LastBossRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LastBossRoot, ksys::act::ai::Ai)
public:
    explicit LastBossRoot(const InitArg& arg);
    ~LastBossRoot() override;

    bool hasPreDeleteCb() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

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
