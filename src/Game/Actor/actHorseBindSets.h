#pragma once

#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/ActorSystem/actActorBindSet.h"

namespace uking::act {

// Placeholder name (vtable 0x71024e8e18, ctor 0x7100e52280, D1 / D0 0x7100e5236c / 0x7100e52ef8): the bind set of
// HorseManeGrabbedAction (embedded at +0x20), 12 entries (size 0x8d8).
class Unk_71024e8e18 : public ksys::act::ActorBindSet {
public:
    Unk_71024e8e18();
    ~Unk_71024e8e18() override;

    /* 0x38 */ ksys::act::ActorBindEntry mStorage[12];
};
KSYS_CHECK_SIZE_NX150(Unk_71024e8e18, 0x8d8);

// Placeholder name (vtable 0x71024e92c0, ctor 0x7100e56548, D1 / D0 0x7100e54e8c / 0x7100e550f8): an ActorBindSet
// with inline storage for 20 entries (size 0xe98). Base of Unk_71024e9450.
class Unk_71024e92c0 : public ksys::act::ActorBindSet {
public:
    Unk_71024e92c0();
    ~Unk_71024e92c0() override;

    /* 0x38 */ ksys::act::ActorBindEntry mStorage[20];
};
KSYS_CHECK_SIZE_NX150(Unk_71024e92c0, 0xe98);

// Placeholder name (vtable 0x71024e9450, D1 / D0 0x7100e5625c / 0x7100e5629c; the constructor is inlined into
// HorseReinsDefaultAction's): the bind set of HorseReinsDefaultAction (embedded at +0x20). Binds the reins to
// the horse's bit: `mReinsRoot` is the "Reins_Root" bone of the reins model, `mBit` the "Bit" bone of the horse
// model. Size 0xf10.
class Unk_71024e9450 : public Unk_71024e92c0 {
public:
    Unk_71024e9450() = default;
    // Defined inline: HorseReinsDefaultAction's D1 / D0 inline it (the original also keeps an out-of-line copy for the
    // vtable).
    ~Unk_71024e9450() override = default;

    // 0x7100e562e4 (returns false), 0x7100e55c9c (1.4 KB, declared only). m5 is declared first so that it is the key
    // function (the vtable is emitted with its definition while m4 has no body).
    bool m5(ksys::act::BaseProc* proc) override;
    bool m4(ksys::act::BaseProc* proc) override;

    /* 0xe98 */ gsys::BoneAccessKeyEx mReinsRoot;
    /* 0xed0 */ gsys::BoneAccessKeyEx mBit;
    /* 0xf08 */ u8 mFlags = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71024e9450, 0xf10);

// Placeholder name (vtable 0x71024e9710, ctor 0x7100e56ee0, D1 / D0 0x7100e57118 / 0x7100e57b98): the bind set of
// HorseSaddleDefaultAction (embedded at +0x20), 36 entries (size 0x1a18).
class Unk_71024e9710 : public ksys::act::ActorBindSet {
public:
    Unk_71024e9710();
    // Defined inline: HorseSaddleDefaultAction's D1 / D0 inline it (the original also keeps an out-of-line copy for the
    // vtable).
    ~Unk_71024e9710() override { mEntries = nullptr; }

    /* 0x38 */ ksys::act::ActorBindEntry mStorage[36];
};
KSYS_CHECK_SIZE_NX150(Unk_71024e9710, 0x1a18);

}  // namespace uking::act
