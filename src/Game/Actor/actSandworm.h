#pragma once

#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <prim/seadEnum.h>
#include <gsys/gsysModelAccessKey.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <random/seadRandom.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "KingSystem/System/VFRValue.h"

namespace ksys::phys {
class RigidBody;
}  // namespace ksys::phys

namespace uking::act {

// Name from the CSV (Sandworm::*): Molduga / Molduking. vtable 0x71023cf6d8 (181 slots, no new
// virtuals), RTTI static 0x71025b5838 (parent: Enemy). Factory 0x71002cbadc (CSV Sandworm::construct,
// which inlines the ctor): new(0x1658).
// TODO: incomplete. Members are public: AI code reads them directly.
// 0x148-byte element of Unk_71007237d0::_70 (built by 0x71007237d0: BoneHandle and BoneAccessKeyEx
// constructors only, so 0xe0-0x148 is trivial).
struct Unk_71007237d0Part {
    /* 0x00 */ ksys::act::BoneHandle handle;
    /* 0xa8 */ gsys::BoneAccessKeyEx _a8;
    /* 0xe0 */ u32 _e0;
    // Bone local matrix copied by the Dragon part groups (Unk_7102357188::m0 0x710000f228).
    /* 0xe4 */ sead::Matrix34f _e4;
    /* 0x114 */ u8 _114[0x148 - 0x114];
};
KSYS_CHECK_SIZE_NX150(Unk_71007237d0Part, 0x148);

// Bone part set at Sandworm + 0x14d0, named after its init function 0x71007237d0 (actor, bone names,
// part count, matrix count, heap; the constructor is inline). Its code lives near Unk_7100722420.
// Only the members the destructor and init touch are modelled.
struct Unk_71007237d0 {
    ~Unk_71007237d0() {
        sub_71002CCFD4();
        _40.freeBuffer();
        _50.freeBuffer();
    }

    // 0x71007237d0 (placeholder name): allocates `num_parts` parts (searching / naming those with a non-empty
    // name in the actor's model) and `num_values` matrices and values (values set to -1). False if an allocation
    // fails or the actor has no model.
    bool sub_71007237D0(ksys::act::Actor* actor, const sead::SafeString* names, s32 num_parts, s32 num_values,
                        sead::Heap* heap);
    // 0x7100723a84 (placeholder name): searches the bone `name` of the actor's model for _8.
    bool sub_7100723A84(const sead::SafeString& name);
    // 0x710072479c (placeholder name): passes every part's bone handle to the actor (Actor::sub_71011DA868).
    // Called by Sandworm::preDelete2_ and startPreparingForPreDelete_.
    void sub_710072479C();

    // 0x71002ccfd4 (placeholder name): frees the part buffer and both value buffers. Inline: the original
    // emits it in the Sandworm TU, away from the rest of this class.
    void sub_71002CCFD4() {
        _70.freeBuffer();
        _40.freeBuffer();
        _50.freeBuffer();
    }

    /* 0x00 */ ksys::act::Actor* mActor = nullptr;
    /* 0x08 */ gsys::BoneAccessKeyEx _8;
    /* 0x40 */ sead::Buffer<sead::Matrix34f> _40;  // 0x30-byte elements (init)
    /* 0x50 */ sead::Buffer<f32> _50;  // 4-byte elements (init; type a guess)
    /* 0x60 */ void* _60 = nullptr;
    /* 0x68 */ f32 _68 = 0.05;
    /* 0x6c */ u32 _6c = 0;
    /* 0x70 */ sead::Buffer<Unk_71007237d0Part> _70;
};
KSYS_CHECK_SIZE_NX150(Unk_71007237d0, 0x80);

// Placeholder name (vtable 0x71023cfcf0, size 0x318, D1 0x7100682350): the terrain-shape holder
// Sandworm::prepareInit_ (0x71002ccc40) allocates at Sandworm + 0x1588. Its D1 unlinks the object
// from a global list and releases the shared tera shape at + 8 through the tera system; the runtime
// writes a position and a shape into the 15 0x2c-byte slots at + 0x28.
class Unk_71023cfcf0 {
public:
    struct Slot {
        /* 0x00 */ f32 _0;
        /* 0x04 */ f32 _4;
        /* 0x08 */ f32 _8;
        /* 0x0c */ u32 _c;
        /* 0x10 */ f32 _10;
        /* 0x14 */ f32 _14;
        /* 0x18 */ f32 _18;
        /* 0x1c */ f32 _1c;
        /* 0x20 */ u32 _20;
        /* 0x24 */ u32 _24;
        /* 0x28 */ u32 _28;
    };
    KSYS_CHECK_SIZE_NX150(Slot, 0x2c);

    virtual ~Unk_71023cfcf0();

    // 0x71006825f0 (placeholder name): the game checks this before deleting the holder.
    bool sub_71006825F0();
    // 0x71002cbde4 (placeholder name): updates the shape at `mode` for a position.
    void sub_71002CBDE4(f32 x, f32 z, s32 mode);

