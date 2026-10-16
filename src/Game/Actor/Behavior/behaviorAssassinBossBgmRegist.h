#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class AssassinBossBgmRegist : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AssassinBossBgmRegist, ksys::act::ai::Behavior)
public:
    explicit AssassinBossBgmRegist(const InitArg& arg);
    ~AssassinBossBgmRegist() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(AssassinBossBgmRegist, 0x28);

}  // namespace uking::behavior
