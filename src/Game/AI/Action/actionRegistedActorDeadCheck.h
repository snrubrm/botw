#pragma once

#include "Game/AI/Action/actionRegistedActorAllDeadCheckBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RegistedActorDeadCheck : public RegistedActorAllDeadCheckBase {
    SEAD_RTTI_OVERRIDE(RegistedActorDeadCheck, RegistedActorAllDeadCheckBase)
public:
    explicit RegistedActorDeadCheck(const InitArg& arg);
    ~RegistedActorDeadCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    bool m32(ksys::act::BaseProcLink* link) override;
};

}  // namespace uking::action
