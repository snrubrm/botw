#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventCheckAndCreateEquip : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventCheckAndCreateEquip, ksys::act::ai::Action)
public:
    explicit EventCheckAndCreateEquip(const InitArg& arg);
    ~EventCheckAndCreateEquip() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // 0x7100116c38 (placeholder name): the equipment slot of a weapon profile (0 sword / large sword / spear,
    // 1 shield, 2 bow, 3 anything else).
    s32 sub_7100116C38(const sead::SafeString& profile);

    // dynamic_param at offset 0x20
    int* mSharpWeaponAddValue_d{};
    // dynamic_param at offset 0x28
    int* mSharpWeaponAddType_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mTargetActorName_d{};
};

}  // namespace uking::action
