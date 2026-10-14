#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetDirLRSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetDirLRSelect, ksys::act::ai::Ai)
public:
    explicit TargetDirLRSelect(const InitArg& arg);
    ~TargetDirLRSelect() override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }
    bool isChangeable() const override { return getCurrentChild()->isChangeable(); }

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;

    virtual u8 m34();

protected:
};

}  // namespace uking::ai
