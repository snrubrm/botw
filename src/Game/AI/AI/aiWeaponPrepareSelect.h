#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WeaponPrepareSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WeaponPrepareSelect, ksys::act::ai::Ai)
public:
    explicit WeaponPrepareSelect(const InitArg& arg);
    ~WeaponPrepareSelect() override;

    bool isChangeable() const override { return getCurrentChild()->isChangeable(); }

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
};

}  // namespace uking::ai
