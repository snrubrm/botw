#pragma once

#include <basis/seadTypes.h>
#include <filedevice/seadFileDevice.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/gameUnk_71024739f8.h"

namespace sead {
class Heap;
class XmlDocument;
class XmlElement;
}  // namespace sead

namespace uking {

// Placeholder name (lane4 s46): the object constructed by 0x71008be174, which holds 16
// sead::Delegate1<this, bool*> members (0x20 bytes each, the targets are the methods below). Each method
// stores one bit of the hold mask of the player's controller (MaskController controller 1) to `*out`;
// the object itself is not used. Only the methods are declared; the data members are not modelled yet.
class Unk_71008be174 {
public:
    // 0x71008be304: hold mask bit 0.
    void sub_71008BE304(bool* out);
    // 0x71008be340: hold mask bit 1.
    void sub_71008BE340(bool* out);
    // 0x71008be37c: hold mask bit 2.
    void sub_71008BE37C(bool* out);
    // 0x71008be3b8: hold mask bit 3.
    void sub_71008BE3B8(bool* out);
    // 0x71008be3f4: hold mask bit 4.
    void sub_71008BE3F4(bool* out);
    // 0x71008be430: hold mask bit 5.
    void sub_71008BE430(bool* out);
    // 0x71008be46c: hold mask bit 6.
    void sub_71008BE46C(bool* out);
    // 0x71008be4a8: hold mask bit 7.
    void sub_71008BE4A8(bool* out);
    // 0x71008be4e4: hold mask bit 8.
    void sub_71008BE4E4(bool* out);
    // 0x71008be520: hold mask bit 9.
    void sub_71008BE520(bool* out);
    // 0x71008be55c: hold mask bit 10.
    void sub_71008BE55C(bool* out);
    // 0x71008be598: hold mask bit 11.
    void sub_71008BE598(bool* out);
    // 0x71008be5d4: hold mask bit 12.
    void sub_71008BE5D4(bool* out);
    // 0x71008be610: hold mask bit 13.
    void sub_71008BE610(bool* out);
    // 0x71008be64c: hold mask bit 14.
    void sub_71008BE64C(bool* out);
    // 0x71008be688: hold mask bit 15.
    void sub_71008BE688(bool* out);
    // 0x71008be6c4: hold mask bit 16.
    void sub_71008BE6C4(bool* out);
    // 0x71008be700: hold mask bit 17.
    void sub_71008BE700(bool* out);
    // 0x71008be73c: hold mask bit 18.
    void sub_71008BE73C(bool* out);
    // 0x71008be778: hold mask bit 19.
    void sub_71008BE778(bool* out);
};

}  // namespace uking

// Secondary base of Unk_710246d140 at +0x480: only a virtual destructor (its vtable in the
// 0x710246d140 group holds the D1 / D0 thunks 0x71008bdfb4 / 0x71008be0c0). Placeholder name.
class Unk_710246d140Base {
public:
    virtual ~Unk_710246d140Base() = default;
};

// vtable 0x710246d140 (ctor 0x71008bddd8, D1 0x71008bde54, D0 0x71008be038): an input source that
// records the controller input into an XML document (sub_71008BDED4 writes it to
// "replay/win/replay.xml").
class Unk_710246d140 : public uking::Unk_71024739f8, public Unk_710246d140Base {
    SEAD_RTTI_OVERRIDE(Unk_710246d140, uking::Unk_71024739f8)
public:
    Unk_710246d140();
    ~Unk_710246d140() override;
    // 0x71008be300
    void update() override { Unk_71024739f8::update(); }

    // 0x71008bded4 (declared only): saves mDocument to "replay/win/replay.xml" (needs the write
    // position of a sead::RamWriteStream, private in lib/sead).
    void sub_71008BDED4();

    /* 0x488 */ sead::Heap* mHeap = nullptr;
    /* 0x490 */ sead::FileHandle mFileHandle;
    /* 0x4d0 */ sead::XmlDocument* mDocument = nullptr;
    /* 0x4d8 */ sead::XmlElement* mRoot = nullptr;
    /* 0x4e0 */ u32 mFlags = 0;  // bit 1: save the document on destruction
    /* 0x4e4 */ u8 _4e4 = 0;
    /* 0x4e8 */ u32 _4e8 = 0;
};

// vtable 0x710246d258 (ctor 0x71008bed58, D1 0x71008bedc4, D0 0x71008bee34): the sibling input source of
// Unk_710246d140 with a file handle and an owned document (the replay player, by its neighbours).
class Unk_710246d258 : public uking::Unk_71024739f8 {
    SEAD_RTTI_OVERRIDE(Unk_710246d258, uking::Unk_71024739f8)
public:
    Unk_710246d258();
    ~Unk_710246d258() override;
    // 0x71008beeb4
    void update() override {
        mOwnsDocument = false;
        Unk_71024739f8::update();
    }

    /* 0x480 */ sead::FileHandle mFileHandle;
    // Deleted through its virtual destructor when mOwnsDocument is set; type taken from Unk_710246d140.
    /* 0x4c0 */ sead::XmlDocument* mDocument = nullptr;
    /* 0x4c8 */ u64 _4c8 = 0;
    /* 0x4d0 */ u32 _4d0 = 0;
    u8 _4d4[0x4e4 - 0x4d4];
    /* 0x4e4 */ u8 _4e4 = 0;
    /* 0x4e5 */ bool mOwnsDocument = false;
};
