#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class OnLeaveResetAttackInterval : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(OnLeaveResetAttackInterval, ksys::act::ai::Behavior)
public:
    explicit OnLeaveResetAttackInterval(const InitArg& arg);
    ~OnLeaveResetAttackInterval() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(OnLeaveResetAttackInterval, 0x28);

}  // namespace uking::behavior
