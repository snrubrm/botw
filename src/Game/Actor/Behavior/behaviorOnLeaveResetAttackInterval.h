#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class OnLeaveResetAttackInterval : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(OnLeaveResetAttackInterval, ksys::act::ai::Behavior)
public:
    explicit OnLeaveResetAttackInterval(const InitArg& arg);
    ~OnLeaveResetAttackInterval() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(OnLeaveResetAttackInterval, 0x28);

}  // namespace uking::behavior
