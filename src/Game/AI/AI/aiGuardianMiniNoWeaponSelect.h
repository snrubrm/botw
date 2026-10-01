#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniNoWeaponSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMiniNoWeaponSelect, ksys::act::ai::Ai)
public:
    explicit GuardianMiniNoWeaponSelect(const InitArg& arg);
    ~GuardianMiniNoWeaponSelect() override;
    bool isChangeable() const override;
    bool isFinished() const override;
    bool isFailed() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsSelectFirstTime_s{};
};

}  // namespace uking::ai
