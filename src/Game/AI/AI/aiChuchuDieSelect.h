#pragma once

#include "Game/AI/AI/aiDieSelectChemicalPlus.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChuchuDieSelect : public DieSelectChemicalPlus {
    SEAD_RTTI_OVERRIDE(ChuchuDieSelect, DieSelectChemicalPlus)
public:
    explicit ChuchuDieSelect(const InitArg& arg);
    ~ChuchuDieSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void m34(s32 a2, s32 a3, bool a4, bool a5) override;

protected:
};

}  // namespace uking::ai
