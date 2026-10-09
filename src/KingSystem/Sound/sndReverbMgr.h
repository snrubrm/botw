#pragma once

#include "KingSystem/Utils/Types.h"
#include <container/seadListImpl.h>
#include <container/seadOffsetList.h>
#include <thread/seadCriticalSection.h>

namespace sead {
class PrimitiveDrawer;
class DrawContext;
class Camera;
class Projection;
class Viewport;
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

// Whole FxMgr::init 10504fc allocates 98 bytes and constructs this manager at +50.
// Own complete table 2502bd8 has D1/D0; ctor and cleanup establish list and lock.
class Unk_7101059888 {
public:
    Unk_7101059888();
    virtual ~Unk_7101059888();
    void sub_710105999C(sead::Heap* heap);
    void sub_7101059B08();
    // Whole SoundMgr draw caller 11FC428 passes the same four graphics arguments.
    void sub_7101059C00(sead::DrawContext* context, const sead::Camera& camera,
                      const sead::Projection& projection, const sead::Viewport& viewport);
    void sub_7101059B14(Unk_7101059828* controller);
    void sub_7101059B8C(Unk_7101059828* controller);

private:
    sead::OffsetList<Unk_7101059828> _8;
    sead::CriticalSection _20;
    f32 _60[5]{};
    u32 _74 = 0;
    f32 _78[5]{};
    f32 _8c = 100.0f;
    f32 _90 = 600.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_7101059888, 0x98);

}  // namespace ksys::snd
