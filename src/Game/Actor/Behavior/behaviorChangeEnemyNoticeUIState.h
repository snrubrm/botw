#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ChangeEnemyNoticeUIState : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ChangeEnemyNoticeUIState, ksys::act::ai::Behavior)
public:
    explicit ChangeEnemyNoticeUIState(const InitArg& arg);
    ~ChangeEnemyNoticeUIState() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const int* mKey_s{};
};
KSYS_CHECK_SIZE_NX150(ChangeEnemyNoticeUIState, 0x30);

}  // namespace uking::behavior
