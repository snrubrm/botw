#pragma once

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
    float _48 = 0.0f;
    float _4c = 0.0f;
    int _50 = 0;
    u8 _54[0x60 - 0x54];
    float _60 = 0.0f;
    int _64 = 0;
};

}  // namespace uking::action
