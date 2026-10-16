#pragma once

#include <prim/seadSafeString.h>

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include <math/seadMatrix.h>
#include <thread/seadAtomic.h>
#include <heap/seadDisposer.h>
#include <heap/seadHeap.h>
#include <container/seadOffsetList.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadThread.h>
#include <common/aglGPUMemAddr.h>
#include <common/aglGPUMemBlock.h>
#include <common/aglTextureSampler.h>
#include "KingSystem/Terrain/teraResourceNode.h"
#include "KingSystem/Utils/Types.h"

namespace gsys {
class Model;
}

namespace sead {
class Heap;
class ExpHeap;
}

namespace ksys::phys {
class Material;
}

namespace ksys::tera {

// ResourceHolder 1138A2C supplies a size, name, parent and heap direction.
sead::ExpHeap* sub_7101120314(u32 size, const sead::SafeString& name, sead::Heap* parent,
                            sead::Heap::HeapDirection direction);

// TODO:
class ApertureMaps {
    void updateMap();
};
class ApertureMapsCollector {
    void allocateImage();
    void releaseImage();
};
class System;

class Core {
public:
    class Grass {
    public:
        struct Unk_7101150c24 {
            u32 _0;
            const sead::Vector3f* mPosition;
            f32 _10;
            f32 _14;
            bool _18;
            bool _19;
            bool _1a;
            bool _1b;
            bool _1c;
        };
        static_assert(sizeof(Unk_7101150c24) == 0x20);
        u32 sub_7101150C24(const Unk_7101150c24* arg);
        bool sub_7101150F08(const sead::Vector3f* pos, f32 a, f32 b);
        bool sub_7101150F48(const sead::Vector3f* pos, f32 a, f32 b);
        bool sub_7101150F88(const sead::Vector3f* pos, f32 a, f32 b, bool flag);
        bool sub_7101150FD4(const sead::Vector3f* pos, f32 a, f32 b);
        bool sub_710115101C(const sead::Vector3f* pos, f32 radius);
        // Position and radius from ActorUtil and the independent terrain-cull caller.
        // Declaration only; the implementation remains with the Grass owner.
        bool sub_7101150BA4(const sead::Vector3f* pos, f32 radius);
        // CutGrass and independent Motorcycle/Sandworm callers establish the position and flags.
        // Declaration only; the implementation remains with the Grass owner.
        bool sub_7101151064(const sead::Vector3f* pos, f32 radius, f32 intensity, bool call_effect,
                           bool flag, bool check_ground);
        // 0x71011516d0 (declared only): grass amount at `xz` written to `out`; returns the terrain query result
        // (2 when the grass is disabled, 0 without terrain data).
        u32 sub_71011516D0(f32* out, const sead::Vector2f* xz);

        void sub_7101150990(bool enabled);
        void sub_7101150A7C(const sead::Vector3f* pos, f32 radius, f32 value);
        // 0x7101150be0 (placeholder name; ExpandChemicalField::calc_ with cut grass type 3).
        bool sub_7101150BE0(const sead::Vector3f* pos, f32 radius, f32 value);

        // Shared flags read and written by 0x7101150990 and 0x710114dd4c.
        u8 _0[8];
        u32 mFlags;
    };
    struct Unk_71013010d4 {
        s8 mIndex;
        u8 mFlags;
    };
    static_assert(sizeof(Unk_71013010d4) == 2);
    void sub_71013010D4(const Unk_71013010d4& state, s32 index);

    // Setter 0x7101300b4c and cleanup 0x710130063c prove the position and record stride.
    // The remainder includes an unrecovered uniform block; no record lifetime is implemented.
    struct Unk_7101300b4c {
        u8 _0[8];
        sead::Vector3f mPosition;
        u8 _14[0x1a0 - 0x14];
    };
    static_assert(sizeof(Unk_7101300b4c) == 0x1a0);
    void sub_7101300B4C(u32 index, const sead::Vector3f* position, bool update);
    void sub_7101300F1C(u32 index, const sead::Vector3f* position, bool update);
    void sub_7101300BF0();
    void sub_710130085C();
    void sub_710130089C();
    // 0x7101300aac (declared only; 160 B): sets the visibility mask of the units of the model _f8 (all bits
    // for true).
    void sub_7101300AAC(bool visible);
    void sub_71013008E4(sead::Heap* heap, System* system);
    void sub_71013009C4(sead::Heap* heap);
    bool sub_7101300D50(u32 index, bool a, bool b);

