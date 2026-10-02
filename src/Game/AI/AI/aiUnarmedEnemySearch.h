#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class UnarmedEnemySearch : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(UnarmedEnemySearch, ksys::act::ai::Ai)
public:
    explicit UnarmedEnemySearch(const InitArg& arg);
    ~UnarmedEnemySearch() override;

    bool isChangeable() const override { return getCurrentChild()->isChangeable(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mReachTargetArea_s{};
    // static_param at offset 0x48
    const float* mTurnStartAng_s{};
    void* _50 = nullptr;
    sead::Vector3f _58{0, 0, 0};
};
KSYS_CHECK_SIZE_NX150(UnarmedEnemySearch, 0x68);

}  // namespace uking::ai
