#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CustomDuckingEndAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CustomDuckingEndAction, ksys::act::ai::Action)
public:
    explicit CustomDuckingEndAction(const InitArg& arg);
    ~CustomDuckingEndAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    bool oneShot_() override;
};

}  // namespace uking::action
