#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class BattleTensionUp : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(BattleTensionUp, ksys::act::ai::Behavior)
public:
    explicit BattleTensionUp(const InitArg& arg);
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(BattleTensionUp, 0x28);

}  // namespace uking::behavior
