#pragma once

#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OnEnterSwapActorBase : public Fork {
    SEAD_RTTI_OVERRIDE(OnEnterSwapActorBase, Fork)
public:
    explicit OnEnterSwapActorBase(const InitArg& arg);
    ~OnEnterSwapActorBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual bool m32(sead::BufferedSafeString* name);

    // static_param at offset 0x30
    const bool* mOnGroundPos_s{};
    ksys::act::BaseProcLink _38;
    sead::Matrix34f _48;
};

KSYS_CHECK_SIZE_NX150(OnEnterSwapActorBase, 0x78);

}  // namespace uking::action
