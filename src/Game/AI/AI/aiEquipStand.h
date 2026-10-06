#pragma once

#include "Game/AI/aiActorLink.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EquipStand : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EquipStand, ksys::act::ai::Ai)
public:
    explicit EquipStand(const InitArg& arg);
    ~EquipStand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    Unk_71023e0020 _38{0x1800029};
    // static_param at offset 0x78
    sead::SafeString mDisplayAttKey_s{};
    // static_param at offset 0x88
    sead::SafeString mTakeOutAttKey_s{};
    // map_unit_param at offset 0x98
    const int* mEquipStandSlot_m{};
    // aitree_variable at offset 0xa0
    void* mEquipDisplayChild_a{};
    bool _a8 = false;
    ActorLink _b0;
};
KSYS_CHECK_SIZE_NX150(EquipStand, 0xc8);

}  // namespace uking::ai
