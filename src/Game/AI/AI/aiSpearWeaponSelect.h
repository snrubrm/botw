#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SpearWeaponSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SpearWeaponSelect, ksys::act::ai::Ai)
public:
    explicit SpearWeaponSelect(const InitArg& arg);
    ~SpearWeaponSelect() override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
