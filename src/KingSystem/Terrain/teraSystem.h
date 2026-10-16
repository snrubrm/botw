#pragma once

#include <prim/seadSafeString.h>

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadFreeList.h>
#include <container/seadSafeArray.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include <math/seadMatrix.h>
#include <thread/seadAtomic.h>
#include <heap/seadDisposer.h>
#include <thread/seadThread.h>
#include <heap/seadHeap.h>
#include <hostio/seadHostIONode.h>
#include <container/seadOffsetList.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadReadWriteLock.h>
#include <thread/seadThread.h>
#include <common/aglGPUMemAddr.h>
#include <common/aglGPUMemBlock.h>
#include <common/aglTextureSampler.h>
#include "KingSystem/Terrain/teraResourceNode.h"
#include "KingSystem/Utils/Types.h"
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglTextureSampler.h>

namespace agl {
class ShaderProgram;
}

namespace gsys {
class Model;
}

namespace sead {
class FileDevice;
class Heap;
class Thread;
class ExpHeap;
}

namespace ksys::phys {
class Material;
}

namespace ksys::res {
class Handle;
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
class Unk_7101106F44;

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
    // 0x710114d7c8 (placeholder name): whether the calling thread is the one stored in _a40.
    bool sub_710114D7C8() const;
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
    // 0x710114d928 (CSV Terrain::a; placeholder name): whether the image file of `area` for `type` exists
    // on _428.
    bool sub_710114D928(System* system, Unk_7101106F44* area, const ImageTypeMaybe& type);

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
        u8 _720[0x730 - 0x720];
        // Placeholder: one u32 per material (read by sub_710110C1A4).
        struct MaterialValueTable {
            u8 _0[8];
            u32* mValues;
        };
        MaterialValueTable* _730;
        u8 _738[0x748 - 0x738];
        // Placeholder: pairs read by sub_710110C134 / sub_710110B7A4 (-1 when out of range).
        struct IndexPair {
            s32 a;
            s32 b;
        };
        u32 _748;
        IndexPair* _750;
        u8 _758[0x888 - 0x758];
        // Read by index by 0x7101123224.
        sead::Buffer<sead::Vector4f> _888;
        u8 _898[0x3910 - 0x898];
        u32 _3910;
        IndexPair* _3918;
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
    u8 _404[0x418 - 0x404];
    // Placeholder: one render target set per core (0x710114c3c4 .. 0x710114ce48 index this buffer with
    // sead::CoreInfo::getCurrentCoreId()). Color targets 0 / 1 at 0x68 / 0x1e0, depth at 0x358, eight samplers
    // at 0x4d0; bits 0 / 1 of mColorFlags mark bound color targets (0x710114c9d0 invalidates them).
    struct RenderSet {
        agl::RenderBuffer mRenderBuffer;
        agl::RenderTargetColor mColorTargets[2];
        agl::RenderTargetDepth mDepthTarget;
        agl::TextureSampler mSamplers[8];
        u32 mColorFlags;
    };
    // 0x710114c9d0 (placeholder name): invalidates the GPU cache of the bound color targets of this core's set
    // and clears their flags.
    void sub_710114C9D0(agl::DrawContext* context);
    // 0x710114c648 (placeholder name): binds this core's render set and fast-clears its depth to 1.
    void sub_710114C648(agl::DrawContext* context);
    // 0x710114c3c4 (declaration only; placeholder name): binds `texture` (mip, layer) as color target `index`
    // of this core's set. Flag bit 0 first unbinds all targets, bit 1 sets the buffer size from the texture and
    // binds it (or clears it through 0x710114c648 when bit 31 of mColorFlags is set). The agl layer / mip
    // setters it inlines are not in lib/agl yet.
    void sub_710114C3C4(agl::DrawContext* context, const agl::TextureData& texture, u32 mip, u32 layer,
                        s32 index, u32 flags);
    // 0x710114c72c (declaration only; placeholder name): the same for the depth target, with its storage.
    void sub_710114C72C(agl::DrawContext* context, const agl::TextureData& texture,
                        const agl::GPUMemVoidAddr& storage, u32 mip, u32 flags);
    // 0x710114ca64 (declaration only; placeholder name): when bit 0 of `flags` is set, resets sampler `index`
    // of this core's set (filters, wraps, LOD, border colour sead::Color4f::cBlack).
    void sub_710114CA64(s32 index, u32 flags);
    // 0x710114ce48 (declaration only; placeholder name; x0 is not read): sets three uniforms of `program`,
    // activates `sampler` and the shared vertex attribute, then draws.
    static void sub_710114CE48(agl::DrawContext* context, const agl::ShaderProgram* program,
                               const agl::TextureSampler* sampler, const sead::Vector4f* a,
                               const sead::Vector4f* b, const sead::Vector4f* c);
    sead::Buffer<RenderSet> mRenderSets;
    // Checked for image files by sub_710114D928.
    sead::FileDevice* _428;
    u8 _430[0x680 - 0x430];
    sead::Matrix44f mProjectionMatrix;
    sead::Matrix34f mViewMatrix;
    u8 _6f0[0xa40 - 0x6f0];
    // Placeholder type (zeroed by the ctor): sub_710114D7C8 compares its thread at 0x750 with the current thread.
    struct Unk_a40 {
        u8 _0[0x750];
        sead::Thread* mThread;
    };
    Unk_a40* _a40;
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

// Placeholder: a 2D scale and offset (0x7101128b24).
struct Unk_7101128B24Transform {
    f32 scale;
    f32 _4;
    sead::Vector2f offset;
};

// 0x7101128b24 (placeholder name): the box from `min` to `max` (x / z, scaled and offset by `transform`)
// with heights interpolated between `low` and `high` at `t_min` / `t_max`.
void sub_7101128B24(f32 low, f32 high, f32 t_min, f32 t_max, sead::BoundBox3f* box,
                    const sead::Vector2f& min, const sead::Vector2f& max,
                    const Unk_7101128B24Transform& transform);

// 0x7101123224 (placeholder name): entry `index` of Terrain::_370->_4ae0->_888 (the first one when out of
// range).
sead::Vector4f sub_7101123224(s32 index);

class ImageResourceMgr {
    // 0x7101136d7c (declaration only; 2664 B). Returns a status (2: busy, 5: idle; see sub_7101130C80).
    s32 procUnloadResidualRequest();

public:
    // Placeholder: a load / unload request for one image of an area node (defined after System).
    struct Request;
    // Placeholder: a queued load task for one image of an area node (defined after System). Filled by
    // sub_7101132FE0, queued in mList3200 / mKindLists by sub_7101133274; free tasks wait in mList31e8.
    struct LoadTask;

