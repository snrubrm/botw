#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCPurchaseMaterial : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCPurchaseMaterial, ksys::act::ai::Action)
public:
    explicit NPCPurchaseMaterial(const InitArg& arg);
    ~NPCPurchaseMaterial() override;

protected:
    bool oneShot_() override;
};

}  // namespace uking::action
