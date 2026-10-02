#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LastAttackerSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LastAttackerSelect, ksys::act::ai::Ai)
public:
    explicit LastAttackerSelect(const InitArg& arg);
    ~LastAttackerSelect() override;

    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34();

protected:
};

}  // namespace uking::ai
