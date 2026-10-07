#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace ksys::act {
class Actor;
}

// Placeholder name (dtor 0x7100710078, deleting dtor 0x71007100d4; its other functions up to 0x71007107cc are not decompiled):
// the 0xe8-byte BoneHandleBase subclass at Unk_71025ba778 + 0x18 (a bone key at +0x20, an owned object at +0x70). Only its
// destructor is used (declared only; Unk_71025ba778's inline destructor calls it).
class Unk_7100710078 : public ksys::act::BoneHandleBase {
public:
    ~Unk_7100710078() override;
    // 0x71007102c0 (1184 B) / 0x7100710124 (340 B) / 0x7100710760 (8 B): declared only.
    void m2(gsys::Model* model) override;
    bool m3(gsys::Model* model, bool sorted) override;
    const gsys::BoneAccessKey* m4() override;

    // The constructor is inline in the original (LynelRoot's constructor inlines it).
    /* 0x20 */ gsys::BoneAccessKeyEx _20;
    /* 0x58 */ sead::SafeString _58;
    /* 0x68 */ s32 _68 = 0;
    /* 0x70 */ void* _70 = nullptr;  // owned object (deleted by the destructor)
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

    // 0x710070f79c: (LynelBodyFitToGroundNormal::m8) attaches the "Man_Spine_1" bone handle to the actor
    // if needed and sets bit 1 of `_8`.
    void sub_710070F79C(ksys::act::Actor* actor);
    // 0x710070f820: (LynelBodyFitToGroundNormal::m9; the actor argument is unused) clears bit 1 of `_8`.
    void sub_710070F820(ksys::act::Actor* actor);
    // 0x710070f398 (declared only; lane1 s46): LynelRoot::leave_ calls it with the actor: detaches the bone handles
    // (`_18`, `_100`) that the flags `_8` bit 0 / 1 say are attached.
    void sub_710070F398(ksys::act::Actor* actor);

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
