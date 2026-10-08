#pragma once

#include <container/seadSafeArray.h>
#include <container/seadObjList.h>
#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

// The look-at camera whose projection fields CameraS1 reads (vtable 0x71024dd110).
// Its constructor places hostio::Node at 0x60, after LookAtCamera.
class Unk_71024dd110 : public sead::LookAtCamera, public sead::hostio::Node {
    SEAD_RTTI_OVERRIDE(Unk_71024dd110, sead::LookAtCamera)
public:
    Unk_71024dd110();
    ~Unk_71024dd110() override;
    bool sub_7100D8AFCC(const sead::Vector3f& pos);
    void sub_7100D8B364(bool active);
    void sub_7100D8B380(s32 id, s32 index);
    void sub_7100D8B3E8(s32 id);

    sead::BitFlag32 _68;
    f32 _6c = 1.0f;
    f32 _70 = 10000.0f;
    f32 _74 = sead::Mathf::pi() / 4;
    sead::Vector2f _78 = sead::Vector2f::zero;

private:
    // Constructor d8acd8 makes four 24-byte entries; d8b380 writes the two words.
    // d8adc0 dispatches each id/index pair to the corresponding CameraMgr selector.
    struct Listener {
        s32 id;
        s32 index;
    };
    sead::FixedObjList<Listener, 4> _80;
};
KSYS_CHECK_SIZE_NX150(Unk_71024dd110, 0x110);

// The two-camera selector embedded at CameraS1 + 0xd0 (constructor 0x710131dfb8).
class Unk_710131dfb8 {
public:
    explicit Unk_710131dfb8(s32 id);
    virtual ~Unk_710131dfb8();
    s32 sub_710131E060() const;
    void sub_710131E068(s32 index, Unk_71024dd110* camera);
    void sub_710131E0D8(s32 index);
    void sub_710131E118(s32 index);
    Unk_71024dd110* getLookAtCamera() const;

private:
    s32 _8;
    s32 _c = -1;
    sead::SafeArray<Unk_71024dd110*, 2> _10{};
};
KSYS_CHECK_SIZE_NX150(Unk_710131dfb8, 0x20);

// Name from the CSV. CameraMgr constructs two instances, with selector ids 0 and 1.
class CameraS1 : public sead::hostio::Node {
public:
    explicit CameraS1(s32 id);
    virtual ~CameraS1();
    void sub_7101265390(s32 index);
    void sub_7101265398(s32 index, Unk_71024dd110* camera);
    void sub_7101265444(s32 index);
    void sub_71012654D8(s32 index);
    void sub_7101265584();
    Unk_71024dd110* getLookAtCamera() const;
    sead::PerspectiveProjection* sub_7101265658();
    const sead::Viewport* getViewport() const;

private:
    friend class CameraMgr;
    s32 _8 = -1;
    sead::PerspectiveProjection _10;
    Unk_710131dfb8 _d0;
};
KSYS_CHECK_SIZE_NX150(CameraS1, 0xf0);

}  // namespace ksys
