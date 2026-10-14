#pragma once

#include "Game/Actor/aiUnk_71000b0800.h"
#include "Game/Actor/aiUnk_71025b2aa8.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkBasicMessageDialogCtrl : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkBasicMessageDialogCtrl, ksys::act::ai::Action)
public:
    explicit ForkBasicMessageDialogCtrl(const InitArg& arg);
    ~ForkBasicMessageDialogCtrl() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x20
    void* mSimpleDialogUnit_a{};
    Unk_71000b0800<Unk_71025b2aa8> _28;
};

}  // namespace uking::action
