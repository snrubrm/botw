#pragma once

#include "Game/AI/aiActorLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class VacuumedBombDamageSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(VacuumedBombDamageSelect, ksys::act::ai::Ai)
public:
    explicit VacuumedBombDamageSelect(const InitArg& arg);
    ~VacuumedBombDamageSelect() override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    Unk_7102370e70** mVacuumedExplodingBomb_a{};
};

}  // namespace uking::ai
