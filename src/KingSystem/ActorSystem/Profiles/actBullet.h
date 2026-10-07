#pragma once

#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

// Name from the CSV (Bullet::construct 0x71000045e0 = new(0xd00) + inlined ctor; RTTI static
// 0x71025ae5f0, parent DynamicActor; vtable 0x7102355940 = DynamicActor's 163 slots + m163).
// TODO: incomplete (overrides not decompiled; field meanings unknown).
class Bullet : public DynamicActor {
    SEAD_RTTI_OVERRIDE(Bullet, DynamicActor)
public:
    explicit Bullet(const CreateArg& arg);
    static BaseProc* construct(const CreateArg& arg, sead::Heap* heap);
    ~Bullet() override;

    Actor* m31() override;
    Actor* m48() override;
    bool m52(sead::Vector3f* out, Chemical* chemical) override;
    void initMaybe() override;
    void m73() override;
    void m76(VFR::ScopedDeltaSetter* setter) override;
    void updateMtxFromPhysics() override;

    // 0x71000048d0: the actor linked by _ba0 (the bullet's owner), if any.
    virtual Actor* m163();

    // 0x71000048bc / 0x71000048c8: set _b90.
    void sub_71000048BC(BaseProc* proc);
    void sub_71000048C8(const BaseProcLink& link);
    // 0x710000497c / 0x7100004988: set _ba0 (the owner).
    void sub_710000497C(BaseProc* proc);
    void sub_7100004988(const BaseProcLink& link);

    /* 0xb90 */ BaseProcLink _b90;
    /* 0xba0 */ BaseProcLink _ba0;  // owner (acc::Bullet::sub_71000056E4, m163)
    /* 0xbb0 */ BaseProcLink _bb0;
    /* 0xbc0 */ BaseProcLink _bc0;
    // A link, a critical section and a link (the dtor keeps &_bd0 and &_bd0._10 in registers).
    struct Unk_bd0 {
        struct Unk_10 {
            /* 0x00 */ sead::CriticalSection _0;
            /* 0x40 */ BaseProcLink _40;
        };

        /* 0x00 */ BaseProcLink _0;
        /* 0x10 */ Unk_10 _10;
    };

    /* 0xbd0 */ Unk_bd0 _bd0;
    /* 0xc30 */ u64 _c30 = 0;
    /* 0xc38 */ u64 _c38 = 0;
    /* 0xc40 */ u64 _c40 = 0;
    /* 0xc48 */ u64 _c48 = 0;
    /* 0xc50 */ u64 _c50 = 0;
    /* 0xc58 */ u64 _c58 = 0;
    /* 0xc60 */ u64 _c60 = 0;
    /* 0xc68 */ u64 _c68 = 0;
    /* 0xc70 */ f32 _c70 = 1.0;
    /* 0xc74 */ u32 _c74 = 0;
    /* 0xc78 */ u16 _c78 = 0;
    /* 0xc7a */ bool _c7a = false;  // Arrow::enter_
    /* 0xc7b */ u8 _c7b = 0;
    /* 0xc7c */ u16 _c7c = 0;
    /* 0xc7e */ u8 _c7e = 0;
    /* 0xc80 */ u64 _c80 = 0;
    /* 0xc88 */ sead::Vector3f _c88 = sead::Vector3f::zero;
    /* 0xc94 */ sead::Vector3f _c94 = sead::Vector3f::zero;
    /* 0xca0 */ f32 _ca0 = -1.0;
    /* 0xca4 */ u32 _ca4;  // padding (not initialised)
    /* 0xca8 */ f32 _ca8 = 0;  // PlayerBeamMove::m34
    /* 0xcac */ f32 _cac = 0;  // PlayerBeamMove::m37 (as an int)
    /* 0xcb0 */ u64 _cb0 = 0;
    /* 0xcb8 */ u64 _cb8 = 0;
    /* 0xcc0 */ f32 _cc0 = 1.0;
    /* 0xcc4 */ sead::Vector2f _cc4[6];
    /* 0xcf4 */ u16 _cf4 = 0;
    /* 0xcf8 */ f32 _cf8 = -1.0;
    /* 0xcfc */ f32 _cfc = 1.0;
};
KSYS_CHECK_SIZE_NX150(Bullet, 0xd00);

