#pragma once

#include "Game/AI/Action/actionActorObserver.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaTagAction : public ksys::act::ai::Action, public ActorObserver {
    SEAD_RTTI_OVERRIDE(AreaTagAction, ksys::act::ai::Action)
public:
    explicit AreaTagAction(const InitArg& arg);
    ~AreaTagAction() override = default;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;
};

}  // namespace uking::action
