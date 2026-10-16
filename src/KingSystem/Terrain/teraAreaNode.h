#pragma once

#include <container/seadPtrArray.h>
#include <container/seadTList.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Terrain/teraResourceNode.h"
#include "KingSystem/Terrain/teraSystem.h"
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

    struct InitArg {
        u8 _0[0x8];
        Unk_7101106F44* parent;
        s32 slot;
        u32 id;
        s32 _18;
        u32 depth;
    };
    // 0x71011070e0 (placeholder name): links the node to its parent slot, names it ("%X%X%08X": id, depth,
    // the slot path two bits per level) and initialises its two images.
    bool init(const InitArg& arg);

    // 0x7101106fd0: unlinks and destroys all type-2 nodes and type-3 images.
    ~Unk_7101106F44();

    // 0x7101108460 (placeholder name): creates a type-2 node (image size 1, key `key`) and links it.
    Unk_7101108460* sub_7101108460(sead::Heap* heap, Unk_710110d278::Key* key);
    // 0x7101108334 (placeholder name): as sub_7101108460 with an image size and a B value divided by 2^depth.
    Unk_7101108460* sub_7101108334(sead::Heap* heap, Unk_710110d278::Key* key, u32 size, f32 value);
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

    // inline-only in the original; name is a guess. Repeated four times in 0x71011074a0, which loads each
    // type as one word (taken by value).
    bool tryMarkImageUnusedMaybe(ImageTypeMaybe type) {
        Unk_710250dcd8* image = getImageMaybe(type);
        return image && image->_18.tryMarkUnusedMaybe();
    }

    // 0x71011074a0 (placeholder name): marks all images unused; false if one is still referenced.
    bool sub_71011074A0();
    // 0x710110736c (placeholder name): waits (1 ms steps) until the image for `type` is marked unused.
    void sub_710110736C(const ImageTypeMaybe& type);
    // 0x7101107768 (placeholder name): waits (1 ms steps) until sub_71011074A0 succeeds.
    void sub_7101107768();

    // inline-only in the original; name is a guess. Whether the node has the image for `type` (types 0
    // and 1 always); inlined into 0x7101120374 and 0x7101120598.
    bool hasImageMaybe(const ImageTypeMaybe& type) const {
        switch (type.type) {
        case 0:
        case 1:
            return true;
        case 2:
            return findNodeMaybe(type.index) != nullptr;
        case 3:
            for (const Unk_710250db28* image : mImages) {
                if (image->mIndex == type.index)
                    return image != nullptr;
            }
            return false;
        default:
            return false;
        }
    }

    // 0x710111fafc (placeholder name): false unless this node has the image for `type` (a type-2 node also
    // needs a B value above epsilon). Then with `no_child`, true if no child has it; otherwise true if
    // a child is missing or lacks it.
    bool sub_710111FAFC(const ImageTypeMaybe& type, bool no_child) const;

    // 0x710111fd70 (placeholder name): writes the file name of the image for `type` to `out` (the node name
    // plus ".hght", ".mate", ".<index>.extm", ".grass.extm" or ".water.extm") and returns its length; 0
    // if the node does not have that image.
    s32 sub_710111FD70(sead::BufferedSafeString* out, const ImageTypeMaybe& type) const;

    // 0x7101120598 (placeholder name): climbs from `*node` to the first node that has the image for
    // `type`, keeping `center` / `size` in step; null if there is none.
    static void sub_7101120598(Unk_7101106F44** node, sead::Vector2f* center, f32* size,
                               const ImageTypeMaybe& type);
    // 0x7101120374 (placeholder name): the same for a node whose image is also ready (flag 4).
    static void sub_7101120374(Unk_7101106F44** node, sead::Vector2f* center, f32* size,
                               const ImageTypeMaybe& type);

    // 0x71011206e4 / 0x7101120594 (placeholder names): branch to sub_7101120598 / sub_7101120374 (the
    // callers, e.g. 0x7101108860, use these).
    static void sub_71011206E4(Unk_7101106F44** node, sead::Vector2f* center, f32* size,
                               const ImageTypeMaybe& type);
    static void sub_7101120594(Unk_7101106F44** node, sead::Vector2f* center, f32* size,
                               const ImageTypeMaybe& type);

    // 0x7101108860 (placeholder name): finds the node for `pos` (through `system`), then the nearest node
    // up the tree whose image for `type` is ready and not being unloaded, and takes a reference on that
    // image. Returns 2 if it is the starting node, 1 for a parent, 0 if none.
    static s32 sub_7101108860(Unk_7101106F44** out_area, sead::Vector2f* center, f32* size,
                              const sead::Vector2f& pos, System* system, const ImageTypeMaybe& type,
                              u32 levels);

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
    char mName[11]{};
    u8 mNameLength = 0;
    u32 mNameHash = -1;
};
KSYS_CHECK_SIZE_NX150(Unk_7101106F44, 0xc8);

// Placeholder (owner unknown; functions at 0x7101088b24 / 0x7101088bb4): a list of area images
// (System::Entry) whose users are added or removed together, and how many of them are not
// ready yet.
class Unk_7101088B24 {
public:
    // 0x7101088b24 (placeholder name): adds (`add`) or removes a user of every image through `system`
    // (sub_71011171D8 / sub_710111731C) and remembers which.
    void sub_7101088B24(System* system, bool add);
    // 0x7101088bb4 (placeholder name): moves the images that are now ready (flag 4) behind the first
    // mNumPending entries; true when all are ready.
    bool sub_7101088BB4();

    sead::PtrArray<System::Entry> mEntries;
    u8 _10[0x20 - 0x10];
    u16 mNumPending;
    // 0x7101088b24 stores one bit with bfi.
    u8 _22_0 : 2;
    bool mAdded : 1;
};

}  // namespace ksys::tera
