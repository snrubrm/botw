#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SoundProxyRootAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SoundProxyRootAction, ksys::act::ai::Action)
public:
    explicit SoundProxyRootAction(const InitArg& arg);
    ~SoundProxyRootAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool _1c = false;
    void* _20{};
    void* _28{};
    int _30 = 0;
    void* _38{};
};

}  // namespace uking::action
