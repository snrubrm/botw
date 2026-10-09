#pragma once

#include <basis/seadTypes.h>

namespace gsys {
class ModelAnimation;
}

namespace ksys::as {
class ASList;
}

namespace ksys::mii {

// Placeholder (lane4 s49; Actor::mUMiiHylianInfo): only the integer at +0x18 that Actor::sub_71011CA00C returns is known.
class HylianInfo {
public:
    // Actor x_42 passes its AS list and model animation to these native methods.
    void sub_71012A5418(as::ASList* list);
    void sub_71012A56FC(gsys::ModelAnimation* animation);

    u8 _0[0x18];
    /* 0x18 */ s32 _18;
};

}  // namespace ksys::mii
