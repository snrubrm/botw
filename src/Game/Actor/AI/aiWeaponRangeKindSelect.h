#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WeaponRangeKindSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WeaponRangeKindSelect, ksys::act::ai::Ai)
public:
    explicit WeaponRangeKindSelect(const InitArg& arg);

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }
    bool isChangeable() const override { return getCurrentChild()->isChangeable(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    void* _40{};
};
KSYS_CHECK_SIZE_NX150(WeaponRangeKindSelect, 0x48);

}  // namespace uking::ai
