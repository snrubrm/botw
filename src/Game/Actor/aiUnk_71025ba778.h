#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace ksys::act {
class Actor;
}

// Placeholder name (dtor 0x7100710078, deleting dtor 0x71007100d4; its other functions up to 0x71007107cc are not decompiled):
// the 0xe8-byte BoneHandleBase subclass at Unk_71025ba778 + 0x18 (a bone key at +0x20, an owned object at +0x70). Only its
// destructor is used (declared only; Unk_71025ba778's inline destructor calls it).
// Object that Unk_7100710078::m3 creates (factory 0x7100f72bf8, which inlines the constructor; name: placeholder after it).
// 0x18 bytes: a zeroed 8-byte field, then a sead::Buffer of 0xb0-byte elements with a gsys::BoneAccessKeyEx at +0x18.
// Only its destructor (0x7100f72b94, which frees the buffer) is used here; declared only.
class Unk_7100F72BF8 {
public:
    // Placeholder element (0xb0 bytes).
    struct Entry {
        u8 _0[0x18];
        gsys::BoneAccessKeyEx _18;
        /* 0x50 */ sead::Matrix34f _50;
        /* 0x80 */ sead::Matrix34f _80;
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0xb0);
    static_assert(offsetof(Entry, _50) == 0x50);
    static_assert(offsetof(Entry, _80) == 0x80);

    // 0x7100f72ca0 (placeholder name): builds the bone table of `arg.model` for `arg.name`.
    struct InitArg {
        gsys::Model* model;
        const char* name;
    };
    // 0x7100f72bf8 (placeholder name): allocates the object and runs init; null on failure.
    static Unk_7100F72BF8* create(sead::Heap* heap, const InitArg& arg);
    bool init(sead::Heap* heap, const InitArg& arg);

    ~Unk_7100F72BF8();
    void sub_7100F72FF4();
    void sub_7100F73114(s32 index);
    void sub_7100F731F8(s32 index, const sead::Matrix34f& matrix, bool update_cumulative,
                       bool propagate);

    /* 0x00 */ gsys::Model* _0;
    /* 0x08 */ sead::Buffer<Entry> _8;
};
KSYS_CHECK_SIZE_NX150(Unk_7100F72BF8, 0x18);

class Unk_7100710078 : public ksys::act::BoneHandleBase {
public:
    ~Unk_7100710078() override;
    // 0x71007102c0: applies the weighted relative bone rotation to the matrix chain.
    void m2(gsys::Model* model) override;
    bool m3(gsys::Model* model, bool sorted) override;
    const gsys::BoneAccessKey* m4() override;

    // 0x7100710124 (declared only; placeholder name): sets up the bone key `_20` for the bone `name` of `model`.
    void sub_7100710124(sead::Heap* heap, gsys::Model* model, const sead::SafeString& name);

    // The constructor is inline in the original (LynelRoot's constructor inlines it).
    /* 0x20 */ gsys::BoneAccessKeyEx _20;
    /* 0x58 */ sead::SafeString _58;
    /* 0x68 */ f32 _68 = 0.0f;  // blended towards Unk_71025ba778::_c by Unk_71025ba778::sub_710070F400
    /* 0x70 */ Unk_7100F72BF8* _70 = nullptr;  // owned object (deleted by the destructor)
    /* 0x78 */ sead::Matrix34f _78 = sead::Matrix34f::ident;
    /* 0xa8 */ sead::Matrix34f _a8 = sead::Matrix34f::ident;
    /* 0xd8 */ sead::Vector3f _d8{0.0f, 1.0f, 0.0f};
    u8 _e4[0xe8 - 0xe4];
};
KSYS_CHECK_SIZE_NX150(Unk_7100710078, 0xe8);

// Object shared by the Lynel body behaviors through the "LynelBodyControlUnit" AI tree variable.
// Placeholder name from its RTTI typeInfo static (0x71025ba778; parent: Unk_71025afb58); size and most
// members are unknown.
class Unk_71025ba778 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025ba778, Unk_71025afb58)
public:
    // Inline in the original (the owner's destructor inlines it; the out-of-line copies sit after LynelRoot's).
    ~Unk_71025ba778() override = default;

    // 0x710070f32c (placeholder name): clears `_8` and sets up the bone handle `_18` for `bone` on the actor's model.
    bool sub_710070F32C(sead::Heap* heap, ksys::act::Actor* actor, const sead::SafeString& bone);
    // 0x710070f350 (lane1 s47): LynelRoot::enter_ calls it: attaches the bone handle `_18` to the actor (unless `_100` is
    // attached) and sets bit 0 of `_8`.
    void sub_710070F350(ksys::act::Actor* actor);
    // 0x710070f79c: (LynelBodyFitToGroundNormal::m8) attaches the "Man_Spine_1" bone handle to the actor
    // if needed and sets bit 1 of `_8`.
    void sub_710070F79C(ksys::act::Actor* actor);
    // 0x710070f820: (LynelBodyFitToGroundNormal::m9; the actor argument is unused) clears bit 1 of `_8`.
    void sub_710070F820(ksys::act::Actor* actor);
    // 0x710070f398 (declared only; lane1 s46): LynelRoot::leave_ calls it with the actor: detaches the bone handles
    // (`_18`, `_100`) that the flags `_8` bit 0 / 1 say are attached.
    void sub_710070F398(ksys::act::Actor* actor);
    // Full 924-byte updater and LynelRoot::calc_ pass this body-control unit and its actor.
    void sub_710070F400(ksys::act::Actor* actor);

    /* 0x08 */ u8 _8 = 0;  // flags; bit 1: body fitting to the ground normal enabled
    /* 0x09 */ u8 _9[0xc - 0x9];
    /* 0x0c */ f32 _c = 0.0f;  // set to 1 / 0 by LynelStandBody::m8 / m9
    /* 0x10 */ f32 _10 = 0.14f;
    u8 _14[0x18 - 0x14];
    /* 0x18 */ Unk_7100710078 _18;
    /* 0x100 */ ksys::act::BoneHandle _100;  // "Man_Spine_1"
    /* 0x1a8 */ f32 _1a8 = 3.14159265f;  // the CorrectAngleMax of LynelBodyFitToGroundNormal
    u8 _1ac[0x1b0 - 0x1ac];
};
KSYS_CHECK_SIZE_NX150(Unk_71025ba778, 0x1b0);