    // 0x7101132270 (declared only; placeholder name).
    bool sub_7101132270(Request* request);
    // 0x7101133724 (placeholder name): sets up the image of `request` from its data (unless already set
    // up), marks it in use and counts it.
    void sub_7101133724(Request* request);

    // 0x7101133af8 (placeholder name): unless the image for `type` is already requested (flag 2), takes a free
    // request from mList31e8, fills it (sub_7101132FE0), marks the image and runs sub_7101133274; returns
    // false when no request is free.
    bool sub_7101133AF8(System* system, Unk_7101106F44* area, const ImageTypeMaybe& type);
    // 0x7101132fe0 (declaration only; placeholder name).
    void sub_7101132FE0(LoadTask* task, System* system, Unk_7101106F44* area,
                        const ImageTypeMaybe& type);
    // 0x710113625c (placeholder name): under the manager lock (0x68), runs sub_7101135F34 and, with flag 2
    // of _6473, finishes the matching request of mLists19c0 (sub_7101136328 first if `a4`).
    bool sub_710113625C(System* owner, Unk_7101106F44* area, const ImageTypeMaybe& type,
                        bool a4, void* a5);
    // 0x7101130c80 (CSV tera::ImageResourceMgr::a; placeholder name): one step of the loader thread with
    // flag 4 of _6473: unloads residual requests, publishes the queue size (waking the thread), and
    // sleeps 33 ms or yields; after 16 busy steps, lowers _3c of the queued kind-1 tasks by 2.
    void sub_7101130C80();
    // 0x7101130df0
    ~ImageResourceMgr();
    // 0x71011339d0 (placeholder name): releases the image of `request` if its flag 8 is set.
    void sub_71011339D0(Request* request);
    // 0x71011311bc (placeholder name): under both locks, runs sub_7101131290 and sub_71011320B4 on every
    // request of _31c0, then publishes the queue size and wakes the loader thread if it is not zero.
    void sub_71011311BC();
    // 0x7101131290 (placeholder name): under both locks, drops the queued load tasks (Unk_7101132878) and
    // unloads every request of mLists1c0 (releasing its image first while its handle is valid).
    void sub_7101131290();
    // 0x71011320b4 (declared only; placeholder name; 444 B).
    void sub_71011320B4(Request* request);
    // 0x710113333c (declared only; placeholder name): looks for a matching queued request.
    s32 sub_710113333C(LoadTask* task, bool a3);
    // 0x7101133274 (placeholder name): queues `request` unless sub_710113333C finds a match (returns its
    // result) and wakes the loader thread if the queue was empty.
    s32 sub_7101133274(LoadTask* task);
    // 0x71011315bc (placeholder name): publishes the queue size and wakes the loader thread if it is not
    // zero.
    void sub_71011315BC();
    // 0x7101131cdc (placeholder name): registers `system` in the slot given by the low three bits of its
    // _1334 (false if taken).
    bool sub_7101131CDC(System* system);
    // 0x71011334b4 (placeholder name): moves the kind-1 requests to the front of the queue.
    void sub_71011334B4();
    // 0x71011355e8 (declared only; placeholder name).
    void sub_71011355E8(LoadTask* task);
    // 0x7101131d68 (placeholder name): moves every request of mList4a18 to mList31e8 (running
    // sub_71011355E8 on kind 0); false if there was none.
    bool sub_7101131D68();
    // 0x7101131fd0 (placeholder name): takes `request` out of mList31c0 / mLists19c0 if it is linked and
    // queues it in mLists1c0.
    void sub_7101131FD0(Request* request);
    // 0x7101131e7c (placeholder name; `this` unused): the request in `lists` for (`a2`, `area`, `type`), or null (also when
    // the area does not have that image).
    Request* sub_7101131E7C(sead::OffsetList<Request>* lists, void* a2, Unk_7101106F44* area,
                            const ImageTypeMaybe& type);
    // 0x7101136328 (declared only; placeholder name).
    // The second argument is a pointer (null-checked and passed on; sub_710113625C forwards its a5).
    void sub_7101136328(Request* request, void* a2);
    // 0x7101135aa0 (placeholder name): if the image for `type` is requested (flag 2), marks it unused and
    // queues a kind-1 (unload) task for it; 0 if no task is free or the image is still referenced.
    s32 sub_7101135AA0(System* system, Unk_7101106F44* area, const ImageTypeMaybe& type);
    // 0x7101135f34 (placeholder name): under the manager lock, clears the image's pending state for `type`
    // (sub_710110DD20(false), flag 2), queues a kind-1 load task for it (sub_710113333C) and hands it to
    // sub_7101136188.
    void sub_7101135F34(System* owner, Unk_7101106F44* area, const ImageTypeMaybe& type);
    // Placeholder: holds only the manager (x0 of 0x7101132878 is loaded as a pointer to it); probably a
    // lambda closure in teraImageResourceMgrStuff 0x710113400c.
    struct Unk_7101132878 {
        // 0x7101132878 (placeholder name): with `load`, drops the queued kind-0 tasks (kind 2 and stale
        // ones directly) after clearing their image's flag 2 and updating their system; with `unload`, the
        // same for kind 1 / 3, setting flag 2 and waiting for the image (sub_71011077C8) instead. Dropped
        // tasks leave `queue` and `kind_lists` and go back to mList31e8.
        void sub_7101132878(sead::OffsetList<LoadTask>* queue, sead::OffsetList<LoadTask>* kind_lists,
                            bool load, bool unload);

