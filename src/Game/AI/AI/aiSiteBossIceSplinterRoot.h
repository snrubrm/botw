#pragma once

#include <prim/seadDelegate.h>
#include "Game/AI/AI/aiSiteBossChemicalProjectile.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossIceSplinterRoot : public SiteBossChemicalProjectile {
    SEAD_RTTI_OVERRIDE(SiteBossIceSplinterRoot, SiteBossChemicalProjectile)
public:
    explicit SiteBossIceSplinterRoot(const InitArg& arg);
    ~SiteBossIceSplinterRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void loadParams_() override;

    const sead::SafeString& m34() override;
    sead::Vector3f m35() override;
    bool m39() override;
    bool m40() override;
    u32 m50() override;
    u32 m51() override;
    bool m54() override;
    bool m56() override;
    void m43(bool a) override;
    void m44() override;
    f32 m57() override;

protected:
    // static_param at offset 0x180
    const int* mReflectAtkPower_s{};
    // static_param at offset 0x188
    const float* mChaseAngleMin_s{};
    // static_param at offset 0x190
    const float* mRotateSpeed_s{};
    // static_param at offset 0x198
    sead::SafeString mBindNodeName0_s{};
    // static_param at offset 0x1a8
    sead::SafeString mBindNodeName1_s{};
    // static_param at offset 0x1b8
    sead::SafeString mChaseParentNode_s{};
    // static_param at offset 0x1c8
    const sead::Vector3f* mBindOffset0_s{};
    // static_param at offset 0x1d0
    const sead::Vector3f* mBindOffset1_s{};
    // static_param at offset 0x1d8
    const sead::Vector3f* mBindOffset2_s{};
    // static_param at offset 0x1e0
    const sead::Vector3f* mBindOffset3_s{};
    // static_param at offset 0x1e8
    const sead::Vector3f* mBindOffset4_s{};
    // static_param at offset 0x1f0
    const sead::Vector3f* mBindOffset5_s{};
    // static_param at offset 0x1f8
    const sead::Vector3f* mBindOffset6_s{};
    // static_param at offset 0x200
    const sead::Vector3f* mBindOffset7_s{};
    // static_param at offset 0x208
    const sead::Vector3f* mBindOffset8_s{};
    // static_param at offset 0x210
    const sead::Vector3f* mRotateSpeedAtHit_s{};
    // static_param at offset 0x218
    const sead::Vector3f* mRotateSpeedAtFall_s{};
    // map_unit_param at offset 0x220
    const int* mCount_m{};
    bool _228 = false;
    bool _229 = false;
    bool _22a = false;
    bool _22b = false;
    bool _22c = false;
    f32 _230 = 0;
    f32 _234 = 0;
    f32 _238 = 0;
    f32 _23c = 0;
    f32 _240 = 0;
    u32 _244 = 0;
    sead::Vector3f _248;
    sead::Vector3f _254;
    sead::Vector3f _260;
    u32 _26c;
    // Handler 0x7100577b18 (1312 bytes, not decompiled yet): the argument has a Vector3f at +0 and a
    // pointer at +0x18 to an object holding a BaseProcLink at +0xd8 (the same type as TrolleyRoot's /
    // StoneBall_BRoot's delegate argument).
    void sub_7100577B18(ksys::act::Unk_71006dc134* arg);

    sead::Delegate1<SiteBossIceSplinterRoot, ksys::act::Unk_71006dc134*> _270{
        this, &SiteBossIceSplinterRoot::sub_7100577B18};
};
KSYS_CHECK_SIZE_NX150(SiteBossIceSplinterRoot, 0x290);

}  // namespace uking::ai
