#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DoubtItemSubTargetSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DoubtItemSubTargetSelect, ksys::act::ai::Ai)
public:
    explicit DoubtItemSubTargetSelect(const InitArg& arg);
    ~DoubtItemSubTargetSelect() override;
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
