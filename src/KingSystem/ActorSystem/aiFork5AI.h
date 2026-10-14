#pragma once

#include "KingSystem/ActorSystem/aiForkAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::act::ai {

class Fork5AI : public ForkAI {
    SEAD_RTTI_OVERRIDE(Fork5AI, ForkAI)
public:
    explicit Fork5AI(const InitArg& arg);
    ~Fork5AI() override;

protected:
};

}  // namespace ksys::act::ai
