#pragma once

#include "Game/AI/Action/actionTurnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OnCliffTurn : public TurnBase {
    SEAD_RTTI_OVERRIDE(OnCliffTurn, TurnBase)
public:
    explicit OnCliffTurn(const InitArg& arg);
    ~OnCliffTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(f32 x) override;
    void m33(sead::Vector3f* up) override;
    void m34(sead::Vector3f* front) override;
    void m35(sead::Vector3f* dir) override;

    // static_param at offset 0x90
    sead::SafeString mASName_s{};
    int _a0 = 0;
};

}  // namespace uking::action
