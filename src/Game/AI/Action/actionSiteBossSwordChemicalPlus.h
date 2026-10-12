#pragma once

#include "Game/AI/Action/actionStopBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSwordChemicalPlus : public StopBase {
    SEAD_RTTI_OVERRIDE(SiteBossSwordChemicalPlus, StopBase)
public:
    explicit SiteBossSwordChemicalPlus(const InitArg& arg);
    ~SiteBossSwordChemicalPlus() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool _30 = false;
    u8 _31 = 0;
    void sub_7100268FCC();
    bool _32 = false;
};

}  // namespace uking::action
