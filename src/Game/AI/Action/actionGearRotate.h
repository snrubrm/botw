#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace xlink2 {
class Handle;
}

namespace uking::action {

class GearRotate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GearRotate, ksys::act::ai::Action)
public:
    explicit GearRotate(const InitArg& arg);
    ~GearRotate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool handleMessage_(const ksys::Message& message) override;

    // static_param at offset 0x20
    const float* mStopCheckSpdRate_s{};
    // static_param at offset 0x28
    const float* mCheckSpdIdlingRate_s{};
    // static_param at offset 0x30
    const bool* mIsReverse_s{};
    // static_param at offset 0x38
    const bool* mIsTwoWayGear_s{};
    // map_unit_param at offset 0x40
    const int* mDgnRotDir_m{};
    // map_unit_param at offset 0x48
    const float* mRotateSpeed_m{};
    sead::Vector3f _50 = sead::Vector3f::ex;
    f32 _5c = 0;
    ksys::VFRValue _60;
    f32 _6c = 0;
    xlink2::Handle* _70 = nullptr;
};

KSYS_CHECK_SIZE_NX150(GearRotate, 0x78);

}  // namespace uking::action
