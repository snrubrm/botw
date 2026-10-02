#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class WaitBase : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(WaitBase, ActionWithPosAngReduce)
public:
    explicit WaitBase(const InitArg& arg);
    // The original keeps this destructor out of line next to the subclasses' inlined copies, which a
    // defaulted destructor does not. Written like upstream's GameDataFlagSelector::~GameDataFlagSelector()
    // { ; } (commit 96101229).
    ~WaitBase() override { ; }

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mTime_s{};
    // static_param at offset 0x38
    const int* mTimeRand_s{};

    ksys::Timer mTimer;
};

}  // namespace uking::action
