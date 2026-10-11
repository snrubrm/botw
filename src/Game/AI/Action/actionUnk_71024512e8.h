#pragma once

#include "KingSystem/ActorSystem/actBoneHandle.h"

// Native vtable 0x71024512e8 has D1/D0, m2, m3 and m4. ClothReactionUnit::init
// (0x71006f7928) constructs this at +0x38 in a 0xd8-byte allocation.
class Unk_71024512e8 : public ksys::act::BoneHandleBase {
public:
    Unk_71024512e8();
    ~Unk_71024512e8() override;

    void m2(gsys::Model* model) override;
    bool m3(gsys::Model* model, bool sorted) override;
    const gsys::BoneAccessKey* m4() override { return &_60.getKey(); }

    void setName(const sead::SafeString& name);

    sead::Matrix34f _20{sead::Matrix33f::ident};
    sead::SafeString _50;
    gsys::BoneAccessKeyEx _60;
    bool _98 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71024512e8, 0xa0);
