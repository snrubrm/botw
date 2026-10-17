#pragma once

#include "Game/Actor/aiUnk_71010F122C.h"

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <container/seadBuffer.h>
#include <container/seadRingBuffer.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actSandworm.h"

namespace ksys::map {
class Object;
}

namespace uking::act {

// Bone handle with vtable 0x7102450330 (D1 0x7100700400, D0 0x7100700404, m2 0x71006ffa14 not decompiled;
// m3 / m4 inherited). Built inline by the Dragon part constructor 0x710000b710; its members start in the tail
// padding of Unk_71024512e8.
class Unk_7102450330 : public Unk_71024512e8 {
public:
    Unk_7102450330() { _98 = true; }

    void m2(gsys::Model* model) override;

    /* 0x9c */ sead::Matrix34f _9c = sead::Matrix34f::ident;
    /* 0xcc */ sead::Vector3f _cc = sead::Vector3f::ones;
    /* 0xd8 */ sead::Matrix34f _d8 = sead::Matrix34f::ident;
    /* 0x108 */ sead::Matrix34f _108 = sead::Matrix34f::ident;
    /* 0x138 */ sead::Matrix34f _138 = sead::Matrix34f::ident;
    /* 0x168 */ f32 _168 = 1.0f;
    /* 0x16c */ f32 _16c = 1.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_7102450330, 0x170);

// 0x280-byte bone part of Dragon::Unk_710000b710 (three inline, more in its _850 buffer). Not polymorphic:
// array delete runs ~BoneAccessKeyEx(+0x170) then ~Unk_71024512e8 directly. 0x1a8-0x280 is never
// initialised by the constructor.
struct Unk_710000b710Part {
    /* 0x000 */ Unk_7102450330 handle;
    /* 0x170 */ gsys::BoneAccessKeyEx _170;
    /* 0x1a8 */ u8 _1a8[0x280 - 0x1a8];
};
KSYS_CHECK_SIZE_NX150(Unk_710000b710Part, 0x280);

// Bone part group of the Dragon (four Unk_7102357168 at 0x1fd0, one Unk_7102357188 at 0x2270):
// parts attached to bones of `actor`. Name is descriptive; the base has no vtable of its own in
// the binary (no virtual destructor; two virtual slots).
class DragonBonePartGroup {
public:
    virtual void m0() = 0;
    virtual void m1() = 0;
    // 0x710000d2e4 out of line (shared by both derived classes): releases the parts' bone handles,
    // then frees the two heap arrays.
    void destroy();

    // inline-only in the original; name is a guess (Dragon::startPreparingForPreDelete_ repeats it
    // for all five groups): releases the parts' bone handles once.
    void detachParts() {
        if (!attached)
            return;
        attached = false;
        if (!actor)
            return;
        for (s32 i = 0; i < numParts; ++i)
            actor->sub_71011DA868(&parts[i].handle);
    }

    /* 0x08 */ ksys::act::Actor* actor;
    // Bone keys (0x38 bytes: Unk_7102357188::m0 reads the model unit / bone index of the first two).
    /* 0x10 */ sead::Buffer<gsys::BoneAccessKeyEx> _10;
    /* 0x20 */ sead::Buffer<Unk_71007237d0Part> parts;
    /* 0x30 */ s32 numParts;
    /* 0x34 */ bool attached;
};

// vtable 0x7102357168 (m0 0x71000102b8, m1 0x710001049c); four of them at Dragon + 0x1fd0
// (array ctor 0x710000b9b0).
class Unk_7102357168 : public DragonBonePartGroup {
public:
    void m0() override;
    void m1() override;

    /* 0x38 */ sead::Vector3f _38;
    /* 0x44 */ sead::Vector3f _44;
    /* 0x50 */ sead::Vector3f _50;
    /* 0x5c */ sead::Vector3f _5c;
    /* 0x68 */ sead::FixedSafeString<32> _68;
    /* 0xa0 */ u32 _a0;
    // m0 resets it to 0.
    /* 0xa4 */ f32 _a4;
};
KSYS_CHECK_SIZE_NX150(Unk_7102357168, 0xa8);

// vtable 0x7102357188 (m0 0x710000f228, m1 0x710000ded8); one at Dragon + 0x2270.
class Unk_7102357188 : public DragonBonePartGroup {
public:
    void m0() override;
    void m1() override;