    /* 0x08 */ void* _8 = nullptr;
    /* 0x10 */ u16 _10 = 0;
    /* 0x12 */ u8 _12 = 0;
    /* 0x13 */ u8 _13[0x18 - 0x13];
    /* 0x18 */ u64 _18 = 0;
    /* 0x20 */ u64 _20 = 0;
    /* 0x28 */ sead::SafeArray<Slot, 15> mSlots;
    /* 0x2bc */ u32 _2bc = 0;
    /* 0x2c0 */ u8 _2c0[0x2d4 - 0x2c0];
    /* 0x2d4 */ u32 _2d4 = 0;
    /* 0x2d8 */ u8 _2d8[0x2f8 - 0x2d8];
    /* 0x2f8 */ f32 _2f8 = 0;
    /* 0x2fc */ u8 _2fc[0x318 - 0x2fc];
};
KSYS_CHECK_SIZE_NX150(Unk_71023cfcf0, 0x318);

class Sandworm : public Enemy {
    SEAD_RTTI_OVERRIDE(Sandworm, Enemy)
public:
    // Placeholder (the terrain-shape index stored in _163c; SandwormTeraShapeChanger sets it and
    // sub_71002CD990 maps it to the shape passed to the holder).
    SEAD_ENUM(TeraShape, _0, _1, _2, _3, _4)

    explicit Sandworm(const CreateArg& arg);
    ~Sandworm() override;

    // 0x71002cd930 (96 B, not decompiled; placeholder name, lane4 s85): writes `pos` into the 15 entries of the
    // object at +0x1588 (called by SandwormTeraPach::m8).
    void sub_71002CD930(const sead::Vector3f& pos);
    // 0x71002cd990 (80 B, not decompiled; placeholder name): called by SandwormTeraPach::m7 with the blended
    // node position.
    void sub_71002CD990(const sead::Vector3f& pos);

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

protected:
    bool startPreparingForPreDelete_() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    void killWithDropsAndEffects(int a1) override;
    // 0x71002cdb48 (CSV Sandworm::kill_; declared only).
    void sub_71002CDB48();
    // 0x71002cdde8 (unnamed in the CSV; declared only; SandwormRoot::calc_): with an active character controller,
    // moves the position at +0x1644 towards the actor (distance < 30, height difference < 15) via 0x710072fbd4.
    void sub_71002CDDE8();
    // Declaration only.
    void sub_71002CDAE4(bool on);
    // 0x71002ce2c8 (unnamed in the CSV; same shape as GiantEnemy::setNecklaceFlag, but another tag (hash 0x12ad8456, name
    // unknown) and it passes index + 1).
    void setNecklaceFlag(s32 index);
    void m56(sead::Vector3f* pos) override;
    void m63() override;
    void initMaybe() override;
    void calcMaybe() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    bool m81(const ksys::Message* message) override;
    bool m146() override;
    bool weaponDroppedByEnemy() override;
    // 0x71002cdfcc: creates an 8-byte material filter (vtable 0x71023cf690).
    ksys::phys::NavMeshCharacterUnk58* m179(sead::Heap* heap) override;

    /* 0x14c8 */ s32 _14c8 = 2;
    /* 0x14cc */ s32 _14cc = 2;
    /* 0x14d0 */ Unk_71007237d0 _14d0;
    /* 0x1550 */ sead::Matrix34f _1550 = sead::Matrix34f::ident;
    /* 0x1580 */ f32 _1580 = 3.0;
    /* 0x1584 */ u8 _1584 = 0;
    /* 0x1588 */ Unk_71023cfcf0* _1588 = nullptr;
    /* 0x1590 */ ksys::VFRValue _1590{0.0f};
    /* 0x159c */ f32 _159c = 0;
    /* 0x15a0 */ u32 _15a0 = 0;
    /* 0x15a4 */ u32 _15a4 = 0;
    /* 0x15a8 */ u32 _15a8 = 0;
    /* 0x15ac */ f32 _15ac = 0;  // sand offset speed (SandwormASPlay)
    /* 0x15b0 */ f32 _15b0 = 0;  // target sand offset (SandwormASPlay)
    /* 0x15b4 */ u32 _15b4;
    /* 0x15b8 */ gsys::BoneAccessKeyEx _15b8;
    /* 0x15f0 */ gsys::BoneAccessKeyEx _15f0;
    /* 0x1628 */ sead::Random _1628;
    /* 0x1638 */ u8 _1638 = 0;
    /* 0x163c */ TeraShape _163c;
    /* 0x1640 */ u32 _1640 = 0;
    /* 0x1644 */ sead::Vector3f _1644 = sead::Vector3f::zero;
    /* 0x1650 */ ksys::phys::RigidBody* _1650 = nullptr;  // m56
};
KSYS_CHECK_SIZE_NX150(Sandworm, 0x1658);

}  // namespace uking::act
