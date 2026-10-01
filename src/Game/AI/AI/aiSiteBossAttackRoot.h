#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class SiteBossAttackRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossAttackRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossAttackRoot(const InitArg& arg);
    ~SiteBossAttackRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mEquipWeapon_s{};
    ksys::act::BaseProcHandle _40;
    ksys::act::BaseProcHandle _50;
    ksys::act::BaseProcLink _60;
    ksys::act::BaseProcLink _70;
};
KSYS_CHECK_SIZE_NX150(SiteBossAttackRoot, 0x80);

}  // namespace uking::ai