    /* 0x38 */ u8 _38[0x50 - 0x38];
};
KSYS_CHECK_SIZE_NX150(Unk_7102357188, 0x50);

// Name from the CSV (Dragon::*): the three dragons. vtable 0x7102356b28 (181 slots, no new
// virtuals), RTTI static 0x71025ae7c0 (parent: Enemy). ctor 0x710000b214 (CSV Dragon::ctor),
// factory 0x710000ae20: new(0x22c0).
// TODO: incomplete. Members are public: AI code reads them directly.
class Dragon : public Enemy {
    SEAD_RTTI_OVERRIDE(Dragon, Enemy)
public:
    explicit Dragon(const CreateArg& arg);
    // Canonical declaration verified and gated by lane1 (acc300dcf).
    f32 x_0() const;
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
    // 0x710000d474 (declared only; 168 B): when _1f70 bit 22 is set, clears it and removes three named rigid bodies
    // from the world.
    void sub_710000D474();
    // 0x710000eca4 (declared only; 584 B): the counterpart of sub_710000D474 (updatePositionMaybe calls it within
    // 350 of _1f54 when m139() >= 1).
    void sub_710000ECA4();
    // 0x710000d51c (placeholder name): unless _1f70 bit 28 is set, `_1ec0.sub_71010F17FC(false)` (inlined in m63).
    void sub_710000D51C();
    bool sub_710000FE10();
    void sub_710000E500(const sead::SafeString& name);
    // 0x710000ea88 (declared by lane1 s95; placeholder name): DragonRoot::enter_ passes HornAnmName.
    void sub_710000EA88(const sead::SafeString& name);
    // 0x710000ec50 (declared by lane1 s95; placeholder name): starts an AS (5, 2) on the dragon's ASList.
    void sub_710000EC50();
    // 0x710000c440: the dragon's map object: Actor::mMapObject when _1f70 bit 28 is set, otherwise a lookup
    // by dragon kind (_1e0c) (declared only; DragonFireRoot::sub_71003687B4).
    ksys::map::Object* sub_710000C440() const;
    bool getGameDataFlagGrudgeAlive(int idx);  // CSV name
    // 0x710000ff60 (lane4 s45, unnamed in the CSV): `_1f70` has the bit `idx` and not the bit `idx + 4`.
    bool sub_710000FF60(int idx);
    // 0x710000f70c (lane4 s46, unnamed in the CSV): `_1f70` has the bit `idx + 4`.
    bool sub_710000F70C(int idx);
    // Full F654 / FC70 bodies and independent DragonIceRoot / DragonRoot callers prove these arguments.
    void sub_710000F36C(s32 idx);
    void sub_710000F52C(s32 idx);
    void sub_710000F654(s32 idx);
    void sub_710000FC70(s32 idx, bool start, bool secondary);
    bool getGameDataFlag(const sead::SafeString& name, int idx);  // CSV name
    // 0x710000bc38 (CSV name; lane1 s45): sets the game data flag `name` of the dragon (`idx` -1: the dragon's own).
    void setGameDataFlag(bool value, const sead::SafeString& name, int idx);
    void x(const sead::Matrix34f& mtx);  // CSV name (0x710000ff8c)
    void sub_710000C160(const Dragon* other);  // copies state from another dragon (DragonRoot::reenter_)
    // 0x710001014c: *_14c8.sub_71006FC514() (DragonMoveTo::enter_).
    const sead::Matrix34f& sub_710001014C() const;

    // Object with ctor 0x710000b710(this + 0x14c8); the Dragon AI reads 0x8b0-0x930.
    struct Unk_710000b710 {
        // 0x71006fc514: the matrix at +0x20.
        const sead::Matrix34f* sub_71006FC514() const;
        void sub_71006FD830(f32 start_frame, f32 end_frame);
        // FF8C supplies a normalized matrix; 6FB3FC copies it to the existing matrix20.
        void sub_71006FB3FC(const sead::Matrix34f& matrix);

        // 0x71006fb8a8 (placeholder name): with flags 2 and 3 set, detaches the three bone parts and every
        // valid named part of _850 from the actor (Actor::sub_71011DA868), then clears flag 3.
        void sub_71006FB8A8();
        // 0x71006fb7f8 (placeholder name): with flag 2 set, detaches the parts (flag 3), frees _850 and
        // _8, then clears flag 2. Called by the Dragon destructor.
        void sub_71006FB7F8();

        // 0x71006fbad4 (placeholder name): clears flag 0 and the translation of _860, then runs the reset steps
        // whose skip flags (0x800, 0x20, 0x10, 0x80) are clear. Called by startPreparingForPreDelete_.
        void sub_71006FBAD4();
        // 0x71006fabc8 / 0x71006fb51c / 0x71006fbb64 (464 / 732 / 1696 B, declaration only; placeholder names).
        void sub_71006FABC8();
        void sub_71006FB51C();
        void sub_71006FBB64();

        ~Unk_710000b710() { sub_71006FB7F8(); }

