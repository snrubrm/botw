#pragma once

#include "Game/AI/Action/actionActorObserver.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaActionBase : public ksys::act::ai::Action, public ActorObserver {
    SEAD_RTTI_OVERRIDE(AreaActionBase, ksys::act::ai::Action)
public:
    explicit AreaActionBase(const InitArg& arg);
    ~AreaActionBase() override = default;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;
};

}  // namespace uking::action
