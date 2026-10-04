#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GolemThrowPartsToTargetBase : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(GolemThrowPartsToTargetBase, ActionWithAS)
public:
    explicit GolemThrowPartsToTargetBase(const InitArg& arg);
    ~GolemThrowPartsToTargetBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710018d8dc (declared only): out of line in the original.
    void sub_710018D8DC();
    void calc_() override;

    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    // static_param at offset 0x40
    sead::SafeString mTgtBodyName_s{};
    // static_param at offset 0x50
    sead::SafeString mChmObjectName_s{};
    Unk_71005e1be8 _60;
    Unk_71005e1be8 _a0;
    bool _e0;
    bool _e1;
    // aitree_variable at offset 0xe8
    void* mGolemChemicalController_a{};
    Unk_7102451ba0 _f0;
};

}  // namespace uking::action