        /* 0x000 */ ksys::act::Actor* mActor = nullptr;
        /* 0x008 */ sead::RingBuffer<u8> _8;  // element type unknown (trivial: freed without destructors)
        /* 0x020 */ sead::Matrix34f _20 = sead::Matrix34f::ident;
        /* 0x050 */ sead::Matrix34f _50 = sead::Matrix34f::ident;
        /* 0x080 */ f32 _80 = 1.0f;
        // _90 / _a0 / _b0 (read by sub_71006FD830) are the translation of this matrix.
        /* 0x084 */ sead::Matrix34f _84 = sead::Matrix34f::ident;
        /* 0x0b8 */ Unk_710000b710Part _b8;
        // _3e0 / _3f0 / _400 (read by sub_71006FD830) are the translation of _338.handle._9c.
        /* 0x338 */ Unk_710000b710Part _338;
        // lane4 s46: snapshot of the values above taken by sub_71006FD830.
        /* 0x5b8 */ f32 _5b8;
        /* 0x5bc */ f32 _5bc;
        /* 0x5c0 */ f32 _5c0;
        /* 0x5c4 */ f32 _5c4;
        /* 0x5c8 */ f32 _5c8;
        /* 0x5cc */ f32 _5cc;
        /* 0x5d0 */ Unk_710000b710Part _5d0;
        /* 0x850 */ sead::Buffer<Unk_710000b710Part> _850;
        /* 0x860 */ sead::Matrix34f _860 = sead::Matrix34f::ident;
        u8 _890[0x8a4 - 0x890];
        /* 0x8a4 */ f32 _8a4;  // start frame (-1: none)
        /* 0x8a8 */ f32 _8a8;  // end frame
        /* 0x8ac */ f32 _8ac;
        u8 _8b0[0x8b8 - 0x8b0];
        /* 0x8b8 */ f32 _8b8;  // Dragon + 0x1d80 (DragonPlayASForDemo: 0 on enter, 1 on leave)
        /* 0x8bc */ sead::Vector3f _8bc;  // Dragon + 0x1d84: offset added by DragonPlayASForDemo (flag 0x40)
        u8 _8c8[0x930 - 0x8c8];
        /* 0x930 */ u16 _930;  // flags (Dragon + 0x1df8)
        u8 _932[0x938 - 0x932];
    };

    /* 0x14c8 */ Unk_710000b710 _14c8;
    /* 0x1e00 */ f32 _1e00;
    /* 0x1e04 */ f32 _1e04;
    /* 0x1e08 */ f32 _1e08;
    /* 0x1e0c */ s32 _1e0c;  // dragon kind (3 checked by getGameDataFlagGrudgeAlive)
    /* 0x1e10 */ sead::Vector3f _1e10;
    // 2026-10-07: x_0 at 0x710000c630 reads XYZ here and returns their vector length.
    /* 0x1e1c */ sead::Vector3f _1e1c{0.0f, 0.0f, 0.0f};
    /* 0x1e28 */ sead::Matrix34f _1e28;
    /* 0x1e58 */ sead::Matrix34f _1e58;
    // gsys::BoneAccessKeyEx at 0x1e88, object with ctor 0x71010f122c at 0x1ec0, two
    // FixedSafeString<20> at 0x1ef0 / 0x1f18
    /* 0x1e88 */ gsys::BoneAccessKeyEx _1e88;
    /* 0x1ec0 */ Unk_710250d530 _1ec0;
    /* 0x1ef0 */ sead::FixedSafeString<20> _1ef0;
    /* 0x1f18 */ sead::FixedSafeString<20> _1f18;  // current horn animation (sub_710000EA88)
    /* 0x1f40 */ u8 _1f40[0x1f4c - 0x1f40];
    // FC70 writes these; calcMaybe D5E0 passes them in s0/s1 to6FD6BC.
    /* 0x1f4c */ f32 _1f4c;
    /* 0x1f50 */ f32 _1f50;
    // updatePositionMaybe compares the actor's horizontal distance to this point with 350.
    /* 0x1f54 */ sead::Vector3f _1f54;
    /* 0x1f60 */ sead::Vector3f _1f60;  // m34
    /* 0x1f6c */ f32 _1f6c = 0;  // copied to the dragon BGM (DragonRoot::calc_)
    /* 0x1f70 */ sead::BitFlag32 _1f70;  // ~45 AI accesses
    // B214 stores capacity 16 at +1f88 and the buffer pointer +1f8c at +1f80.
    /* 0x1f78 */ sead::FixedSafeString<16> _1f78;
    // DragonItemRoot 36CE54 copies these f32 values to the TransOffset Vector3f.
    /* 0x1fa0 */ u8 _1fa0[0xc];
    /* 0x1fac */ f32 _1fac;
    /* 0x1fb0 */ u8 _1fb0[0xc];
    /* 0x1fbc */ f32 _1fbc;
    /* 0x1fc0 */ u8 _1fc0[0xc];
    /* 0x1fcc */ f32 _1fcc;
    // Array ctor 0x710000b9b0(this + 0x1fd0).
    /* 0x1fd0 */ Unk_7102357168 _1fd0[4];
    /* 0x2270 */ Unk_7102357188 _2270;
};
KSYS_CHECK_SIZE_NX150(Dragon, 0x22c0);

bool getDragonItemDropPosition(sead::Vector3f* target_pos, const sead::Vector3f& current_pos);
// 0x710000ae6c (declared by lane1 s95; placeholder name): returns false. DragonRoot::calc_ calls it after
// its ground ray cast and ignores the result.
bool sub_710000AE6C();

// 0x710000aecc (CSV dragon::isWithin1kmOfHyruleCastle): false within 1000 (XZ) of Hyrule Castle in the open world.
bool isWithin1kmOfHyruleCastle();

}  // namespace uking::act
