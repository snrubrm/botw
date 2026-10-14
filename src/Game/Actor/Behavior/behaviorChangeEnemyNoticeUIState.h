#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ChangeEnemyNoticeUIState : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ChangeEnemyNoticeUIState, ksys::act::ai::Behavior)
public:
    explicit ChangeEnemyNoticeUIState(const InitArg& arg);
    ~ChangeEnemyNoticeUIState() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mKey_s{};
};
KSYS_CHECK_SIZE_NX150(ChangeEnemyNoticeUIState, 0x30);

}  // namespace uking::behavior
