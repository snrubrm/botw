#pragma once

#include "Game/AI/AI/aiWeaponRootAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChemicalWeaponRoot : public WeaponRootAI {
    SEAD_RTTI_OVERRIDE(ChemicalWeaponRoot, WeaponRootAI)
public:
    explicit ChemicalWeaponRoot(const InitArg& arg);
    ~ChemicalWeaponRoot() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;

    // 0x7100348fc8 / 0x71003491c0 (not decompiled yet; called by SiteBossSwordWeapon)
    bool m41() override;
    bool m42() override;
    void m43() override;
    void m44() override;

protected:
    bool _e8 = false;
    s32 _ec = -1;
};
KSYS_CHECK_SIZE_NX150(ChemicalWeaponRoot, 0xf0);

}  // namespace uking::ai