        ImageResourceMgr* mgr;
    };

    // Placeholder: like Unk_7101132878, a closure over the manager in 0x710113400c.
    struct Unk_7101136B40 {
        // 0x7101136b40 (placeholder name): if the request's handle is stale, unloads it (sub_7101133588,
        // then sub_71011320B4 with flag 2 of _6473) and returns 8; otherwise gives it a GPU address in
        // mMemBlock6328 (if it has none), sets up its image (sub_7101133724) and returns `result`.
        s32 sub_7101136B40(s32 result, Request* request);

        ImageResourceMgr* mgr;
    };

    // Placeholder: a closure over the manager in 0x710113400c (with a flag it clears).
    struct Unk_7101136C10 {
        // 0x7101136c10 (placeholder name): waits for `handle` in 30 ms steps (sleeping 3.3 ms between
        // tries) while flag 4 of _6473 is set and `task` (if any) is still valid. Clears _8 when the flag
        // goes away; false if it stopped waiting.
        bool sub_7101136C10(res::Handle* handle, LoadTask* task);

        ImageResourceMgr* mgr;
        bool _8;
    };

    // 0x7101136188 (placeholder name): under the manager lock, finds the request in mLists1c0 matching
    // `task`, releases its image when its handle is still valid and runs sub_7101133588 on it. Returns 8
    // if the task's handle is stale, 3 if no request matches, 1 otherwise.
    s32 sub_7101136188(LoadTask* task);
    // 0x7101133588 (declared only; placeholder name).
    void sub_7101133588(Request* request);
    // 0x7101136950 (placeholder name): sub_7101136328 and sub_71011320B4 on every request of mList31c0.
    void sub_7101136950();
    // 0x7101131d64 (placeholder name): branch to sub_7101131D68.
    bool sub_7101131D64();
    // 0x7101130fbc (placeholder name): writes "<dir>/<file name>" for the image of `area` for `type` to
    // `out`; dir is system->_1050, or mBaseDir when the image has flag 0x40 and flag 1 of _6473 is set
    // (then returns true).
    bool sub_7101130FBC(sead::BufferedSafeString* out, System* system, Unk_7101106F44* area,
                        const ImageTypeMaybe& type);
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
    sead::OffsetList<LoadTask> mList31e8;
    // Pending requests (insertion order depends on the request kind); its size is published in _62a0.
    sead::OffsetList<LoadTask> mList3200;
    // Indexed by the low byte of LoadTask::_24.
    sead::OffsetList<LoadTask> mKindLists[0x100];
    sead::OffsetList<LoadTask> mList4a18;
    // Indexed like mKindLists (0x7101131d68).
    sead::OffsetList<LoadTask> mKindLists2[0x100];
    // Destroyed by 0x7101130df0.
    agl::GPUMemBlock<u8> mMemBlock6230;
    u8 _6268[0x626c - 0x6268];
    // Cleared by 0x7101133588.
    u32 _626c;
    s32 _6270;
    u8 _6274[0x6298 - 0x6274];
    sead::Thread* mThread;
    sead::Atomic<s32> _62a0;
    u8 _62a4[0x62a8 - 0x62a4];
    // Storage for the requests' resource handles (0x710113400c allocates, 0x7101133588 frees).
    sead::FreeList mHandleFreeList;
    u8 _62b8[0x62d8 - 0x62b8];
    System* mSystems[8];
    // CPU address of mMemBlock6328's buffer (0x7101136b40 turns request addresses into block offsets).
    u64 _6318;
    u64 _6320;
    agl::GPUMemBlock<u8> mMemBlock6328;
    u8 _6360[0x6470 - 0x6360];
    // Key passed to Unk_71012eb6e8::set / isValid for the tasks and requests (0x7101132fe0, 0x7101136188).
    u16 _6470;
    // Busy step counter of sub_7101130C80.
    u8 _6472;
    // Bit 0: use mBaseDir; bit 3: mMemBlock6328 has a buffer.
    u8 _6473;
};
class ResourceHolder;

// The objects System keeps in its 0x90-byte scene slots (name from the CSV row at 0x7101111650).
// Placeholder (0x7101102b58; callers 0x71011027a8, 0x71011041a4 and four more): a layered texture whose
// frames are slices of one GPU buffer; keeps a sampler bound to the current layer / frame.
struct Unk_7101102B58 {
    // 0x7101102b58 (placeholder name): binds frame `frame` of layer `layer` (animated: bit 3 of _0) or
    // the first texture to the sampler and returns it.
    agl::TextureSampler* sub_7101102B58(u32 frame, u32 layer);

