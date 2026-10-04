#pragma once

#include "Game/AI/Action/actionLookAtObject.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class CharacterController;
}

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
    virtual void m41(ksys::phys::CharacterController* controller);

    // dynamic_param at offset 0xc8
    bool* mIsConfront_d{};
    bool _d0 = false;
    bool _d1 = false;
};
KSYS_CHECK_SIZE_NX150(TurnAndLookToObject, 0xd8);

}  // namespace uking::action
