#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormNormalBase : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(SandwormNormalBase, EnemyNormal)
public:
    explicit SandwormNormalBase(const InitArg& arg);
    ~SandwormNormalBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x3d0
    const bool* mSealedSight_s{};
    // static_param at offset 0x3d8
    const bool* mSealedHearing_s{};
    // static_param at offset 0x3e0
    const bool* mSealedTerror_s{};
    // static_param at offset 0x3e8
    const bool* mSealedWorry_s{};
    ksys::act::ai::ActionBase* _3f0 = nullptr;  // child at the last sensor update
    u8 _3f8 = 0;  // bit i: awareness sensor i was active on enter
};

}  // namespace uking::ai