    u8 _0;
    u8 _1[0x8 - 0x1];
    // Frames per layer.
    u8 mNumFrames;
    u8 _9[0x18 - 0x9];
    agl::TextureData* mTextures;
    agl::GPUMemVoidAddr mAddr;
    // Start offset of each layer in mAddr (one more than the layer count).
    u32 mLayerOffsets[(0x2c0 - 0x38) / 4];
    agl::TextureSampler mSampler;
    u16 mFrame;
    u16 mLayer;
};
static_assert(offsetof(Unk_7101102B58, mSampler) == 0x2c0);

class Scene {
    void exportFileBinary();

public:
    // Placeholder type: passed by sub_710110234C to sub_71011021E4 (0x7101100330 reads _0 and _8).
    struct Unk_276c {
        u32 _0;
        u32 _4;
        u32 _8;
        u8 _c[0x14 - 0xc];
    };

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
    // 0x710110234c (placeholder name): sub_71011021E4 with _276c and true.
    void sub_710110234C(System* system);
    // 0x71011021e4 (placeholder name): with `request_all`, sub_7101101578 for all four image types (inlined),
    // then sub_7101100330.
    void sub_71011021E4(System* system, const Unk_276c* arg, bool request_all);
    // 0x7101100330 (declaration only; placeholder name and signature).
    void sub_7101100330(System* system, const Unk_276c* arg, bool a, bool b);
    // Placeholder: an image type with its two request flags (sub_7101101578 builds four).
    struct Unk_7101101DFC {
        ImageTypeMaybe type;
        u32 flag_a;
        u32 flag_b;
    };
    // 0x7101101578 (placeholder name): under _2950, calls sub_7101101DFC for each of the four image types
    // (0, 1, grass, water) whose flags are in `flags` (System::x passes 0xff0000).
    void sub_7101101578(System* system, u32 flags);
    // 0x7101101dfc (declaration only; placeholder name and signature): picks the per-type data
    // (0x15e0 / 0x8c0 / 0xd20 / 0x1180) by entry.type.
    void sub_7101101DFC(System* system, const Unk_7101101DFC& entry, s32 a3, bool a, bool b);
    // 0x71010ffe70 (placeholder name): when (a, b) differ from _2780 / _2784, stores them,
    // rebuilds through _2948 and sets flags 0xff00.
    void sub_71010FFE70(s32 a, s32 b);
    // 0x71011016f4 (placeholder name): forwards the level _2942 to _2948.
    void sub_71011016F4();
    // 0x7101100260 (placeholder name): stores the four values as u16 into the sub-objects of
    // stride 0x460 (+0x1c).
    void sub_7101100260(s32 a, s32 b, s32 c, s32 d);
    // 0x71011020c0 (placeholder name): whether records 5 - 8 have no area below `level` that is not
    // loaded yet (Unk_71010FEDBC::areAreasReadyMaybe).
    bool sub_71011020C0(u32 level) const;

