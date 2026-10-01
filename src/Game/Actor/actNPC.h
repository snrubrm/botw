#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/actNPCBase.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Physics/physMaterialMask.h"

namespace uking::act {

// Name from the CSV (NPC::*). vtable 0x7102358310 (150 slots: NPCBase's 148 + m148, m149),
// RTTI static 0x71025aebc0. Factory 0x710001c748 (CSV NPC::construct): new(0x1200).
// TODO: incomplete. Members are public: AI code and the AI helper functions read them directly.
class NPC : public NPCBase {
    SEAD_RTTI_OVERRIDE(NPC, NPCBase)
public:
    explicit NPC(const CreateArg& arg);
    ~NPC() override;

protected:
    InitResult init_() override;
    bool startPreparingForPreDelete_() override;
    void onDeleteRequested_(DeleteReason reason) override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void onPreDeleteStart_(PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;
    bool canWakeUp_() override;

public:
    void m61() override;
    void m63() override;
    void initMaybe() override;
    void calcMaybe() override;
    void updatePositionMaybe() override;
    void m73() override;
    void m76() override;
    void m79() override;
    void m93(int a1, float a2) override {
        if (_1058 <= a1) {
            _1058 = a1;
            _105c = a2;
        }
    }
    s32 m94() override { return _1054; }
    ksys::act::ActorWeapons* getWeapons() override { return &mWeapons; }
    void m101() override;
    void m114() override;
    void m117() override;
    void m119() override;
    void getAtk() override;
    void m126() override;
    uking::dmg::DamageManagerBase* getDamageMgr() override;
    void getPlayerRideInfo() override;
    bool m146() override;

    // FIXME: figure out return types, parameters and names
    // (m148 forwards (int, pointer, bool, bool) to ActorWeapons vtable slot 1)
    virtual void m148();
    virtual void m149();

    // Same as PlayerOrEnemy::sub_7100007CA8 / sub_7100007D58 (forward a request to the equipped
    // weapon in slot `idx`). Placeholder names.
    void sub_71000225B0(int idx, const Unk_71002eda38& arg);
    void sub_7100022660(int idx, const Unk_71002edaec& arg);

    /* 0x0c78 */ u8 _c78[0xcf8 - 0xc78];  // ActorAtk (CSV ActorAtk::ctor 0x710079d76c); getAtk
    /* 0x0cf8 */ void* _cf8 = nullptr;     // m126
    /* 0x0d00 */ ksys::act::ActorWeapons mWeapons{this};
    // DamageManagerBase subclass (vtable 0x71023ceca0, ctor 0x71002c9024); getDamageMgr
    /* 0x0da0 */ u8 _da0[0xe30 - 0xda0];
    /* 0x0e30 */ ksys::act::BaseProcLink _e30;
    /* 0x0e40 */ sead::Matrix34f _e40 = sead::Matrix34f::ident;
    /* 0x0e70 */ sead::Vector3f _e70 = sead::Vector3f::zero;
    /* 0x0e7c */ sead::Vector3f _e7c = sead::Vector3f::zero;
    /* 0x0e88 */ u32 _e88 = 0;
    /* 0x0e8c */ u16 _e8c = 0;
    /* 0x0e90 */ Unk_71002dccbc _e90{this};
    // object with vtable 0x71023cee88 (CSV methods Player::RideInfo::*); getPlayerRideInfo
    /* 0x0f28 */ u8 _f28[0xf60 - 0xf28];
    /* 0x0f60 */ ksys::act::BaseProcLink _f60;
    /* 0x0f70 */ ksys::act::BaseProcLink _f70;
    /* 0x0f80 */ void* _f80 = nullptr;
    /* 0x0f88 */ u8 _f88[0xfa8 - 0xf88];  // object with vtable 0x7102358858
    /* 0x0fa8 */ Unk_7100d3cd74 _fa8{this};  // m101
    /* 0x0fc8 */ ksys::act::BaseProcLink _fc8;
    /* 0x0fd8 */ ksys::act::BaseProcLink _fd8;
    /* 0x0fe8 */ u32 _fe8 = 0;  // flags
    /* 0x0ff0 */ sead::FixedSafeString<32> _ff0;
    /* 0x1028 */ sead::SafeString _1028;
    /* 0x1038 */ u32 _1038 = 0;
    /* 0x103c */ u8 _103c[0x1048 - 0x103c];
    /* 0x1048 */ u32 _1048 = 4;
    /* 0x104c */ u32 _104c = 0;
    /* 0x1050 */ bool _1050 = true;
    /* 0x1054 */ s32 _1054 = 0;
    /* 0x1058 */ s32 _1058 = -1;
    /* 0x105c */ f32 _105c = 0;
    /* 0x1060 */ u32 _1060 = 2;
    /* 0x1064 */ f32 _1064 = -1.0;
    /* 0x1068 */ f32 _1068 = -1.0;
    /* 0x106c */ f32 _106c[8]{};
    /* 0x108c */ f32 _108c = 5.0;
    /* 0x1090 */ f32 _1090 = 5.0;
    /* 0x1094 */ f32 _1094 = -1.0;
    /* 0x1098 */ u8 _1098[0x10a4 - 0x1098];
    /* 0x10a4 */ u32 _10a4 = 0;
    /* 0x10a8 */ u8 _10a8[0x10b0 - 0x10a8];
    /* 0x10b0 */ u32 _10b0 = 0;
    /* 0x10b8 */ void* _10b8 = nullptr;
    /* 0x10c0 */ void* _10c0 = nullptr;
    /* 0x10c8 */ u32 _10c8 = 0;
    /* 0x10d0 */ void* _10d0 = nullptr;
    /* 0x10d8 */ u32 _10d8 = 0;
    /* 0x10e0 */ void* _10e0 = nullptr;  // m119
    /* 0x10e8 */ sead::Matrix34f _10e8 = sead::Matrix34f::ident;
    /* 0x1118 */ f32 _1118 = 0;
    /* 0x111c */ f32 _111c = 1.0;
    /* 0x1120 */ f32 _1120 = 0;
    /* 0x1124 */ f32 _1124 = 1.0;
    /* 0x1128 */ f32 _1128 = 1.0;
    /* 0x112c */ f32 _112c = 1.0;
    /* 0x1130 */ void* _1130 = nullptr;
    /* 0x1138 */ void* _1138 = nullptr;
    /* 0x1140 */ u32 _1140 = 0;
    /* 0x1148 */ ksys::phys::MaterialMask _1148;
    /* 0x1160 */ ksys::phys::MaterialMask _1160;
    /* 0x1178 */ void* _1178[6]{};
    /* 0x11a8 */ u32 _11a8 = 2;
    /* 0x11ac */ u8 _11ac = 6;
    /* 0x11b0 */ ksys::act::BaseProcLink _11b0;
    /* 0x11c0 */ u16 _11c0 = 0;
    /* 0x11c2 */ u8 _11c2[0x11c8 - 0x11c2];
    /* 0x11c8 */ u8 _11c8 = 0;
    /* 0x11cc */ u32 _11cc = 0;
    /* 0x11d0 */ sead::Vector3f _11d0 = sead::Vector3f::zero;
    /* 0x11e0 */ ksys::act::BaseProcLink _11e0;
    /* 0x11f0 */ sead::Vector3f _11f0 = sead::Vector3f::zero;
};
KSYS_CHECK_SIZE_NX150(NPC, 0x1200);

}  // namespace uking::act
