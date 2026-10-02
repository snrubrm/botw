#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "Game/AI/aiUnk_7102431fa8.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WizzrobeRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(WizzrobeRoot, EnemyRoot)
public:
    explicit WizzrobeRoot(const InitArg& arg);
    ~WizzrobeRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m37() override;

protected:
    // static_param at offset 0x1d8
    const int* mMagicTargetIdx_s{};
    // static_param at offset 0x1e0
    sead::SafeString mStartASName_s{};
    // static_param at offset 0x1f0
    sead::SafeString mStopASName_s{};
    // aitree_variable at offset 0x200
    void* mWizzrobeMagicWeatherUnit_a{};
    Unk_7102431fa8 _208{mActor};
};
KSYS_CHECK_SIZE_NX150(WizzrobeRoot, 0x2e0);

}  // namespace uking::ai
