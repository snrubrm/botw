#pragma once

#include "Game/AI/AI/aiOctarockRootBase.h"
#include "Game/AI/aiActorLink.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102450d10.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OctarockRoot : public OctarockRootBase {
    SEAD_RTTI_OVERRIDE(OctarockRoot, OctarockRootBase)
public:
    explicit OctarockRoot(const InitArg& arg);
    ~OctarockRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    void m37() override;
    void m38() override;
    void m39() override;
    bool m41() override;
    virtual void m45();

protected:
    // static_param at offset 0x1d8
    const bool* mIsWigBreakable_s{};
    // static_param at offset 0x1e0
    sead::SafeString mItemName_s{};
    // static_param at offset 0x1f0
    sead::SafeString mConnectRigidBodyName_s{};
    // static_param at offset 0x200
    sead::SafeString mConnectTgtBodyName_s{};
    // static_param at offset 0x210
    sead::SafeString mShootActorName_s{};
    // static_param at offset 0x220 (ShootActorKey1 .. ShootActorKey3)
    sead::SafeString mShootActorKey_s[3]{};
    // static_param at offset 0x250
    sead::SafeString mExtraShootActorName_s{};
    // static_param at offset 0x260
    sead::SafeString mExtraShootActorKey_s{};
    // map_unit_param at offset 0x270
    sead::SafeString mCarryActorName_m{};
    // aitree_variable at offset 0x280
    void* mVacuumedExplodingBomb_a{};
    // aitree_variable at offset 0x288
    void* mOctarockFormChangeUnit_a{};
    ksys::act::BaseProcHandle _290[3];
    u32 _2c0 = 1;
    Unk_710240dd68 _2c8;
    bool _318 = false;
    sead::Vector3f _31c = {0, 0, 0};
    Unk_7102450d10 _328{mActor};
    Unk_7102370e70 _368;
};
KSYS_CHECK_SIZE_NX150(OctarockRoot, 0x380);

}  // namespace uking::ai
