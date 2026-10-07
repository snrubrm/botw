#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SeqTimeredTwoAction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqTimeredTwoAction, ksys::act::ai::Ai)
public:
    explicit SeqTimeredTwoAction(const InitArg& arg);
    ~SeqTimeredTwoAction() override = default;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual int m34() { return *mFirstActionTime_s; }
    virtual int m35() { return *mSecondActionTime_s; }
    virtual int m36() { return *mAllActionTime_s; }

protected:
    // static_param at offset 0x38
    const int* mFirstActionTime_s{};
    // static_param at offset 0x40
    const int* mSecondActionTime_s{};
    // static_param at offset 0x48
    const int* mAllActionTime_s{};
    ksys::Timer _50;
    ksys::Timer _5c;
    bool _68 = true;
};

}  // namespace uking::ai