    class Model;
    class Tree;

    // Placeholder (the object at 0x140; ForestRenderer x_2 / x_3 / x_5 reach it through
    // Terrain::sub_710114DE70): flags at +0x8 (bit 2 checked by all three methods), two objects at
    // +0x14cd0 / +0x14cd8.
    class Unk_140 {
    public:
        // 0x71010827dc (declared only): clears flag bit 2 and resets both sub-objects (0x7101084d04).
        void sub_71010827DC();
        // 0x7101082824 (declared only): unless flag bit 2 is set, handles a tree placed at `pos` by name.
        void sub_7101082824(const sead::SafeString& name, const sead::Vector3f& pos);
        // 0x7101083028 (declared only): calls 0x7101084e78 on both sub-objects.
        void sub_7101083028();
        // 0x7101083060 (declared only; 400 B): sets flag bit 1 unless bit 2 is set and builds the tables.
        void sub_7101083060();
    };

    u8 _0[0xf0];
    void* _f0;
    gsys::Model* _f8;
    u8 _100[0x38];
    Grass* _138;
    Unk_140* _140;
    // Getter 0x710114dd84 and setter 0x71013010d4 share this two-byte record buffer.
    sead::Buffer<Unk_71013010d4> mStates;
    sead::Buffer<Unk_7101300b4c> mPositions;
    u8 _168[0x360 - 0x168];
    // Original 0x710130085c and 0x710130089c reset this word with exclusive-loop exchanges.
    sead::Atomic<u32> _360;
    u8 _364[0x18];
    u8 _37c;
};

// 0x71011501c8 (declaration only): Grass cleanup thunk called by world::ChemicalMgr::unload2;
// the body stays with the Grass owner.
void sub_71011501C8(Core::Grass* grass);

// Terrain is the CSV name of the singleton at 0x7102620698 (a sead singleton: createInstance 0x710114961c
// builds the disposer at 0x300). Its ctor 0x71011496a4 also constructs bases at 0x20 (ctor 0x710107e724) and
class ImageResourceMgr;

// 0x58 (vtable group 0x710250faa8); those and the remaining members are not modeled yet.
class Terrain : public sead::IDisposer {
public:
    Terrain();
    ~Terrain() override;

    void setPauseState(bool paused);
    // 0x710114d73c (CSV Terrain::__auto21; placeholder name): Core::sub_710130085C while bits 1 and 2 of _a58 are
    // set.
    void sub_710114D73C();
    // 0x710114deac (CSV Terrain::__auto0; placeholder name): forwards to Core::sub_7101300AAC.
    void sub_710114DEAC(bool visible);
    void sub_710114D8C0(sead::Heap* heap, System* system);
    void sub_710114D8C8(sead::Heap* heap);
    void sub_710114D804(bool enabled, const sead::Matrix44f* projection,
                      const sead::Matrix34f* view);
    s32 sub_710114DD84(s32 index);
    void sub_710114DDF8(u32 index, const sead::Vector3f* position, bool update);
    void sub_710114DE04(u32 index, const sead::Vector3f* position, bool update);
    void sub_710114DDA4(const Core::Unk_71013010d4* states, u32 count);
    bool isGrassEnabled() const { return (_a58 & 2) != 0; }
    Core::Grass* sub_710114DE4C();
    Core::Grass* sub_710114DE58();
    void* sub_710114DE64();
    Core::Unk_140* sub_710114DE70();
    void sub_710114DE7C(bool value);
    bool sub_710114DE9C();
    gsys::Model* sub_710114DEE0();
    bool sub_710114DD40();
    f64 sub_710114D9E8();
    void* sub_710114DED4();
    void* sub_710114D8D0();
    struct Unk_710114D8E4 {
        u8 _0[0x10];
        sead::Vector2f _10;
        f32 _18;
    };
    sead::Vector2f sub_710114D8E4(const Unk_710114D8E4* params);
    f32 sub_710114D8F8(const Unk_710114D8E4* params);

