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

protected:
    bool _e8 = false;
    s32 _ec = -1;
};
KSYS_CHECK_SIZE_NX150(ChemicalWeaponRoot, 0xf0);

}  // namespace uking::ai
