#pragma once

#include <container/seadTList.h>
#include <math/seadVector.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Terrain/teraResourceNode.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::tera {

// Placeholder name (ctor 0x7101106f44, created by 0x7101117a08; size 0xc8): a terrain area node with
// a parent at _18 and its images: one of type 0 at _40, one of type 1 at _60, the type-2 nodes in
// mNodes and the type-3 images in mImages (see 0x71011339d0, 0x7101108860).
class Unk_7101106F44 {
public:
    Unk_7101106F44();

    // 0x7101108460 (placeholder name): creates a type-2 node (image size 1, key `key`) and links it.
    Unk_7101108460* sub_7101108460(sead::Heap* heap, Unk_710110d278::Key* key);
    // 0x7101108564 (placeholder name): creates a type-3 image and links it.
    Unk_710250db28* sub_7101108564(sead::Heap* heap, u32 index, u32 size);

    // inline-only in the original; name is a guess. The image for `type`: the same search is inlined
    // into 0x71011080d4, 0x7101108860 and 0x71011339d0 (type 2 dereferences a missing node).
    const Unk_710250dcd8* getImageMaybe(const ImageTypeMaybe& type) const {
        switch (type.type) {
        case 0:
            return &mImage0;
        case 1:
            return &mImage1;
        case 2: {
            const Unk_7101108460* found = nullptr;
            for (const Unk_7101108460* node : mNodes) {
                if (node->getB()->_8->id == type.index) {
                    found = node;
                    break;
                }
            }
            return found->getA();
        }
        case 3: {
            const Unk_710250db28* found = nullptr;
            for (const Unk_710250db28* image : mImages) {
                if (image->mIndex == type.index) {
                    found = image;
                    break;
                }
            }
            return found;
        }
        default:
            return nullptr;
        }
    }

    Unk_710250dcd8* getImageMaybe(const ImageTypeMaybe& type) {
        return const_cast<Unk_710250dcd8*>(static_cast<const Unk_7101106F44*>(this)->getImageMaybe(type));
    }

    // 0x71011074a0 (placeholder name): marks all images unused; false if one is still referenced.
    bool sub_71011074A0();
    // 0x7101107768 (placeholder name): waits (1 ms steps) until sub_71011074A0 succeeds.
    void sub_7101107768();

    // 0x71011080d4 (placeholder name): releases the buffers of the image for `type` (slot 12).
    void sub_71011080D4(const ImageTypeMaybe& type);

    u8 _0 = 0;
    u8 _1 = 4;
    u16 _2 = 0xffff;
    s32 _4 = -1;
    sead::Vector2f _8{0.0f, 0.0f};
    sead::Vector2f _10{0.0f, 0.0f};
    Unk_7101106F44* mParent = nullptr;
    sead::Vector2f _20{0.0f, 0.0f};
    sead::Vector2f _28{0.0f, 0.0f};
    sead::Vector2f _30{0.0f, 0.0f};
    sead::Vector2f _38{0.0f, 0.0f};
    Unk_710250dc50 mImage0;
    Unk_710250dd60 mImage1;
    sead::TList<Unk_7101108460*> mNodes;
    sead::TList<Unk_710250db28*> mImages;
    u8 _b8 = 0;
    u8 _b9[0xc3 - 0xb9];
    u8 _c3 = 0;
    s32 _c4 = -1;
};
KSYS_CHECK_SIZE_NX150(Unk_7101106F44, 0xc8);

// Placeholder: the owner of 0x7101118b34 (its `this` is only passed on to the recursive call; called by
// 0x7101118c40).
class Unk_7101118B34 {
public:
    // 0x7101118b34 (placeholder name): makes sure `area` and its parents have a type-2 node for `key`
    // (creating missing ones); with `check`, an existing node only counts if Terrain flag 0x400 is
    // clear or its image has flag 1, and new nodes get flag 1.
    bool sub_7101118B34(sead::Heap* heap, Unk_7101106F44* area, Unk_710110d278::Key* key, bool check);
};

}  // namespace ksys::tera
