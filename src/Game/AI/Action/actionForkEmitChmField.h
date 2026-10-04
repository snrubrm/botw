#pragma once

#include "Game/AI/Action/actionForkEmitExpandField.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class ForkEmitChmField : public ForkEmitExpandField {
    SEAD_RTTI_OVERRIDE(ForkEmitChmField, ForkEmitExpandField)
public:
    explicit ForkEmitChmField(const InitArg& arg);
    ~ForkEmitChmField() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual bool m33();
    virtual bool m34(sead::Matrix34f* mtx) = 0;

    // static_param at offset 0x90
    const int* mEmitIntervalTime_s{};
    bool _98 = false;
    ksys::Timer _9c;
};

KSYS_CHECK_SIZE_NX150(ForkEmitChmField, 0xa8);

}  // namespace uking::action
