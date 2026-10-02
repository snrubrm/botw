#pragma once

#include <math/seadQuat.h>
#include "Game/AI/AI/aiSiteBossRoot.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossSpearRoot : public SiteBossRoot {
    SEAD_RTTI_OVERRIDE(SiteBossSpearRoot, SiteBossRoot)
public:
    explicit SiteBossSpearRoot(const InitArg& arg);
    ~SiteBossSpearRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool m35(act::SiteBoss* boss) override;

protected:
    // static_param at offset 0xf8
    const int* mThrowSpearAttackPower_s{};
    // static_param at offset 0x100
    const int* mThrowSpearMinDmage_s{};
    // static_param at offset 0x108
    const int* mIceSplinterAttackPower_s{};
    // static_param at offset 0x110
    const int* mIceSplinterMinDamage_s{};
    bool _118 = false;
    ksys::act::BoneHandle _120;
    ksys::act::BoneHandle _1c8;
    ksys::act::BoneHandle _270;
    ksys::act::BoneHandle _318;
    sead::Quatf _3c0;
    sead::Quatf _3d0;
    sead::Quatf _3e0;
};
KSYS_CHECK_SIZE_NX150(SiteBossSpearRoot, 0x3f0);

}  // namespace uking::ai
