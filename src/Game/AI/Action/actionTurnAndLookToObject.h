#pragma once

#include "Game/AI/Action/actionLookAtObject.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TurnAndLookToObject : public LookAtObject {
    SEAD_RTTI_OVERRIDE(TurnAndLookToObject, LookAtObject)
public:
    explicit TurnAndLookToObject(const InitArg& arg);
    ~TurnAndLookToObject() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m40();

    // dynamic_param at offset 0xc8
    bool* mIsConfront_d{};
    bool _d0 = false;
    bool _d1 = false;
};

}  // namespace uking::action