    // [5] is returned by System::sub_710111F4F0, [8] by System::sub_710111F504.
    Unk_71010FEDBC _0[9];
    // Set on every scene by System::sub_7101112C30.
    sead::Vector3f _2760;
    Unk_276c _276c;
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
    // Set (at least 0) by System::sub_71011126C4.
    u8 _2943;
    u8 _2944[0x2946 - 0x2944];
    s8 _2946;
    u8 _2947[0x2948 - 0x2947];
    // Placeholder type: System::sub_710111F644 writes its _afc0.
    struct Unk_2948 {
        // 0x710112727c (declaration only; placeholder name): called by sub_71010FFE70 with the first four
        // sub-objects and the two new values.
        void sub_710112727C(Unk_71010FEDBC* a, Unk_71010FEDBC* b, Unk_71010FEDBC* c, Unk_71010FEDBC* d, s32 x,
                            s32 y);

        // 0x7101128ba0 (declaration only; placeholder name)
        void sub_7101128BA0(s32 level);

        u8 _0[0xafc0];
        void* _afc0;
    };
    Unk_2948* _2948;
    // Locked by sub_7101101578.
    sead::CriticalSection _2950;
    u8 _2950_end[0x2998 - 0x2950 - sizeof(sead::CriticalSection)];
    // Flags: 4 set when the levels change, 8 read by System::sub_710111F618.
    u32 _2998;
};

// Placeholder: the listener System::sub_7101112C94 notifies (slot 0, event 5) before an area node is
// destroyed (passed through from System::x 0x7101112714).
class Unk_7101112C94Listener {
public:
    virtual void m0(Unk_7101106F44* area, s32 event) = 0;
};

class System {
public:
    static System* instance();
    // 0x710111f504: `*_e0 + 0x2300`.
    Unk_71010FEDBC* sub_710111F504();
    // 0x710111f4f0 (placeholder name): `*_e0 + 0x15e0`.
    Unk_71010FEDBC* sub_710111F4F0();
    // 0x710111f644 (placeholder name): stores `value` in _2948->_afc0 of every scene.
    void sub_710111F644(void* value);
    // 0x710111f518 (placeholder name): sub_71011001D4(level, type) on every scene.
    void sub_710111F518(int level, int type);
    // 0x710111f598 (placeholder name): Scene::sub_7101100234(a, b) on every scene.
    void sub_710111F598(bool a, bool b);
    // 0x71011126c4 (placeholder name): stores `value` (at least 0) in _2943 of every scene.
    void sub_71011126C4(s32 value);
    // 0x71011129cc (placeholder name): unless bit 3 of _1338 is set (and not `force`), passes `levels` to
    // every scene; `force` then sets bit 3.
    void sub_71011129CC(const sead::SafeArray<s32, 19>& levels, bool force);
    // 0x7101112a74 (placeholder name): sub_7101101964 on every scene, then clears bit 3 of _1338.
    void sub_7101112A74();
    // 0x7101112af0 / 0x7101112b80 (placeholder names): Scene::sub_71010FFE70 / sub_7101100260 on every scene.
    void sub_7101112AF0(s32 a, s32 b);
    void sub_7101112B80(s32 a, s32 b, s32 c, s32 d);
    // 0x7101112c30 (placeholder name): stores `vec` in every scene (_2760) and sets its flag 4.
    void sub_7101112C30(const sead::Vector3f& vec);
    // 0x7101112c94 (placeholder name): destroys `area` and its subtree (children first): waits until its
    // images are unused, tells `listener`, releases its images from the image resource manager and deletes it.
    void sub_7101112C94(Unk_7101106F44* area, Unk_7101112C94Listener* listener);
    // 0x7101115158 (placeholder name): with a current area node: if `update`, runs Scene::sub_710110234C
    // on every scene under the write lock, sets flag 0x10000 and runs sub_7101115BAC; otherwise only sets
    // flags 0x10002.
    void sub_7101115158(bool update);
    // 0x7101115bac (declaration only; placeholder name).
    void sub_7101115BAC();
    // 0x7101117048 (placeholder name): under the write lock, runs Scene::sub_71011021E4 on scene `index`
    // and then sub_7101115BAC (only with Terrain flags 2 and 4).
    void sub_7101117048(s32 index, const Scene::Unk_276c* arg, bool request_all);
    // 0x71011170f4 (CSV TeraSystem::x; placeholder name): Scene::sub_71011020C0 of scene `index` (true
    // unless Terrain flags 2 and 4 are set).
    bool sub_71011170F4(s32 index, u32 level);
    // 0x710111713c (CSV TeraSystem::x_1; placeholder name): Scene::_276c of scene `index`.
    Scene::Unk_276c* sub_710111713C(s32 index);
    // 0x7101112714 (CSV System::x; placeholder name): under the write lock, resets every scene, removes
    // the image users of the flagged _fa8 nodes, destroys the area tree (telling `listener`) and clears
    // the image change ring.
    void sub_7101112714(Unk_7101112C94Listener* listener);
    // 0x71011188e4 (placeholder name): `_2946 - 1 - _2780` of the first scene, at least 0.
    s32 sub_71011188E4() const;
    void allocateApertureMapsCollectorImage(sead::Heap* heap);
    void loadScene();
    // 0x710111f618 (CSV TeraSystem::x_0): bit 3 of the flags of the `index`th scene (the first if out of range)
    bool sub_710111F618(s32 index);

