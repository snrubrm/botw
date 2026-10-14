#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DisappearNumTargets : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DisappearNumTargets, ksys::act::ai::Action)
public:
    explicit DisappearNumTargets(const InitArg& arg);
    ~DisappearNumTargets() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    bool oneShot_() override;

};

}  // namespace uking::action
