#pragma once

#include <container/seadTList.h>
#include <math/seadVector.h>
#include <thread/seadAtomic.h>
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

    // 0x7101106fd0: unlinks and destroys all type-2 nodes and type-3 images.
    ~Unk_7101106F44();

    // 0x7101108460 (placeholder name): creates a type-2 node (image size 1, key `key`) and links it.
    Unk_7101108460* sub_7101108460(sead::Heap* heap, Unk_710110d278::Key* key);
    // 0x7101108564 (placeholder name): creates a type-3 image and links it.
    Unk_710250db28* sub_7101108564(sead::Heap* heap, u32 index, u32 size);

    // inline-only in the original; name is a guess. The type-2 node with key id `index` (or null).
    const Unk_7101108460* findNodeMaybe(u16 index) const {
        auto it = mNodes.begin();
        for (; it != mNodes.end(); ++it) {
            if ((*it)->getB()->_8->id == index)
                break;
        }
        return it != mNodes.end() ? *it : nullptr;
    }

    // inline-only in the original; name is a guess. The image for `type`: the same search is inlined
    // into 0x71011080d4, 0x7101108860 and 0x71011339d0 (type 2 dereferences a missing node).
    const Unk_710250dcd8* getImageMaybe(const ImageTypeMaybe& type) const {
        switch (type.type) {
        case 0:
            return &mImage0;
        case 1:
            return &mImage1;
        case 2: {
            return findNodeMaybe(type.index)->getA();
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

    // 0x7101107f40 (placeholder name): numbers this node and its subtree in tree order (`index` counts up)
    // and sets the depths; `max_depth` gets the largest depth.
    void sub_7101107F40(u32* max_depth, s32* index);
    // 0x7101108004 (placeholder name): sub_7101107F40 from the root with both counters reset.
    void sub_7101108004(u32* max_depth, s32* index);
    // 0x7101108174 (placeholder name): whether the nearest node with key `id` (here or in a parent) has a
    // B value above epsilon.
    bool sub_7101108174(u16 id) const;
    // 0x7101108020 (placeholder name): sets up the image for `type` (its m11).
    void sub_7101108020(const ImageTypeMaybe& type, agl::TextureSampler* sampler,
                        const agl::GPUMemVoidAddr& addr, s32 mip_offset, bool flag);

    // 0x7101107318 (placeholder name): sets child `index` (true if the slot was free) or, with null,
    // clears it (true if it was set). A child's _1 holds its slot (4: none).
    bool sub_7101107318(s32 index, Unk_7101106F44* child);
    // 0x7101108298 (placeholder name): gives `node` new A / B objects (heap null, size 1), keeping its key.
    void sub_7101108298(Unk_7101108460* node);
    // 0x71011081d4 (placeholder name): the same with `heap` and `size`; B gets `value` scaled down by the depth.
    void sub_71011081D4(Unk_7101108460* node, sead::Heap* heap, u32 size, f32 value);

    // 0x71011074a0 (placeholder name): marks all images unused; false if one is still referenced.
    bool sub_71011074A0();
    // 0x7101107768 (placeholder name): waits (1 ms steps) until sub_71011074A0 succeeds.
    void sub_7101107768();

    // 0x71011080d4 (placeholder name): releases the buffers of the image for `type` (slot 12).
    void sub_71011080D4(const ImageTypeMaybe& type);

    // Depth in the tree (0 for the root); set by sub_7101107F40.
    u8 mDepth = 0;
    u8 _1 = 4;
    // Index in tree order; set by sub_7101107F40.
    u16 mIndex = 0xffff;
    s32 _4 = -1;
    sead::Vector2f _8{0.0f, 0.0f};
    sead::Vector2f _10{0.0f, 0.0f};
    Unk_7101106F44* mParent = nullptr;
    Unk_7101106F44* mChildren[4]{};
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
    // Placeholder: an image change queued by sub_71011171D8 / sub_710111731C.
    struct Entry {
        Unk_7101106F44* area;
        ImageTypeMaybe type;
    };

    // inline-only in the original; name is a guess. The same ring buffer push is inlined into
    // 0x71011171d8 and 0x710111731c.
    void pushEntryMaybe(Unk_7101106F44* area, const ImageTypeMaybe& type) {
        const u32 index = mWriteIndex.increment();
        mEntries[s32(index % mNumEntries)] = {area, type};
    }

    // 0x7101118b34 (placeholder name): makes sure `area` and its parents have a type-2 node for `key`
    // (creating missing ones); with `check`, an existing node only counts if Terrain flag 0x400 is
    // clear or its image has flag 1, and new nodes get flag 1.
    bool sub_7101118B34(sead::Heap* heap, Unk_7101106F44* area, Unk_710110d278::Key* key, bool check);
    // 0x71011176bc (placeholder name): runs sub_71011171D8 (or sub_710111731C if `flag` is false) on
    // every image of `area`.
    void sub_71011176BC(Unk_7101106F44* area, bool flag);
    // 0x71011171d8 / 0x710111731c (placeholder names): add / remove a user of the image for `type`; the
    // first user / the last one queues the image.
    void sub_71011171D8(Unk_7101106F44* area, const ImageTypeMaybe& type);
    void sub_710111731C(Unk_7101106F44* area, const ImageTypeMaybe& type);

    u8 _0[0x1038];
    u32 mNumEntries;
    Entry* mEntries;
    sead::Atomic<u32> mWriteIndex;
};

}  // namespace ksys::tera
