#pragma once

#include "Game/AI/Action/actionFork.h"
#include "Game/AI/Action/actionUnk_71023c8600.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkOctarockEnterReloadWig : public Fork {
    SEAD_RTTI_OVERRIDE(ForkOctarockEnterReloadWig, Fork)
public:
    explicit ForkOctarockEnterReloadWig(const InitArg& arg);
    ~ForkOctarockEnterReloadWig() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x30
    void* mOctarockFormChangeUnit_a{};
    bool _38 = false;
    Unk_71023c8600 _40{this};
};

}  // namespace uking::action
