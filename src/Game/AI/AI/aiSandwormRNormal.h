#pragma once

#include "Game/AI/AI/aiSandwormNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormRNormal : public SandwormNormal {
    SEAD_RTTI_OVERRIDE(SandwormRNormal, SandwormNormal)
public:
    explicit SandwormRNormal(const InitArg& arg);
    ~SandwormRNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m44(const sead::Vector3f& pos) override;

protected:
};

}  // namespace uking::ai
