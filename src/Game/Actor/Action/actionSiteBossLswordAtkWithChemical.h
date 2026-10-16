#pragma once

#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include "Game/Actor/Action/actionSiteBossLswordAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::action {

class SiteBossLswordAtkWithChemical : public SiteBossLswordAttack {
    SEAD_RTTI_OVERRIDE(SiteBossLswordAtkWithChemical, SiteBossLswordAttack)
public:
    explicit SiteBossLswordAtkWithChemical(const InitArg& arg);
    ~SiteBossLswordAtkWithChemical() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    virtual void m37(sead::Vector3f* pos);
    virtual f32 m38();
    virtual int m39();

    // static_param at offset 0xe8
    const int* mEmitNum_s{};
    // static_param at offset 0xf0
    const int* mEmitInterval_s{};
    // static_param at offset 0xf8
    const int* mEmitAttackDamage_s{};
    // static_param at offset 0x100
    const int* mEmitActorMinDamage_s{};
    // static_param at offset 0x108
    const float* mEmitOffsetFromParent_s{};
    // static_param at offset 0x110
    const float* mEmitIntervalDist_s{};
    // static_param at offset 0x118
    const float* mEmitIntervalRotate_s{};
    // static_param at offset 0x120
    const float* mEmitScale_s{};
    // static_param at offset 0x128
    const float* mEmitMaxScale_s{};
    // static_param at offset 0x130
    const float* mScaleTime_s{};
    // static_param at offset 0x138
    const float* mEmitStartFrame_s{};
    // static_param at offset 0x140
    const float* mEmitAngleFromParent_s{};
    // static_param at offset 0x148
    const float* mEmitActorSpeedRotate_s{};
    // static_param at offset 0x150
    sead::SafeString mEmitActorName_s{};
    // static_param at offset 0x160
    sead::SafeString mEmitPartsName_s{};
    // static_param at offset 0x170
    sead::SafeString mCallSEKeyAtAtOn_s{};
    // static_param at offset 0x180
    const sead::Vector3f* mEmitActorSpeed_s{};
    // Placeholder names. 0x710025b4b0: ray-casts the ground below emit position `index` into _1b8.
    bool sub_710025B4B0(int index);
    void sub_710025B7CC();
    // 0x710025b95c: wakes the first sleeping emit parts actor at ground position `index`.
    void sub_710025B95C(u32 index);

    bool _188 = false;
    bool _189 = false;
    bool _18a = false;
    ksys::Timer _18c;
    s32 _198 = 0;
    // The actor's EntitySensor "BgSensor" body (init_).
    ksys::phys::RigidBody* _1a0 = nullptr;
    sead::Buffer<bool> _1a8;
    sead::Buffer<sead::Vector3f> _1b8;
    Unk_71012419b4 _1c8;
};
KSYS_CHECK_SIZE_NX150(SiteBossLswordAtkWithChemical, 0x1e8);

}  // namespace uking::action
