#pragma once

#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCTurnAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCTurnAction, ksys::act::ai::Action)
public:
    explicit NPCTurnAction(const InitArg& arg);
    ~NPCTurnAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTurnFrame_s{};
    // static_param at offset 0x28
    const bool* mIsIgnoreSameKey_s{};
    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _48;
    sead::Vector3f _54;
    f32 _60 = 0.0f;
    f32 _64 = 0.0f;
};

}  // namespace uking::action
