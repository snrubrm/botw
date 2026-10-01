#pragma once

#include "Game/AI/AI/aiSeqTimeredTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqDynamicTimeredTwoAction : public SeqTimeredTwoAction {
    SEAD_RTTI_OVERRIDE(SeqDynamicTimeredTwoAction, SeqTimeredTwoAction)
public:
    explicit SeqDynamicTimeredTwoAction(const InitArg& arg);
    ~SeqDynamicTimeredTwoAction() override;

    void loadParams_() override;

    int m34() override { return *mDynFirstActionTime_d; }
    int m35() override { return *mDynSecondActionTime_d; }
    int m36() override { return *mDynAllActionTime_d; }

protected:
    // dynamic_param at offset 0x70
    int* mDynFirstActionTime_d{};
    // dynamic_param at offset 0x78
    int* mDynSecondActionTime_d{};
    // dynamic_param at offset 0x80
    int* mDynAllActionTime_d{};
};

}  // namespace uking::ai