    // Placeholders for the chain Terrain::_370->_4ae0 (0x710114de10 / 0x710114de20 / 0x710114de3c).
    struct MaterialName {
        u16 _0;
        char name[1];
    };
    struct MaterialNameTable {
        u8 _0[8];
        MaterialName** mNames;
    };
    struct Unk4ae0 {
        void* _0;
        u8 _8[0x710 - 0x8];
        s32 _710;
        MaterialNameTable* mMaterialNames;
    };
    struct Unk370 {
        u8 _0[0x4ae0];
        Unk4ae0* _4ae0;
    };
    // 0x710114de10 (CSV Terrain::__auto9) / 0x710114de3c (CSV Terrain::__auto6) / 0x710114de20 (placeholder names).
    void* sub_710114DE10() const;
    s32 sub_710114DE3C() const;
    // The name of terrain material `index` (DragonMoveTo searches it for "雪").
    const char* sub_710114DE20(s32 index) const;

    u8 _20[0x300 - 0x20];
    // The disposer buffer (mSingletonDisposerBuf_) is at 0x300.
    SEAD_SINGLETON_DISPOSER(Terrain)
public:
    u8 _320[0x360 - 0x320];
    Core* _360;
    u8 _368[0x370 - 0x368];
    Unk370* _370;
    ImageResourceMgr* mImageResourceMgr;
    u8 _380[0x3c8 - 0x380];
    f32 _3c8;
    // Passed by sub_710110B4A4 to sub_710110AA5C.
    f32 _3cc;
    // Image size index of the Unk_710250dc50 resources (their m9 0x710110d9b4).
    u32 _3d0;
    u8 _3d4[0x3dc - 0x3d4];
    // Scene::sub_7101101964 gives the first _3dc of 19 entries level 1, the first _3dd level 2 and the
    // first _3de level 3.
    u8 _3dc;
    u8 _3dd;
    u8 _3de;
    u8 _3df[0x400 - 0x3df];
    f32 _400;
    u8 _404[0x680 - 0x404];
    sead::Matrix44f mProjectionMatrix;
    sead::Matrix34f mViewMatrix;
    u8 _6f0[0xa48 - 0x6f0];
    f64 _a48;
    // Placeholder type: ForestRenderer::requestDraw 0x7100f03964 draws nothing when bit 5 of its byte at
    // 0x18 is set.
    struct Unk_a50 {
        u8 _0[0x18];
        u8 _18;
    };
    Unk_a50* _a50;
    u32 _a58;
};
KSYS_CHECK_SIZE_NX150(Terrain, 0xa60);
class Unk_7101106F44;
class Unk_7101118B34;

class ImageResourceMgr {
    void procUnloadResidualRequest();

public:
    // Placeholder: a load / unload request for one image of an area node.
    struct Request {
        u8 _0[0x10];
        // Link in mList31c0.
        sead::ListNode mNode10;
        // 1: queued at the front of mList3200.
        s32 _20;
        // Low byte: index of the list in mKindLists.
        u32 _24;
        u8 _28[0x40 - 0x28];
        Unk_7101106F44* area;
        ImageTypeMaybe type;
        // Bit 0: queued in mLists1c0; bit 1: in mList31c0; bit 2: the data is ready (passed to the image
        // set-up); bit 3: set up.
        u8 _4c;
        u8 _4d[0x50 - 0x4d];
        // Index in mLists1c0 / mLists19c0.
        u8 _50;
        u8 _51[0x64 - 0x51];
        u32 _64;
        u8 _68[0x6c - 0x68];
        u32 _6c;
        u8 _70[0x88 - 0x70];
        agl::GPUMemVoidAddr* addr;
        u8 _90[0xb0 - 0x90];
        agl::TextureSampler sampler;
    };

    // 0x7101132270 (declared only; placeholder name).
    bool sub_7101132270(Request* request);
    // 0x7101133724 (placeholder name): sets up the image of `request` from its data (unless already set
    // up), marks it in use and counts it.
    void sub_7101133724(Request* request);

