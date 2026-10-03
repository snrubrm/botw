#pragma once

#include "Game/AI/AI/aiPreyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DuckRoot : public PreyRoot {
    SEAD_RTTI_OVERRIDE(DuckRoot, PreyRoot)
public:
    explicit DuckRoot(const InitArg& arg);
    ~DuckRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool m34() override;
    bool m35() override;
    bool m37() override;

protected:
    void calc_() override;
};

}  // namespace uking::ai
