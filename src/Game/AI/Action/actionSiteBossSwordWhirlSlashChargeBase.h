#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class SiteBossSwordWhirlSlashChargeBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossSwordWhirlSlashChargeBase, ksys::act::ai::Action)
public:
    explicit SiteBossSwordWhirlSlashChargeBase(const InitArg& arg);
    ~SiteBossSwordWhirlSlashChargeBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();

    // static_param at offset 0x20
    const float* mChargeTime_s{};
    // static_param at offset 0x28
    const float* mInitSpeed_s{};
    // dynamic_param at offset 0x30
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _38;
    ksys::VFRValue _44;
    sead::Matrix33f _50;
};

}  // namespace uking::action
