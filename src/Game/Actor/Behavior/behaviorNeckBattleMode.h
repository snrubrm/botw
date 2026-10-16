#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class NeckBattleMode : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(NeckBattleMode, ksys::act::ai::Behavior)
public:
    explicit NeckBattleMode(const InitArg& arg);
    ~NeckBattleMode() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(NeckBattleMode, 0x28);

}  // namespace uking::behavior
