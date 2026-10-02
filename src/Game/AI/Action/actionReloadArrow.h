#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class ReloadArrow : public ActionEx {
    SEAD_RTTI_OVERRIDE(ReloadArrow, ActionEx)
public:
    explicit ReloadArrow(const InitArg& arg);
    ~ReloadArrow() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpeed_s{};
    // static_param at offset 0x28
    const float* mStopSpeedRatio_s{};
    // static_param at offset 0x30
    const int* mWeaponIdx_s{};
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    ksys::VFRValue _40{0.0f};
    ksys::VFRVec3f _4c;
    f32 _70 = 0;
};
KSYS_CHECK_SIZE_NX150(ReloadArrow, 0x78);

}  // namespace uking::action