    // 0x710113625c (declared only; placeholder name): called under the manager lock (0x68).
    bool sub_710113625C(Unk_7101118B34* owner, Unk_7101106F44* area, const ImageTypeMaybe& type,
                        bool a4, void* a5);
    // 0x7101130df0
    ~ImageResourceMgr();
    // 0x71011339d0 (placeholder name): releases the image of `request` if its flag 8 is set.
    void sub_71011339D0(Request* request);
    // 0x71011311bc (placeholder name): under both locks, runs sub_7101131290 and sub_71011320B4 on every
    // request of _31c0, then publishes the queue size and wakes the loader thread if it is not zero.
    void sub_71011311BC();
    // 0x7101131290 (declared only; placeholder name).
    void sub_7101131290();
    // 0x71011320b4 (declared only; placeholder name; 444 B).
    void sub_71011320B4(Request* request);
    // 0x710113333c (declared only; placeholder name): looks for a matching queued request.
    s32 sub_710113333C(Request* request, bool a3);
    // 0x7101133274 (placeholder name): queues `request` unless sub_710113333C finds a match (returns its
    // result) and wakes the loader thread if the queue was empty.
    s32 sub_7101133274(Request* request);
    // 0x71011315bc (placeholder name): publishes the queue size and wakes the loader thread if it is not
    // zero.
    void sub_71011315BC();
    // 0x7101131cdc (placeholder name): registers `system` in the slot given by the low three bits of its
    // _1334 (false if taken).
    bool sub_7101131CDC(System* system);
    // 0x71011334b4 (placeholder name): moves the kind-1 requests to the front of the queue.
    void sub_71011334B4();
    // 0x71011355e8 (declared only; placeholder name).
    void sub_71011355E8(Request* request);
    // 0x7101131d68 (placeholder name): moves every request of mList4a18 to mList31e8 (running
    // sub_71011355E8 on kind 0); false if there was none.
    bool sub_7101131D68();
    // 0x7101131fd0 (placeholder name): takes `request` out of mList31c0 / mLists19c0 if it is linked and
    // queues it in mLists1c0.
    void sub_7101131FD0(Request* request);
    // 0x7101131d64 (placeholder name): branch to sub_7101131D68.
    bool sub_7101131D64();
    // 0x7101130e44 (placeholder name): writes "<dir>/<name>" to `out` (with mBaseDir as the directory if
    // `use_base_dir` and flag 1 of _6473); true if mBaseDir was used.
    bool sub_7101130E44(sead::BufferedSafeString* out, const sead::SafeString& dir,
                        const sead::SafeString& name, bool use_base_dir);

    u8 _0[0x28];
    sead::CriticalSection mCS28;
    sead::CriticalSection mCS68;
    // Directory used instead of the given one when flag 1 of _6473 is set (0x7101130e44); the real
    // string type (a FixedSafeString?) is not known.
    sead::SafeString mBaseDir;
    u8 _b8[0x1c0 - 0xb8];
    // Indexed by Request::_50.
    sead::OffsetList<Request> mLists1c0[0x100];
    sead::OffsetList<Request> mLists19c0[0x100];
    sead::OffsetList<Request> mList31c0;
    u8 _31d8[0x31e8 - 0x31d8];
    sead::OffsetList<Request> mList31e8;
    // Pending requests (insertion order depends on the request kind); its size is published in _62a0.
    sead::OffsetList<Request> mList3200;
    // Indexed by the low byte of Request::_24.
    sead::OffsetList<Request> mKindLists[0x100];
    sead::OffsetList<Request> mList4a18;
    // Indexed like mKindLists (0x7101131d68).
    sead::OffsetList<Request> mKindLists2[0x100];
    // Destroyed by 0x7101130df0.
    agl::GPUMemBlock<u8> mMemBlock6230;
    u8 _6268[0x6270 - 0x6268];
    s32 _6270;
    u8 _6274[0x6298 - 0x6274];
    sead::Thread* mThread;
    sead::Atomic<s32> _62a0;
    u8 _62a4[0x62d8 - 0x62a4];
    System* mSystems[8];
    u64 _6318;
    u64 _6320;
    agl::GPUMemBlock<u8> mMemBlock6328;
    u8 _6360[0x6473 - 0x6360];
    // Bit 0: use mBaseDir; bit 3: mMemBlock6328 has a buffer.
    u8 _6473;
};
class ResourceHolder;
// Placeholder: the object System::sub_710111F504 returns (`*_e0 + 0x2300`); sub_710110AA5C reads it and its +0x20.
// The nine 0x460-byte objects at the start of a Scene (Scene::sub_7101100260 writes _1c of eight of them).
struct Unk_710111F504 {
    u8 _0[0x1c];
    u16 _1c;
    u8 _1e[0x20 - 0x1e];
    u8 _20;
    u8 _21[0x28 - 0x21];
    u8 _28;
    u8 _29;
    u8 _2a[0x460 - 0x2a];
};
KSYS_CHECK_SIZE_NX150(Unk_710111F504, 0x460);

// The objects System keeps in its 0x90-byte scene slots (name from the CSV row at 0x7101111650).
class Scene {
    void exportFileBinary();

public:
    // 0x71011001d4 (declaration only; placeholder name): stores the two levels at 0x2940 / 0x2941
    // (clamped) and sets flag 4.
    void sub_71011001D4(int level, int type);
    // 0x7101100234 (placeholder name): sets flag 8 from `a` and flag 0x10 from `b`.
    void sub_7101100234(bool a, bool b);
    // 0x7101101914 (placeholder name): copies the levels that are not -1 into _278c; flag 4 if one changed.
    void sub_7101101914(const sead::SafeArray<s32, 19>& levels);
    // 0x7101101a10 / 0x7101101a7c / 0x7101101aa0 (placeholder names): store pointers into the buffers at
    // 0x2910 / 0x2920 / 0x2930.
    void sub_7101101A10(void* a, void* b, void* c, void* d, void* e);
    void sub_7101101A7C(void* a, void* b);
    void sub_7101101AA0(void* a, void* b, void* c);
    // 0x7101101964 (declaration only; placeholder name): refreshes the 19 words at 0x278c from the Terrain
    // and sets flag 4 if one changed.
    void sub_7101101964();
    // 0x71010ffe70 (placeholder name): when (a, b) differ from _2780 / _2784, stores them,
    // rebuilds through _2948 and sets flags 0xff00.
    void sub_71010FFE70(s32 a, s32 b);
    // 0x71011016f4 (placeholder name): forwards the level _2942 to _2948.
    void sub_71011016F4();
    // 0x7101100260 (placeholder name): stores the four values as u16 into the sub-objects of
    // stride 0x460 (+0x1c).
    void sub_7101100260(s32 a, s32 b, s32 c, s32 d);

