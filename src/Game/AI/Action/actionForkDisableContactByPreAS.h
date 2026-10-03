#pragma once

#include "Game/AI/Action/actionForkDisableContact.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class ForkDisableContactByPreAS : public ForkDisableContact {
    SEAD_RTTI_OVERRIDE(ForkDisableContactByPreAS, ForkDisableContact)
public:
    explicit ForkDisableContactByPreAS(const InitArg& arg);
    ~ForkDisableContactByPreAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m33() override;
    bool m32() override;

    // static_param at offset 0xd8
    const int* mDisableTime_s{};
    // static_params at offset 0xe0 (PreASName0-4)
    sead::SafeString mPreASName_s[5];
    ksys::Timer mTimer;
    bool mTimerActive = false;
};

}  // namespace uking::action
