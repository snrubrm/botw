#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBoneHandle.h"

// Unnamed bone handle (vtable 0x7102451320; constructor 0x7100743334, D1 0x71007433a0, D0 0x71007433e0,
// m2 0x710074344c, m3 0x7100743748) embedded in GiantAttack (+0x90). Searches the bone named _50 in
// the actor's model every frame and applies a rotation to it (m2 is not decompiled yet).
// Placeholder name = vtable address.
class Unk_7102451320 : public ksys::act::BoneHandleBase {
public:
    Unk_7102451320();
    ~Unk_7102451320() override;

    // Declared before m2 so that this TU emits the vtable.
    bool m3(gsys::Model* model, bool sorted) override;
    void m2(gsys::Model* model) override;
    const gsys::BoneAccessKey* m4() override { return &_60.getKey(); }

    // 0x7100743418: sets the bone name (unless the handle is in a list) and resets the key.
    void setName(const sead::SafeString& name);
    // 0x7100743414: empty.
    void sub_7100743414(s32 a1, bool a2, s32 a3);

    /* 0x20 */ bool _20 = false;
    /* 0x24 */ sead::Matrix33f _24 = sead::Matrix33f::ident;
    /* 0x48 */ u8 _48 = 0xff;
    /* 0x50 */ sead::SafeString _50;
    /* 0x60 */ gsys::BoneAccessKeyEx _60;
};
KSYS_CHECK_SIZE_NX150(Unk_7102451320, 0x98);
