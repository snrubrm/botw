#pragma once

#include "Game/AI/aiUnk_7102450410.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemChemicalResetSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GolemChemicalResetSelect, ksys::act::ai::Ai)
public:
    explicit GolemChemicalResetSelect(const InitArg& arg);
    ~GolemChemicalResetSelect() override;
    void calc_() override;
    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    Unk_7102450410** mGolemChemicalController_a{};
};

}  // namespace uking::ai