    // Renamed from the placeholder System (lane1 s101): the owner of the image change ring at
    // 0x1038; ImageResourceMgr::sub_710113625C and the System method 0x7101112c94 take it as the System,
    // and its slot bits (_1334) index ImageResourceMgr::mSystems.
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
    // 0x7101118908 (placeholder name): when the node with key `id` here and in all four children has a B
    // value above epsilon, hands the type-2 image to the image resource manager and rebuilds the node.
    void sub_7101118908(Unk_7101106F44* area, u16 id);
    // 0x7101118c40 (placeholder name): makes sure `area` has a type-2 node for `key` with image size
    // `size`, creating parents' nodes first and splitting the image to the children when they cannot all
    // provide it. True if the node is ready.
    bool sub_7101118C40(sead::Heap* heap, Unk_7101106F44* area, Unk_710110d278::Key* key, u32 size,
                        bool check, f32 value);
    // 0x71011171d8 / 0x710111731c (placeholder names): add / remove a user of the image for `type`; the
    // first user / the last one queues the image.
    void sub_71011171D8(Unk_7101106F44* area, const ImageTypeMaybe& type);
    void sub_710111731C(Unk_7101106F44* area, const ImageTypeMaybe& type);

    // Placeholder: the context loadScene 0x710111e04c and 0x710111e960 pass (as a member-function
    // delegate) to the area tree walk 0x7101107db0.
    struct Unk_710111E168 {
        // 0x710111e168 (placeholder name): flags (0x40) every image of `area` that the node or its
        // children cannot provide or whose file is missing. Always returns 0 (keep walking).
        s32 sub_710111E168(Unk_7101106F44* area);

        System* system;
        bool no_child;
    };

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
    // 0x7101115080 (placeholder name): the area node with id `id`: a binary search of the sorted _1018
    // when it is not empty, else a linear search of _fa8.
    Unk_7101106F44* sub_7101115080(u32 id) const;

    u8 _e8[0xee9 - 0xe8];
    u8 _ee9;
    // Number of entries of _fa8 / _ff8 in use (sub_7101112714).
    u16 _eea;
    u8 _eec[0xef0 - 0xeec];
    // Write-locked by System::x 0x7101112714 and sub_7101115158 around scene updates.
    sead::ReadWriteLock mLock;
    u8 _ef0_end[0xfa8 - 0xef0 - sizeof(sead::ReadWriteLock)];
    // Area nodes and their flags (bit 0: sub_7101112714 removes their image users). 0x7101112714 passes
    // the elements to sub_71011176BC; 0x7101115080 and 0x71012eb70c read their mIndex / mId.
    sead::Buffer<Unk_7101106F44*> _fa8;
    u8 _fb8[0xff8 - 0xfb8];
    sead::Buffer<u8> _ff8;
    u8 _1008[0x1018 - 0x1008];
    // The area nodes sorted by mId.
    sead::Buffer<Unk_7101106F44*> _1018;
    u8 _1028[0x1038 - 0x1028];
    // Image change ring (see pushEntryMaybe).
    s32 mNumEntries;
    Entry* mEntries;
    sead::Atomic<u32> mWriteIndex;
    u32 _104c;
    // The system's image directory (ImageResourceMgr::sub_7101130FBC copies it through a virtual cstr
    // call, so it is a buffered string; its buffer is not known).
    sead::BufferedSafeString _1050;
    u8 _1068[0x1330 - 0x1068];
    // Copied into ImageResourceMgr load tasks (0x7101132fe0, 0x7101135f34).
    u32 _1330;
    // Two bytes copied together into handles (0x71012eb6e8 ldrh/strh; 0x71012eb70c compares with ldrh).
    // The init function 0x71011113d4 clears both with one strh. 0x7101112714 increments 0x1335 alone
    // with ldrb/strb, and 0x7101131cdc reads 0x1334 alone with ldrb, so these are two byte fields.
    struct Id {
        // Low three bits: slot in ImageResourceMgr::mSystems.
        u8 slot;
        u8 generation;
    };
    Id _1334;
    u8 _1336[0x1338 - 0x1336];
    // sub_7101112A74 clears bit 3 (8).
    u32 _1338;
};

// Placeholder: a handle to an area node in System::_fa8 (set by 0x71012eb6e8, checked by 0x71012eb70c; ImageResourceMgr
// keeps them at +0x40 of its requests and +0x20 of other objects).
struct Unk_71012eb6e8 {
    void set(System* system, const Unk_7101106F44* entry, u16 key);
    // Whether the handle still refers to `entry`: same key, its system is systems[slot & 7] with the same
    // id, and the entry at mIndex (or with id mId) is `entry`.
    bool isValid(System* const* systems, const Unk_7101106F44* entry, u16 key) const;

