#pragma once

#include "Game/AI/Action/actionRegistedActorActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::act {
class BaseProcLink;
}

namespace uking::action {

class RegistedActorDeadCheckBase : public RegistedActorActionBase {
    SEAD_RTTI_OVERRIDE(RegistedActorDeadCheckBase, RegistedActorActionBase)
public:
    explicit RegistedActorDeadCheckBase(const InitArg& arg);
    ~RegistedActorDeadCheckBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    virtual bool m32(ksys::act::BaseProcLink* link);
};

}  // namespace uking::action
