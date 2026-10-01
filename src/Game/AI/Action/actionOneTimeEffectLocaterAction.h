#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OneTimeEffectLocaterAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(OneTimeEffectLocaterAction, ksys::act::ai::Action)
public:
    explicit OneTimeEffectLocaterAction(const InitArg& arg);
    ~OneTimeEffectLocaterAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool _1c = false;
    void* _20{};
    int _28 = 0;
    void* _30{};
    int _38 = 0;
};

}  // namespace uking::action
