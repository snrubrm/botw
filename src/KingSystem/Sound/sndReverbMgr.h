#pragma once

#include "KingSystem/Utils/Types.h"
#include <container/seadListImpl.h>

namespace sead {
class PrimitiveDrawer;
}

namespace ksys::snd {

// Own constructor 1059828 installs the whole three-slot table 2502bb0.
// Own D1/D0 are 1059cfc/1059d00; whole manager 1059c00 dispatches slot 2
// with a PrimitiveDrawer and two booleans. Manager 1059888 sets node offset 28.
class Unk_7101059828 {
public:
    Unk_7101059828();
    virtual ~Unk_7101059828();
    virtual void draw(sead::PrimitiveDrawer* drawer, bool a, bool b);

    void sub_7101059848(f32 value);
    void sub_7101059850(f32 value);
    void sub_7101059858(f32 value);
    void sub_7101059860(f32 value);
    void sub_7101059868(f32 value);
    void sub_7101059870(f32 value);
    void sub_7101059878(f32 value);
    void sub_7101059880(s32 value);

protected:
    f32 _8 = 0.0f;
    f32 _c = 0.0f;
    f32 _10 = 0.0f;
    f32 _14 = 0.0f;
    f32 _18 = 0.0f;
    f32 _1c = 0.0f;
    f32 _20 = 0.0f;
    s32 _24 = 0;
    sead::ListNode _28;
};
KSYS_CHECK_SIZE_NX150(Unk_7101059828, 0x38);

}  // namespace ksys::snd
