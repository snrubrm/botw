#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class BattleTensionUp : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(BattleTensionUp, ksys::act::ai::Behavior)
public:
    explicit BattleTensionUp(const InitArg& arg);
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(BattleTensionUp, 0x28);

}  // namespace uking::behavior