    // [5] is returned by System::sub_710111F4F0, [8] by System::sub_710111F504.
    Unk_710111F504 _0[9];
    // Set on every scene by System::sub_7101112C30.
    sead::Vector3f _2760;
    u8 _276c[0x2780 - 0x276c];
    s32 _2780;
    s32 _2784;
    u8 _2788[0x278c - 0x2788];
    s32 _278c[19];
    u8 _27d8[0x2910 - 0x27d8];
    sead::Buffer<void*> _2910;
    // Element types unknown (pointer-sized).
    sead::Buffer<void*> _2920;
    sead::Buffer<void*> _2930;
    u8 _2940;
    u8 _2941;
    s8 _2942;
    u8 _2943[0x2946 - 0x2943];
    s8 _2946;
    u8 _2947[0x2948 - 0x2947];
    // Placeholder type: System::sub_710111F644 writes its _afc0.
    struct Unk_2948 {
        // 0x710112727c (declaration only; placeholder name): called by sub_71010FFE70 with the first four
        // sub-objects and the two new values.
        void sub_710112727C(Unk_710111F504* a, Unk_710111F504* b, Unk_710111F504* c, Unk_710111F504* d, s32 x,
                            s32 y);

        // 0x7101128ba0 (declaration only; placeholder name)
        void sub_7101128BA0(s32 level);

        u8 _0[0xafc0];
        void* _afc0;
    };
    Unk_2948* _2948;
    u8 _2950[0x2998 - 0x2950];
    // Flags: 4 set when the levels change, 8 read by System::sub_710111F618.
    u32 _2998;
};

class System {
public:
    static System* instance();
    // 0x710111f504: `*_e0 + 0x2300`.
    Unk_710111F504* sub_710111F504();
    // 0x710111f4f0 (placeholder name): `*_e0 + 0x15e0`.
    void* sub_710111F4F0();
    // 0x710111f644 (placeholder name): stores `value` in _2948->_afc0 of every scene.
    void sub_710111F644(void* value);
    // 0x710111f518 (placeholder name): sub_71011001D4(level, type) on every scene.
    void sub_710111F518(int level, int type);
    // 0x7101112a74 (placeholder name): sub_7101101964 on every scene, then clears bit 3 of _1338.
    void sub_7101112A74();
    // 0x7101112af0 / 0x7101112b80 (placeholder names): Scene::sub_71010FFE70 / sub_7101100260 on every scene.
    void sub_7101112AF0(s32 a, s32 b);
    void sub_7101112B80(s32 a, s32 b, s32 c, s32 d);
    // 0x7101112c30 (placeholder name): stores `vec` in every scene (_2760) and sets its flag 4.
    void sub_7101112C30(const sead::Vector3f& vec);
    // 0x71011188e4 (placeholder name): `_2946 - 1 - _2780` of the first scene, at least 0.
    s32 sub_71011188E4() const;
    void allocateApertureMapsCollectorImage(sead::Heap* heap);
    void loadScene();
    // 0x710111f618 (CSV TeraSystem::x_0): bit 3 of the flags of the `index`th scene (the first if out of range)
    bool sub_710111F618(s32 index);

