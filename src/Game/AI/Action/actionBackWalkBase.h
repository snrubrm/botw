#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class BackWalkBase : public ActionEx {
    SEAD_RTTI_OVERRIDE(BackWalkBase, ActionEx)
public:
    explicit BackWalkBase(const InitArg& arg);
    // The original keeps this destructor out of line next to the subclasses' inlined copies, which a
    // defaulted destructor does not. Written like upstream's GameDataFlagSelector::~GameDataFlagSelector()
    // { ; } (commit 96101229).
    ~BackWalkBase() override { ; }

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSpeed_s{};
    // static_param at offset 0x28
    const float* mRotSpd_s{};
    // static_param at offset 0x30
    const float* mRotAddRatio_s{};
    // static_param at offset 0x38
    const int* mTime_s{};
    // static_param at offset 0x40
    const float* mFinishDist_s{};
    // static_param at offset 0x48
    const int* mWeaponIdx_s{};
    // static_param at offset 0x50
    const float* mDecelRatio_s{};
    // static_param at offset 0x58
    const bool* mIsCliffCheck_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    ksys::VFRValue _68;
    sead::Matrix33f _74;
    ksys::Timer _98{0, 0};
    ksys::Timer _a4{0, 0};
};

KSYS_CHECK_SIZE_NX150(BackWalkBase, 0xb0);

}  // namespace uking::action
