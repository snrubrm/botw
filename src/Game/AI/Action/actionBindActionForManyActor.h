#pragma once

#include "Game/AI/Action/actionBindAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BindActionForManyActor : public BindAction {
    SEAD_RTTI_OVERRIDE(BindActionForManyActor, BindAction)
public:
    explicit BindActionForManyActor(const InitArg& arg);
    ~BindActionForManyActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void m32() override;
    ksys::act::Actor* m33() override;
    void calc_() override;

    // dynamic_param at offset 0xd8
    bool* mIsKeepParentActor_d{};
    // dynamic_param at offset 0xe0
    ksys::act::BaseProcLink* mParentActor_d{};
    ksys::act::BaseProcLink _e8;
    bool _f8 = false;
};

}  // namespace uking::action
