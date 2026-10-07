#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsWaterWeakPointRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainsWaterWeakPointRoot, ksys::act::ai::Ai)
public:
    explicit RemainsWaterWeakPointRoot(const InitArg& arg);
    ~RemainsWaterWeakPointRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    bool isAttackedByElectricArrow();
    void sub_710054C520();
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
