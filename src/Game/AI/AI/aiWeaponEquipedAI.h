#pragma once

#include <xlink2/xlink2HandleELink.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WeaponEquipedAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WeaponEquipedAI, ksys::act::ai::Ai)
public:
    explicit WeaponEquipedAI(const InitArg& arg);
    ~WeaponEquipedAI() override;
    bool isChangeable() const override { return true; }

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

    void sub_7100E1DC50();

protected:
    bool _38 = false;
    bool _39 = false;
    u32 _3c = -1;
    xlink2::HandleELink _40;
    xlink2::HandleELink _50;
};
KSYS_CHECK_SIZE_NX150(WeaponEquipedAI, 0x60);

}  // namespace uking::ai
