#pragma once

#include <math/seadQuat.h>
#include "Game/Actor/AI/aiSiteBossRoot.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::phys {
class RigidBody;
}

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
    // 0x7100591264 (placeholder name): whether `body` belongs to an actor with tag 0x0f42c303 (calc_'s helper
    // 0x710058e11c does not pass `this`, which this function does not use)
    bool sub_7100591264(ksys::phys::RigidBody* body);

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
