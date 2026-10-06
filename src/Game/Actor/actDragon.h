#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/actEnemy.h"

namespace ksys::map {
class Object;
}

namespace uking::act {

// Name from the CSV (Dragon::*): the three dragons. vtable 0x7102356b28 (181 slots, no new
// virtuals), RTTI static 0x71025ae7c0 (parent: Enemy). ctor 0x710000b214 (CSV Dragon::ctor),
// factory 0x710000ae20: new(0x22c0).
// TODO: incomplete. Members are public: AI code reads them directly.
class Dragon : public Enemy {
    SEAD_RTTI_OVERRIDE(Dragon, Enemy)
public:
    explicit Dragon(const CreateArg& arg);
    // CSV Dragon::construct: the actor factory function.
    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);
    ~Dragon() override;

protected:
    PreDeletePrepareResult prepareForPreDelete_() override;
    bool startPreparingForPreDelete_() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    bool m33() override { return true; }
    void m34(sead::Vector3f* pos, f32* value) override {
        *pos = _1f60;
        *value = 300.0f;
    }
    bool shouldUnload(s32* a1) override;
    void m63() override;
    void initMaybe() override;
    void calcMaybe() override;
    void updatePositionMaybe() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    void afterModelMatrixUpdate() override;
    void m108() override;
    void m110(f32* a1, s32* a2) override;
    void m111(f32* a1, s32* a2) override;
    void m112(f32* a1, s32* a2) override;
    void m113(f32* a1, s32* a2) override;
    void m115() override;

    // Placeholder names (non-virtual functions called by the Dragon AI).
    bool sub_710000FDFC() const;
    bool sub_710000FE10();
    void sub_710000E500(const sead::SafeString& name);
    // 0x710000c440: the dragon's map object: Actor::mMapObject when _1f70 bit 28 is set, otherwise a lookup
    // by dragon kind (_1e0c) (declared only; DragonFireRoot::sub_71003687B4).
    ksys::map::Object* sub_710000C440() const;
    bool getGameDataFlagGrudgeAlive(int idx);  // CSV name
    // 0x710000ff60 (lane4 s45, unnamed in the CSV): `_1f70` has the bit `idx` and not the bit `idx + 4`.
    bool sub_710000FF60(int idx);
    bool getGameDataFlag(const sead::SafeString& name, int idx);  // CSV name
    void x(const sead::Matrix34f& mtx);  // CSV name (0x710000ff8c)
    void sub_710000C160(const Dragon* other);  // copies state from another dragon (DragonRoot::reenter_)
    // 0x710001014c: *_14c8.sub_71006FC514() (DragonMoveTo::enter_).
    const sead::Matrix34f& sub_710001014C() const;

    // Object with ctor 0x710000b710(this + 0x14c8); the Dragon AI reads 0x8b0-0x930.
    struct Unk_710000b710 {
        // 0x71006fc514: the matrix at +0x20.
        const sead::Matrix34f* sub_71006FC514() const;
        void sub_71006FD830(f32 start_frame, f32 end_frame);

        u8 _0[0x20];
        /* 0x20 */ sead::Matrix34f _20;
        u8 _50[0x8b8 - 0x50];
        /* 0x8b8 */ f32 _8b8;  // Dragon + 0x1d80 (DragonPlayASForDemo: 0 on enter, 1 on leave)
        u8 _8bc[0x930 - 0x8bc];
        /* 0x930 */ u16 _930;  // flags (Dragon + 0x1df8)
        u8 _932[0x938 - 0x932];
    };

    /* 0x14c8 */ Unk_710000b710 _14c8;
    /* 0x1e00 */ f32 _1e00;
    /* 0x1e04 */ f32 _1e04;
    /* 0x1e08 */ f32 _1e08;
    /* 0x1e0c */ s32 _1e0c;  // dragon kind (3 checked by getGameDataFlagGrudgeAlive)
    /* 0x1e10 */ sead::Vector3f _1e10;
    /* 0x1e1c */ u32 _1e1c = 0;
    /* 0x1e20 */ u64 _1e20 = 0;
    /* 0x1e28 */ sead::Matrix34f _1e28;
    /* 0x1e58 */ sead::Matrix34f _1e58;
    // gsys::BoneAccessKeyEx at 0x1e88, object with ctor 0x71010f122c at 0x1ec0, two
    // FixedSafeString<20> at 0x1ef0 / 0x1f18
    /* 0x1e88 */ u8 _1e88[0x1f40 - 0x1e88];
    /* 0x1f40 */ u8 _1f40[0x1f60 - 0x1f40];
    /* 0x1f60 */ sead::Vector3f _1f60;  // m34
    /* 0x1f6c */ u32 _1f6c = 0;
    /* 0x1f70 */ sead::BitFlag32 _1f70;  // ~45 AI accesses
    /* 0x1f78 */ sead::FixedSafeString<64> _1f78;
    // object with ctor 0x710000b9b0(this + 0x1fd0)
    /* 0x1fd0 */ u8 _1fd0[0x2270 - 0x1fd0];
    /* 0x2270 */ u8 _2270[0x22c0 - 0x2270];
};
KSYS_CHECK_SIZE_NX150(Dragon, 0x22c0);

bool getDragonItemDropPosition(sead::Vector3f* target_pos, const sead::Vector3f& current_pos);
}  // namespace uking::act
