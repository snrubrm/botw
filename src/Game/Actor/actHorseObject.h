#pragma once

#include <gfx/seadColor.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorBindSet.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::act {

// Names from the CSV (HorseObject::m2 / m3 at 0x7100e7b234 / 0x7100e7b354 and HorseReins::m2 / m3 at
// 0x7100e7bcfc / 0x7100e7be1c are their `checkDerivedRuntimeTypeInfo` / `getRuntimeTypeInfo` virtuals,
// from the vtable analysis; the namespace is a guess). Direct children of Actor (both RTTI statics are
// initialised with the Derive<Actor> vtable): HorseObject = RTTI static 0x71025ae9e0 (HorseBase::_840 /
// _850, cast in HorseBase::m117, HorseManeCollarSyncAction ...), HorseReins = RTTI static 0x71025ae9d0
// (HorseBase::_860 / _870 / _880, cast in HorseBase::m117, HorseReinsBindAction, HorseSaddleBindAction,
// HorseManeGrabbedAction ...). Both link back to their horse with a BaseProcLink at +0x840.
//
// HorseObject (factory 0x7100e7a5b8: new(0x1418)) has a not yet modelled bind-list object (an
// ActorBind-like with its own vtable, 0xbb8 bytes, ctor 0x7100e7a634) at +0x850, so its constructor,
// destructors and the virtuals that use it (m64 / m69 / m70 / m81) are not written yet.
// Placeholder name (vtable 0x71024ebb00, ctor 0x7100e7a634, D1 / D0 0x7100e7a748 / 0x7100e7b44c): HorseObject's bind set
// with inline storage for 16 entries (size 0xbb8).
class Unk_71024ebb00 : public ksys::act::ActorBindSet {
public:
    Unk_71024ebb00();
    ~Unk_71024ebb00() override;

    /* 0x38 */ ksys::act::ActorBindEntry mStorage[16];
};
KSYS_CHECK_SIZE_NX150(Unk_71024ebb00, 0xbb8);

class HorseObject : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(HorseObject, ksys::act::Actor)
public:
    explicit HorseObject(const CreateArg& arg);
    ~HorseObject() override;

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

protected:
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;

public:
    Actor* m31() override;
    bool shouldUnload(s32* a1) override;
    void initMaybe() override;
    void calcMaybe() override;
    void m70() override;
    bool m81(const ksys::Message& message) override;

    /* 0x840 */ ksys::act::BaseProcLink _840;
    /* 0x850 */ Unk_71024ebb00 _850;
    /* 0x1408 */ sead::Color4u8 _1408{0, 0, 0, 0};
    /* 0x140c */ f32 _140c = 0;
    /* 0x1410 */ u8 _1410 = 0;  // bit 0: fade-in pending (cleared by initMaybe); bit 1 / 2: the horse's m139() value is
                              // applied (m70) with actor flag 0x20 reset / set
};
KSYS_CHECK_SIZE_NX150(HorseObject, 0x1418);

// Factory 0x7100e7b470: new(0x870) + inlined ctor.
class HorseReins : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(HorseReins, ksys::act::Actor)
public:
    explicit HorseReins(const CreateArg& arg);
    ~HorseReins() override;

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

protected:
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;

public:
    Actor* m31() override;
    bool shouldUnload(s32* a1) override;
    void initMaybe() override;
    void updatePositionMaybe() override;

    // 0x7100e7ba64 (declared only): `DynamicCast<Actor>(_840.getProc(nullptr, nullptr))`, the horse.
    Actor* sub_7100E7BA64();
    // 0x7100e7bc10 (declared only): `_840.acquire(horse, false)`.
    void sub_7100E7BC10(ksys::act::BaseProc* horse);

    /* 0x840 */ ksys::act::BaseProcLink _840;
    /* 0x850 */ ksys::act::BaseProcLink _850;
    /* 0x860 */ u32 _860 = 0;
    /* 0x864 */ u32 _864 = 0;
    /* 0x868 */ sead::BitFlag8 _868{3};  // bit 2: fade-in pending, bit 3: set the actor flag 0x20 on update
};
KSYS_CHECK_SIZE_NX150(HorseReins, 0x870);

}  // namespace uking::act
