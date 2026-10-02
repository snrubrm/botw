#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GolemRepairParts : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(GolemRepairParts, ActionWithAS)
public:
    explicit GolemRepairParts(const InitArg& arg);
    ~GolemRepairParts() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    // static_param at offset 0x40
    sead::SafeString mTgtBodyName_s{};
    // static_param at offset 0x50
    sead::SafeString mChmObjectName_s{};
    Unk_71005e1be8 _60;
    Unk_71005e1be8 _a0;
    // aitree_variable at offset 0xe0
    void* mGolemChemicalController_a{};
    Unk_7102396ae0 _e8{mActor, 0x800001f};
    Unk_7102451ba0 _118;
};

}  // namespace uking::action
