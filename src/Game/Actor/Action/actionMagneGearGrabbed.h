#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class MagneGearGrabbed : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MagneGearGrabbed, ksys::act::ai::Action)
public:
    explicit MagneGearGrabbed(const InitArg& arg);
    ~MagneGearGrabbed() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

protected:
    void calc_() override;
    void sub_71001E4DDC();
    void sub_71001E501C();

    s32 _1c = 0;
    // static_param at offset 0x20
    const float* mConnectDistance_s{};
    ksys::Timer _28;
    bool _34 = false;
    sead::Matrix34f _38;
};
KSYS_CHECK_SIZE_NX150(MagneGearGrabbed, 0x68);

}  // namespace uking::action
