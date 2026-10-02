#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class TurnBase : public ActionEx {
    SEAD_RTTI_OVERRIDE(TurnBase, ActionEx)
public:
    explicit TurnBase(const InitArg& arg);
    // The original keeps this destructor out of line next to the subclasses' inlined copies, which a
    // defaulted destructor does not. Written like upstream's GameDataFlagSelector::~GameDataFlagSelector()
    // { ; } (commit 96101229).
    ~TurnBase() override { ; }

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32(f32 x);
    virtual void m33(sead::Vector3f* up);
    virtual void m34(sead::Vector3f* front);
    virtual void m35(sead::Vector3f* dir);
    virtual bool m36() const;

    // static_param at offset 0x20
    const float* mRotSpd_s{};
    // static_param at offset 0x28
    const float* mFinRotate_s{};
    // static_param at offset 0x30
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x38
    const float* mBaseRotRatio_s{};
    // static_param at offset 0x40
    const bool* mIsFollowGround_s{};
    // static_param at offset 0x48
    const float* mRotMinSpeedRatio_s{};
    // static_param at offset 0x50
    const bool* mIsChangeable_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    ksys::VFRValue _60;
    sead::Matrix33f _6c;
};

KSYS_CHECK_SIZE_NX150(TurnBase, 0x90);

}  // namespace uking::action
