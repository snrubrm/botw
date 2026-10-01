#pragma once

#include "Game/AI/AI/aiDieSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DieSelectBombPlus : public DieSelect {
    SEAD_RTTI_OVERRIDE(DieSelectBombPlus, DieSelect)
public:
    explicit DieSelectBombPlus(const InitArg& arg);
    ~DieSelectBombPlus() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void m34(s32 a2, s32 a3, bool a4, bool a5) override;

protected:
};

}  // namespace uking::ai