    // 0x90-byte entries; only the scene pointer at +0 is known.
    struct SceneSlot {
        Scene* scene;
        u8 _8[0x90 - 0x8];
    };

    u8 _0[0x8];
    // 0x7101115218 (placeholder name): from the current area node, climbs to the one containing `pos` and
    // descends at most `levels` (plus the levels climbed) towards it; returns that node and writes its
    // centre and size.
    Unk_7101106F44* sub_7101115218(sead::Vector2f* out_center, f32* out_size, const sead::Vector2f& pos,
                                   u32 levels);

    // Current area node (quadtree, see teraAreaNode.h). Checked by sub_710110B4A4 (no query without it).
    Unk_7101106F44* _8;
    u8 _10[0x1c - 0x10];
    // Centre and size of _8.
    sead::Vector2f _1c;
    f32 _24;
    u8 _28[0xd8 - 0x28];
    sead::Buffer<SceneSlot> mScenes;
    u8 _e8[0x1334 - 0xe8];
    // Low three bits: slot in ImageResourceMgr::mSystems.
    u8 _1334;
    u8 _1335[0x1338 - 0x1335];
    // sub_7101112A74 clears bit 3 (8).
    u32 _1338;
};
class Water {
    void setUpAttributeTable();
};

// 0x710110aa5c (declaration only, 536 bytes): height query used by sub_710110B4A4.
u32 sub_710110AA5C(f32 a, f32 b, f32* out_height, const sead::Vector2f* xz, const u8* info_20,
                   const Unk_710111F504* info);
// CreateTeraSystem passes the System created at 0x71011113d4 to PlacementMgr.
// 0x710110b4a4: 0 without a scene (System+0x8) or unless Terrain flags 2 and 4 are both set.
u32 sub_710110B4A4(f32* out_height, const sead::Vector2f* xz, System* system);
// Full 110C02C writes material and submaterial; independent 1224C1C consumes both.
u32 sub_710110C02C(phys::Material* material, s32* submaterial, const sead::Vector2f* xz,
                    System* system, bool flag);
// Returns query status 0/1/2; the final argument preserves a full integer flag.
u32 sub_71011094A0(f32* out_height, const sead::Vector2f* xz, System* system, s32 index,
                    s32 flag);

// 0x71011096d0 (declaration only): like sub_71011094A0, also writes the terrain normal.
u32 sub_71011096D0(f32* out_height, sead::Vector3f* out_normal, const sead::Vector2f* xz,
                   System* system, s32 index, s32 flag);
// 0x710110b52c (declaration only): like sub_710110B4A4, also writes the terrain normal.
u32 sub_710110B52C(f32* out_height, sead::Vector3f* out_normal, const sead::Vector2f* xz,
                   System* system);
// 0x710110b6a4 (declaration only): like sub_710110C02C without the flag.
u32 sub_710110B6A4(phys::Material* material, s32* submaterial, const sead::Vector2f* xz,
                   System* system);

// Full 110C1E4 looks up the texture name and writes its indexed 32-bit value.
// GolemRootBase 402194 consumes the unsigned output for model and XLink state.
bool sub_710110C1E4(u32* out, const sead::SafeString& name);

bool checkTeraSystemStatus();

// 0x71011190c8 (declaration only; placeholder name and signature): called by map::PlacementMapMgr::postPlaceActorsRouteStuff with
// the tera system and every route of every map.
void sub_71011190C8(void* tera_system, void* route);

}  // namespace ksys::tera

// Full native 0x7100F3F84C (28 bytes) records terrain bit indices 0..9 from
// callback 0x7101200AC0. Declaration only; terrain storage ownership stays unresolved.
void sub_7100F3F84C(u32 index);
