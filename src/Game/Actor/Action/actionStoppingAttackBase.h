#pragma once

#include "Game/Actor/Action/actionStopBase.h"
#include "Game/Actor/Action/actionUnk_71023c8418.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StoppingAttackBase : public StopBase {
    SEAD_RTTI_OVERRIDE(StoppingAttackBase, StopBase)
public:
    explicit StoppingAttackBase(const InitArg& arg);
    ~StoppingAttackBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual Unk_71023c8418* m32() { return nullptr; }
};

}  // namespace uking::action
