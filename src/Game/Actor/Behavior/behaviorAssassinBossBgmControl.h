#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class AssassinBossBgmControl : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AssassinBossBgmControl, ksys::act::ai::Behavior)
public:
    explicit AssassinBossBgmControl(const InitArg& arg);
    ~AssassinBossBgmControl() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(AssassinBossBgmControl, 0x28);

}  // namespace uking::behavior
