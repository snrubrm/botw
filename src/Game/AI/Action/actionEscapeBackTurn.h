#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class EscapeBackTurn : public ActionEx {
    SEAD_RTTI_OVERRIDE(EscapeBackTurn, ActionEx)
public:
    explicit EscapeBackTurn(const InitArg& arg);
    ~EscapeBackTurn() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void sub_7100113950();
    void sub_7100113D4C(const sead::Vector3f& up);
    void sub_7100113EF8(s32 duration);
    void calc_() override;

    ksys::VFRValue _1c;
    sead::Matrix33f _28;
    ksys::Timer _4c{0.0f, 0.0f};
    sead::Vector3f _58{0.0f, 0.0f, 0.0f};
    u32 _64;
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTurnDir_d{};
    // static_param at offset 0x78
    const f32* mMoveSpeed_s{};
    s32 _80 = -1;
    u32 _84;
};
KSYS_CHECK_SIZE_NX150(EscapeBackTurn, 0x88);

}  // namespace uking::action
