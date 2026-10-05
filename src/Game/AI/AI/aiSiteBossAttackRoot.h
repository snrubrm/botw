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
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_7100571EB4(s32 kind, s32 slot);
    void sub_710057201C(s32 kind);
    void sub_71005721F4();
    void sub_7100572360();
    void sub_71005724C8();
    void sub_7100572634();

    // static_param at offset 0x38
    const int* mEquipWeapon_s{};
    ksys::act::BaseProcHandle _40[2];
    ksys::act::BaseProcLink _60[2];
};
KSYS_CHECK_SIZE_NX150(SiteBossAttackRoot, 0x80);

}  // namespace uking::ai