namespace acc {

// Accessor (CSV act::acc::Bullet::*).
class Bullet : public ActorConstDataAccess {
public:
    // 0x71000056e4: the bullet's owner link (_ba0), or the dummy link if the actor is no Bullet.
    BaseProcLink& sub_71000056E4() const;
    // 0x7100006430 / 0x7100006580 / 0x71000066b0 (CSV names).
    bool isHoldByOwner(BaseProc* owner) const;
    bool isHold() const;
    bool isFittingOrShootingArrow() const;

    // 0x7100006034 (placeholder name): the Bullet of the accessor if it is sleeping and `_bd0._0` holds
    // `owner`, else null. Used by the setters below.
    act::Bullet* getBulletOwnedByMaybe(BaseProc* owner) const;
    // 0x71000057dc / 0x71000058d4: bits 1 / 8 of `_cf4` (false without a Bullet); 0x71000059cc: `_cc0`
    // (1.0 without a Bullet).
    bool sub_71000057DC() const;
    bool sub_71000058D4() const;
    f32 sub_71000059CC() const;
    // 0x7100005ac8 - 0x7100005f60: set the AI tree variable named in the comment of the Bullet owned by
    // `owner` (placeholder names).
    void setIsUseAtCollision(bool value, BaseProc* owner);  // IsUseAtCollision
    void setAttackPower(s32 value, BaseProc* owner);   // AttackPower
    void setAttackAttr(s32 value, BaseProc* owner);   // AttackAttr
    void setAttackType(s32 value, BaseProc* owner);   // AttackType
    void setCutGrassType(s32 value, BaseProc* owner);   // CutGrassType
    void setXLinkKey(const sead::SafeString& value, BaseProc* owner);  // XLinkKey
    void setRange(f32 value, BaseProc* owner);   // Range
    void setScaleTime(f32 value, BaseProc* owner);   // ScaleTime
    void setAttackTarget(s32 value, BaseProc* owner);   // AttackTarget
    void setAttackDirType(s32 value, BaseProc* owner);   // AttackDirType
    void setGolemPartInitialIceMagic(bool value, BaseProc* owner);  // GolemPartInitialIceMagic
    void setGolemPartInitialBurn(bool value, BaseProc* owner);  // GolemPartInitialBurn
    // 0x7100005fd0 (declared only): starts xlink event 0x19 with `value` (after updating the model's xlink
    // scale).
    void startXLinkEvent19Maybe(u32 value, BaseProc* owner);
    // 0x7100006144 / 0x71000061a8: read a map unit parameter of the Bullet owned by `owner`.
    bool getMapUnitParamF32(f32* out, const sead::SafeString& key, BaseProc* owner);
    bool getMapUnitParamVec3(sead::Vector3f* out, const sead::SafeString& key, BaseProc* owner);
    // 0x7100006214: AI tree variable "IsReflectThrownBullet" (false without a Bullet).
    bool isReflectThrownBullet() const;
    // 0x710000634c / 0x710000638c: set `_b90` / `_ba0` of the Bullet owned by `owner`.
    void sub_710000634C(BaseProc* proc, BaseProc* owner);
    void sub_710000638C(BaseProc* proc, BaseProc* owner);
    // 0x71000063cc: sets `_cf8`; 0x71000063f4: the gravity factor of the main body.
    void sub_71000063CC(f32 value, BaseProc* owner);
    void sub_71000063F4(f32 factor, BaseProc* owner);
};

}  // namespace acc

}  // namespace ksys::act
