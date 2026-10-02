#pragma once

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

protected:
    bool _38 = false;
    bool _39 = false;
    u32 _3c = -1;
    void* _40 = nullptr;
    u32 _48 = 0;
    void* _50 = nullptr;
    u32 _58 = 0;
};
KSYS_CHECK_SIZE_NX150(WeaponEquipedAI, 0x60);

}  // namespace uking::ai
