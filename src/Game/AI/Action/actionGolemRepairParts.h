#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAction.h"

class Unk_71025afb58;

namespace uking::act { class Enemy; }

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
    // 0x710018d09c (declared only): out of line in the original.
    void sub_710018D09C();
    // Same-class caller and native Enemy/part-record arguments; the receiver is unused.
    void sub_710018D2EC(act::Enemy* enemy, const Unk_71005e1be8& part);
    // 0x710018ced4 (declared only): out of line in the original.
    void sub_710018CED4();
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
    Unk_71025afb58** mGolemChemicalController_a{};
    Unk_7102396ae0 _e8{mActor, 0x800001f};
    Unk_7102451ba0 _118;
};

}  // namespace uking::action
