#pragma once

#include "Game/Actor/AI/aiPriestBoss.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossActorRoot : public PriestBoss {
    SEAD_RTTI_OVERRIDE(PriestBossActorRoot, PriestBoss)
public:
    explicit PriestBossActorRoot(const InitArg& arg);
    ~PriestBossActorRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    virtual void m35() {}

protected:
};

}  // namespace uking::ai
