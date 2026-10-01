#pragma once

#include "Game/AI/AI/aiTargetAttackAttitudeTgtSelectBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetAttackAttitudeTgtSelect : public TargetAttackAttitudeTgtSelectBase {
    SEAD_RTTI_OVERRIDE(TargetAttackAttitudeTgtSelect, TargetAttackAttitudeTgtSelectBase)
public:
    explicit TargetAttackAttitudeTgtSelect(const InitArg& arg);
    ~TargetAttackAttitudeTgtSelect() override;

    void calc_() override;
    void loadParams_() override;
    void m34(ksys::act::ai::InlineParamPack* params) override;
    void m35(ksys::act::ai::InlineParamPack* params) override;

protected:
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
