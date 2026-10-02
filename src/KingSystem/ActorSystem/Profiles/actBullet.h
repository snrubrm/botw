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
    ~Bullet() override;

    Actor* m31() override;
    Actor* m48() override;
    void m52() override;
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
    /* 0xc78 */ u32 _c78 = 0;
    /* 0xc7c */ u16 _c7c = 0;
    /* 0xc7e */ u8 _c7e = 0;
    /* 0xc80 */ u64 _c80 = 0;
    /* 0xc88 */ sead::Vector3f _c88 = sead::Vector3f::zero;
    /* 0xc94 */ sead::Vector3f _c94 = sead::Vector3f::zero;
    /* 0xca0 */ f32 _ca0 = -1.0;
    /* 0xca8 */ u64 _ca8 = 0;
    /* 0xcb0 */ u64 _cb0 = 0;
    /* 0xcb8 */ u64 _cb8 = 0;
    /* 0xcc0 */ f32 _cc0 = 1.0;
    /* 0xcc4 */ u8 _cc4[0xcf4 - 0xcc4]{};
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
    const BaseProcLink& sub_71000056E4() const;
    // 0x7100006430 / 0x7100006580 / 0x71000066b0 (CSV names).
    bool isHoldByOwner(BaseProc* owner) const;
    bool isHold() const;
    bool isFittingOrShootingArrow() const;
};

}  // namespace acc

}  // namespace ksys::act
