#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace gsys {
class ModelAnimation;
}

namespace ksys::as {
class ASList;
}

namespace ksys::res {
class Unk_71024f9938;
class Unk_71024f9a70;
}

namespace ksys::mii {

// Actor::mUMiiHylianInfo, allocated with 0x38 bytes. The blink texture initializer
// produces the four FixedSafeString<32> entries at +8 and the animation slot at +0x1c.
class HylianInfo {
public:
    // Actor x_42 passes its AS list and model animation to these native methods.
    void sub_71012A5418(as::ASList* list);
    void sub_71012A56FC(gsys::ModelAnimation* animation);
    void sub_71012A504C(gsys::ModelAnimation* animation);
    void sub_71012A5304(gsys::ModelAnimation* animation, res::Unk_71024f9938* cache,
                       res::Unk_71024f9a70* loader);

    u8 _0[8];
    /* 0x08 */ sead::Buffer<sead::FixedSafeString<32>> mTextureNames;
    /* 0x18 */ s32 _18;
    /* 0x1c */ s32 mMaterialAnmSlot;
    u8 _20[0x38 - 0x20];
};
KSYS_CHECK_SIZE_NX150(HylianInfo, 0x38);
static_assert(offsetof(HylianInfo, mTextureNames) == 0x8);
static_assert(offsetof(HylianInfo, mMaterialAnmSlot) == 0x1c);

}  // namespace ksys::mii
