#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class LargeDamage : public ActionEx {
    SEAD_RTTI_OVERRIDE(LargeDamage, ActionEx)
public:
    explicit LargeDamage(const InitArg& arg);
    ~LargeDamage() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mActionTime_s{};
    ksys::Timer _28;
    ksys::VFRValue _34;
    sead::Vector3f _40;
    s32 _4c = 0;
    bool _50 = false;
};

KSYS_CHECK_SIZE_NX150(LargeDamage, 0x58);

}  // namespace uking::action