    System* mSystem;
    System::Id mSystemId;
    u16 mKey;
    u32 mId;
    s32 mIndex;
};

struct ImageResourceMgr::Request {
    u8 _0[0x10];
    // Link in mList31c0.
    sead::ListNode mNode10;
    // Checked with isValid against mSystems / _6470 (0x7101131290, 0x7101136188).
    Unk_71012eb6e8 _20;
    void* _38;
    Unk_7101106F44* area;
    ImageTypeMaybe type;
    // Bit 0: queued in mLists1c0; bit 1: in mList31c0; bit 2: the data is ready (passed to the image
    // set-up); bit 3: set up.
    u8 _4c;
    u8 _4d[0x50 - 0x4d];
    // Name hash of the area; the low byte indexes mLists1c0 / mLists19c0.
    u32 _50;
    u8 _54[0x60 - 0x54];
    // Offset of the image data from the request, inside mMemBlock6328 (0x7101136b40).
    u32 _60;
    u32 _64;
    u8 _68[0x6c - 0x68];
    u32 _6c;
    u8 _70[0x88 - 0x70];
    agl::GPUMemVoidAddr* addr;
    // Resource handle taken from ImageResourceMgr::mHandleFreeList (0x710113400c); destroyed and returned
    // there by 0x7101133588.
    res::Handle* _90;
    // GPU address of the image data; `addr` points here once set (0x7101136b40).
    agl::GPUMemVoidAddr _98;
    agl::TextureSampler sampler;
};

// Layout from 0x7101132fe0 (fills it), 0x710113333c (compares _24 / _28 / _30 / _38 and checks _40) and
// 0x7101135f34 (builds one on the stack: 0x88 bytes).
struct ImageResourceMgr::LoadTask {
    // Two list links (only these are cleared in the stack task of 0x7101135f34).
    sead::ListNode mNode0;
    sead::ListNode mNode10;
    // 1: queued at the front of mList3200.
    s32 _20;
    // Name hash of the area; the low byte indexes mKindLists.
    u32 _24;
    System* system;
    Unk_7101106F44* area;
    ImageTypeMaybe type;
    // System::_1330.
    u32 _3c;
    Unk_71012eb6e8 handle;
    u16 _58;
    u8 _5a;
    u32 _5c;
    u32 _60;
    u32 _64;
    u32 _68;
    u32 _6c;
    u32 _70;
    u32 _74;
    u32 _78;
    u32 _7c;
    // The request this task feeds (0x71011355e8).
    Request* _80;
};
class Water {
    void setUpAttributeTable();
};

// 0x710110aa5c (declaration only, 536 bytes): height query used by sub_710110B4A4.
u32 sub_710110AA5C(f32 a, f32 b, f32* out_height, const sead::Vector2f* xz, const Unk_7101108AE8Flags* info_20,
                   const Unk_71010FEDBC* info);
// 0x710110adf8 (declaration only, 752 bytes; placeholder name): sub_710110AA5C that also writes the normal.
u32 sub_710110ADF8(f32 a, f32 b, f32* out_height, sead::Vector3f* out_normal, const sead::Vector2f* xz,
                   const Unk_7101108AE8Flags* info_20, const Unk_71010FEDBC* info);
// 0x710110b0e8 / 0x710110b38c (declaration only; placeholder names): queries like sub_710110AA5C that
// write a 2D value / a u32.
u32 sub_710110B0E8(f32 a, sead::Vector2f* out, const sead::Vector2f* xz, const Unk_7101108AE8Flags* info_20,
                   const Unk_71010FEDBC* info);
u32 sub_710110B38C(u32* out, const sead::Vector2f* xz, const Unk_7101108AE8Flags* info_20, const Unk_71010FEDBC* info);
// 0x710110b5bc / 0x710110b634 (placeholder names): sub_710110B0E8 (with 50) / sub_710110B38C for
// `system`, under the same conditions as sub_710110B4A4.
u32 sub_710110B5BC(sead::Vector2f* out, const sead::Vector2f* xz, System* system);
u32 sub_710110B634(u32* out, const sead::Vector2f* xz, System* system);
// CreateTeraSystem passes the System created at 0x71011113d4 to PlacementMgr.
// 0x710110b4a4: 0 without a scene (System+0x8) or unless Terrain flags 2 and 4 are both set.
u32 sub_710110B4A4(f32* out_height, const sead::Vector2f* xz, System* system);
// Placeholder: the four-byte terrain material record written by 0x710110bd78 (0x710110c02c starts it as
// {0xff, 0, 0, 0}; when _1 has its top bit set, _2 is the material index, otherwise _3).
// 0x710110bd78 stores it as one word.
union MaterialRecordMaybe {
    u32 raw;
    struct {
        u8 _0;
        s8 _1;
        u8 _2;
        u8 _3;
    };
};
// 0x710110bd78 (declaration only, 692 bytes; placeholder name): looks up the material record at `xz`.
u32 sub_710110BD78(MaterialRecordMaybe* out, const sead::Vector2f* xz, System* system, bool flag);
// Full 110C02C writes material and submaterial; independent 1224C1C consumes both.
u32 sub_710110C02C(phys::Material* material, s32* submaterial, const sead::Vector2f* xz,
                    System* system, bool flag);
// Placeholder: the argument of 0x7101108c44 (0x71011094a0 fills it from the area record's _458 and the
// area index).
struct Unk_7101108C44Arg {
    const Unk_710110AC74Table* table;
    s32 index;
    bool _c;
};
// Placeholder: the texel position 0x710110ac74 writes (indices, then the fractions).
struct TexelPosMaybe {
    u32 x;
    u32 y;
    f32 fx;
    f32 fy;
};
// 0x710110ac74 (placeholder name): the texel position of `x` / `y` (wrapped into [0, 1) after the level's
// offset) at mip `level`; with arg->_c set, sub_710110C3E8 instead.
void sub_710110AC74(f32 x, f32 y, const Unk_7101108C44Arg* arg, TexelPosMaybe* out, u32 level);
// 0x710110c3e8 (declaration only, 1352 bytes; placeholder name).
void sub_710110C3E8(const Unk_710110AC74Table* table, TexelPosMaybe* out, s32 index, u32 level);
// 0x7101108c44 (placeholder name): the height (0 - 1, bilinear over 16-bit texels) at `pos` in the area of
// `arg` at mip `level`.
f32 sub_7101108C44(sead::Vector2f pos, const Unk_7101108C44Arg* arg, u32 level);
// Returns query status 0/1/2; the final argument preserves a full integer flag.
u32 sub_71011094A0(f32* out_height, const sead::Vector2f* xz, System* system, s32 index,
                    s32 flag);

// 0x71011091dc (declaration only; placeholder name): height and normal query used by sub_71011096D0.
u32 sub_71011091DC(f32 a, f32 b, f32* out_height, sead::Vector3f* out_normal, const sead::Vector2f* xz,
                   const Unk_7101108AE8Flags* info_20, const Unk_71010FEDBC* info, s32 index,
                   s32 flag);
// 0x71011096d0: like sub_71011094A0, also writes the terrain normal.
u32 sub_71011096D0(f32* out_height, sead::Vector3f* out_normal, const sead::Vector2f* xz,
                   System* system, s32 index, s32 flag);
// 0x710110b52c: like sub_710110B4A4, also writes the terrain normal (sub_710110ADF8).
u32 sub_710110B52C(f32* out_height, sead::Vector3f* out_normal, const sead::Vector2f* xz,
                   System* system);
// 0x710110b6a4 (declaration only): like sub_710110C02C without the flag.
u32 sub_710110B6A4(phys::Material* material, s32* submaterial, const sead::Vector2f* xz,
                   System* system);

// Full 110C1E4 looks up the texture name and writes its indexed 32-bit value.
// GolemRootBase 402194 consumes the unsigned output for model and XLink state.
bool sub_710110C1E4(u32* out, const sead::SafeString& name);
// 0x710110c134 / 0x710110b7a4 (placeholder names): the pair `index` of Unk4ae0::_750 / _3918, or -1.
void sub_710110C134(s32* out_a, s32* out_b, s32 index);
void sub_710110B7A4(s32* out_a, s32* out_b, s32 index);
// 0x710110c1a4 (placeholder name): the u32 value of terrain material `index`; false if out of range.
bool sub_710110C1A4(u32* out, u32 index);

bool checkTeraSystemStatus();

// 0x71011190c8 (declaration only; placeholder name and signature): called by map::PlacementMapMgr::postPlaceActorsRouteStuff with
// the tera system and every route of every map.
void sub_71011190C8(void* tera_system, void* route);

// Placeholder: vtable 0x710250fc48 (hostio::Node::getNodeClassType, D1 0x710114e904, D0 0x710114ea4c),
// ctor 0x710114e714 (sets _8 = 0x1e000481). Held by the renderer that calls sub_710114EA70 (0x71012dafb8).
class Unk_710250fc48 : public sead::hostio::Node {
public:
    virtual ~Unk_710250fc48();
    // 0x710114ea70: bit 0 of _8 is set and Terrain's _a50 does not have bit 3 of its byte at 0x18 set.
    bool sub_710114EA70() const;

    u32 _8;
};

// Placeholder: the objects 0x7101154fc0 and six other unnamed callers pass to sub_7101152DC0.
struct Unk_7101152DC0 {
    u8 _0[0x130];
    f32 _130;
};
// 0x7101152dc0: the larger of obj->_130 and tan(half of an angle in degrees, a TU static).
f32 sub_7101152DC0(const Unk_7101152DC0* obj);

}  // namespace ksys::tera

// Full native 0x7100F3F84C (28 bytes) records terrain bit indices 0..9 from
// callback 0x7101200AC0. Declaration only; terrain storage ownership stays unresolved.
void sub_7100F3F84C(u32 index);
