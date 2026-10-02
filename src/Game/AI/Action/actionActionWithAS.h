#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ActionWithAS : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(ActionWithAS, ActionWithPosAngReduce)
public:
    explicit ActionWithAS(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;
    // Inline: the original emits it in the first TU that needs it (Angry's) and inlines it into
    // overrides (OctarockReloadWigBase::isFinished).
    bool isFinished() const override { return mFlags.isOn(Flag::Finished) || isFinishedAS(0, 0); }
};

}  // namespace uking::action
