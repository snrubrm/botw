#pragma once

#include "Game/AI/AI/aiChemicalWeaponRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossSwordWeapon : public ChemicalWeaponRoot {
    SEAD_RTTI_OVERRIDE(SiteBossSwordWeapon, ChemicalWeaponRoot)
public:
    explicit SiteBossSwordWeapon(const InitArg& arg);
    ~SiteBossSwordWeapon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    bool m41() override;
    bool m42() override;

protected:
    bool _f0 = false;
};
KSYS_CHECK_SIZE_NX150(SiteBossSwordWeapon, 0xf8);

}  // namespace uking::ai
