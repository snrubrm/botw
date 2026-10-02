#pragma once

#include "Game/AI/Action/actionPriestBossAimBeam.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PriestBossAimBeamWithAS : public PriestBossAimBeam {
    SEAD_RTTI_OVERRIDE(PriestBossAimBeamWithAS, PriestBossAimBeam)
public:
    explicit PriestBossAimBeamWithAS(const InitArg& arg);
    ~PriestBossAimBeamWithAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(const char* name) override;


    // static_param at offset 0x190
    sead::SafeString mASName_s{};
    bool _1a0 = false;
};

}  // namespace uking::action
