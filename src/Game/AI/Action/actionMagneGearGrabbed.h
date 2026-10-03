#pragma once

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

protected:
    void calc_() override;

    s32 _1c = 0;
    // static_param at offset 0x20
    const float* mConnectDistance_s{};
    ksys::Timer _28;
    bool _34 = false;
    u8 _38[0x30];
};
KSYS_CHECK_SIZE_NX150(MagneGearGrabbed, 0x68);

}  // namespace uking::action
