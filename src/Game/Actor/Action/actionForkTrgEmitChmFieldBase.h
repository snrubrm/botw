#pragma once

#include "Game/Actor/Action/actionForkEmitExpandField.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class ForkTrgEmitChmFieldBase : public ForkEmitExpandField {
    SEAD_RTTI_OVERRIDE(ForkTrgEmitChmFieldBase, ForkEmitExpandField)
public:
    explicit ForkTrgEmitChmFieldBase(const InitArg& arg);
    ~ForkTrgEmitChmFieldBase() override;

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

KSYS_CHECK_SIZE_NX150(ForkTrgEmitChmFieldBase, 0xa8);

}  // namespace uking::action
