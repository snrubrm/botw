#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <math/seadBoundBox.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/Graphics/gfxLocationalLightMgr.h"
#include <gfx/seadCamera.h>
#include <gfx/seadColor.h>
#include <gfx/seadProjection.h>
#include <gfx/seadViewport.h>
#include <hostio/seadHostIONode.h>
#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include <thread/seadCriticalSection.h>
#include <gsys/gsysModelScene.h>
#include <gsys/gsysModelScenePassCallback.h>
#include <gsys/gsysModelRenderQueue.h>
#include <gsys/gsysModelRenderContext.h>
#include <gsys/gsysModelRenderUnitNodeArray.h>
#include <gsys/gsysModelUnit.h>
#include <gsys/gsysModelSceneContext.h>
#include <gsys/gsysModelRenderCache.h>
#include <gsys/gsysModelResource.h>
#include <common/aglDrawContext.h>
#include <common/aglTextureSampler.h>
#include <common/aglUniformBlock.h>
#include <cull/aglOcclusionQueryDrawer.h>
#include <cull/aglViewFrustumCulling.h>
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglVertexBuffer.h>
#include <common/aglIndexStream.h>
#include <common/aglVertexAttribute.h>
#include <common/aglTextureData.h>
#include <utility/aglDebugTexturePage.h>
#include <utility/aglParameter.h>
#include <utility/aglParameterIO.h>
#include <utility/aglParameterObj.h>
#include <common/aglGPUMemAddr.h>
#include <common/aglGPUMemBlock.h>
#include <utility/aglAtomicPtrArray.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resTextureHandleList.h"
#include <prim/seadSafeString.h>
#include <prim/seadScopedLock.h>
#include "Game/gameAglEnvCubeMapMgr.h"

namespace sead {
class Heap;
}

namespace nn::gfx {
class ResTexture;
}
namespace gsys {
class ModelNW;
class ModelScene;
}
namespace agl::lyr {
class Layer;
}
namespace ksys::gfx {
struct ModelRenderDataMaybe;
}

namespace ksys::act {
class PlayerLink;
}
namespace ksys::world {
class EnvMgr;
}

// Settings registered at Graphics + 0xae0, embedded in RuneMgr + 0x250 and GameSceneSubsys5 + 0x58.
// Constructor 0x7100f35df8; the bounds and result fields are copied by Graphics::sub_7100F2E2A4.
class Unk_7100f35df8 {
public:
    // Copied as one 16-byte block by Graphics::sub_7100F2E2A4 (placeholder name).
    struct Unk_20 {
        sead::Vector3f _0 = sead::Vector3f::zero;
        f32 _c = 0;
    };

    Unk_7100f35df8();

    bool _0 = false;
    u64 _8 = 0;
    sead::BoundBox2f _10;
    Unk_20 _20;
    f32 _30 = 0;
    f32 _34 = 0;
    f32 _38 = 0;
    f32 _3c = 0.36f;
    f32 _40 = 0.48f;
    s32 _44 = 0;
    s32 _48 = 0;
    f32 _4c = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7100f35df8, 0x50);

// Declaration only: Graphics initializer F2C140 allocates 0x4a8 bytes, constructs this
// object at 12A20E0 and stores it at Graphics + 0xab8. Its source name is unknown.
class Unk_71012a20e0 : public sead::hostio::Node {
public:
    // 12A2268 stores the low byte of mode at 0x1b0; the full word is tested for mode 2.
    // EnvMgr reset 10D326C, doCalc 10D62C0 and wrapper 10DB0B0 call this same receiver.
    void sub_71012A2268(u32 mode);
    // 0x71012a2768 (unnamed in the CSV): when this object is enabled (bit 0 of _498) and the cube
    // map manager has at least two reserved units, sets up unit `_1b3 & 1` at _198, pushes its update
    // request, advances _190 down towards _194 and toggles bit 24 of _1b0. True when the unit was set
    // up.
    bool sub_71012A2768();

private:
    // Complete constructor 12A20E0 and cleanup 12A22B0 establish the Node prefix.
    // 12A2768 consumes these two floats and the low mode byte independently.
    // Texture objects and the rest of the lifetime remain undeclared; do not allocate this prefix.
    u8 _8[0x10 - 0x8];
    agl::env::CubeMapMgr* mCubeMapMgr;
    u8 _18[0x190 - 0x18];
    f32 _190;
    f32 _194;
    sead::Vector3f _198;
    u8 _1a4[0x1b0 - 0x1a4];
    // The mode byte (12A2268) and the unit index byte share this word; 12A2768 toggles bit 24.
    union {
        u32 _1b0;
        struct {
            u8 _1b0b;
            u8 _1b1;
            u8 _1b2;
            u8 _1b3;
        };
    };
    u8 _1b4[0x498 - 0x1b4];
    // Bit 0 is the enabled flag; 0x71012a2768 tests only its low byte, Graphics 0x7100f2ac88
    // sets bit 2 with a word read-modify-write.
    u32 _498;
};

// Declaration only: F2C140 constructs a 0x268-byte object at 129175C and stores it at B38.
// 12920C4 selects a signed buffer index and sets byte 1FF4 in its record.
class Unk_710129175c : public sead::hostio::Node {
public:
    // Placeholder: the 0x2088-byte records of the buffer at 0x10 (only the fields read through
    // sub_710129276C and Graphics::sub_7100F2E2A4 are modelled).
    // sub_710129276C copies the fields at 0x1f98..0x1fdc into Result; sub_71012920C4 sets _1ff4.
    struct Record {
        u8 _0[0x12c8];
        agl::GPUMemAddrBase _12c8;
        u8 _12e0[0x13f0 - 0x12e0];
        agl::GPUMemAddrBase _13f0;
        u8 _1408[0x1518 - 0x1408];
        agl::GPUMemAddrBase _1518;
        u8 _1530[0x1b60 - 0x1530];
        agl::GPUMemAddrBase _1b60;
        u8 _1b78[0x1c88 - 0x1b78];
        agl::GPUMemAddrBase _1c88;
        u8 _1ca0[0x1db0 - 0x1ca0];
        agl::GPUMemAddrBase _1db0;
        u8 _1dc8[0x1f91 - 0x1dc8];
        ~Record();
        u8 _1f91;  // Graphics::sub_7100F2E2A4 tests bit 1 of record 0
        u8 _1f92[0x1f98 - 0x1f92];
        u64 _1f98;
        f32 _1fa0;
        f32 _1fa4;
        f32 _1fa8;
        f32 _1fac;
        u8 _1fb0[0x1fc8 - 0x1fb0];
        f32 _1fc8;
        f32 _1fcc;
        f32 _1fd0;
        f32 _1fd4;
        f32 _1fd8;
        f32 _1fdc;
        u8 _1fe0[0x1ff4 - 0x1fe0];
        u8 _1ff4;
        u8 _1ff5[0x2088 - 0x1ff5];
    };
    static_assert(sizeof(Record) == 0x2088);

    // The result that 0x710129276c fills from a record (layout from Graphics::sub_7100F2E2A4, which copies
    // it to the registered Unk_7100f35df8 settings).
    struct Result {
        u64 _0;
        sead::BoundBox2f bounds;
        f32 _18;
        Unk_7100f35df8::Unk_20 _1c;
        f32 _2c;
    };

    // 0x710129175c: the constructor (vtable 0x7102519290, hostio::Node base).
    Unk_710129175c();
    virtual ~Unk_710129175c();

    void sub_71012920C4(s32 index);
    // 0x71012920ec (declaration only; placeholder name): refreshes record `view` of the blocks.
    void sub_71012920EC(s32 view);
    // 0x710129276c (declaration only; placeholder name): copies record `index` (the first if out of range)
    // into `result`.
    void sub_710129276C(s32 index, Result* result);

    u32 _8;
    u8 _c[4];
    sead::Buffer<Record> mRecords;
    agl::utl::DebugTexturePage mPage;
    u8 _260[8];
};
KSYS_CHECK_SIZE_NX150(Unk_710129175c, 0x268);

// Declaration only: F2C140 constructs these (0x1010 bytes at 0x7100f185a4, stored at Graphics + 0x388;
// 0x178 bytes at 0x7100efd9b8, stored at + 0x3a8) and the GrudgeRenderer at + 0x3a0 (0x2fb0 bytes; name from
// the CSV, namespace unknown). Graphics::sub_7100F2E2A4 calls one method of each.
class Unk_7100f185a4 : public sead::hostio::Node {
public:
    // The vtable (0x71024f4218) starts with hostio::Node's type getter and then the destructor
    // pair; 0x7100f18704 / 0x7100f1889c.
    Unk_7100f185a4();
    virtual ~Unk_7100f185a4();
    // One 0x68-byte map-unit entry of the tables at +0xfd0. The map screen sets the colour (+0x20),
    // the two floats at +0x54 and the flags (+0x5f) through the setters below.
    struct UnitEntry {
        // +0x00: the reference records (8 bytes each; the byte at +2 is 0xfe for the special one).
        struct RefRecord {
            u8 _0[2];
            u8 _2;
            u8 _3[5];
        };
        static_assert(sizeof(RefRecord) == 8);
        /* 0x00 */ sead::Buffer<RefRecord> mRefs;
        u8 _10[0x20 - 0x10];
        /* 0x20 */ sead::Color4f mColor;
        /* 0x30 */ sead::Vector3f _30;
        /* 0x3c */ sead::Vector3f _3c;
        /* 0x48 */ sead::Vector3f _48;
        /* 0x54 */ sead::Vector2f _54;
        u8 _5c[0x5e - 0x5c];
        /* 0x5e */ u8 mType;
        /* 0x5f */ u8 mFlags;
        /* 0x60 */ u8 _60;
        /* 0x61 */ u8 mColorSetMaybe;
        u8 _62[0x68 - 0x62];

        // The original destructor is empty but out of line, so the entries arrays carry an array
        // cookie (the group destructor and the model-data teardown subtract 8 before delete[]).
        ~UnitEntry() {}
    };
    static_assert(sizeof(UnitEntry) == 0x68);

    // One group of the table at +0xfd0: the 0x68-byte unit entries and the two flag bytes at +0x20 /
    // +0x21 (0x7100f19c4c skips a group whose +0x21 bit 0 is set).
    struct UnitGroup {
        sead::Buffer<UnitEntry> mEntries;
        u8 _10[0x10];
        u8 _20;
        u8 _21;
    };

    void sub_7100F1AC58();
    // 0x7100f1b020 (declaration only): draws the map units and the map's scene model through `context`.
    // Needed by the map screen's draw override (lane2's m33).
    void sub_7100F1B020(agl::DrawContext* context);
    // 0x7100f1ac50: the projection at +0x128. The map screen's screen-position
    // helper casts it to sead::PerspectiveProjection, so it is returned as sead::Projection.
    sead::Projection& getProjectionMaybe();
    // 0x7100f1b6e0: frees the dynamic map texture and puts the Black2D sampler back on mSampler0.
    void freeDynamicTextureMaybe();
    // The map draw override 0x71009e5080 passes the sampler's texture (this + 0x8d8) to
    // eui::SetupTextureInfoByAglTextureData, so lane2 needs it through the sampler.
    agl::TextureData& getMapTextureDataMaybe() { return mSampler0.getTextureData(); }
    // 0x7100f19c4c: moves every unit's flags byte to +0x60 and clears it, for every group that is
    // present and has bit 0 of +0x21 clear.
    void sub_7100F19C4C();
    // 0x7100f19f90 (placeholder name): sets the colour of map unit `id` (group in the high half,
    // index in the low 16 bits) and sets bit 0 of its flags.
    void setMapUnitColorMaybe(s32 id, const sead::Color4f& color);
    // 0x7100f1a30c (placeholder name): stores the two-float value at +0x54 of map unit `id` when
    // its type is 3, then sets bit 3 of its flags.
    void setMapUnitValueMaybe(s32 id, const sead::Vector2f& value);
    // 0x7100f1a1b4 (placeholder name): stores the three vectors at +0x30 / +0x48 / +0x3c of map unit
    // `id` when they (or the compared flag bit) differ, then sets bit 2 of its flags.
    void setMapUnitTransformMaybe(s32 id, const sead::Vector3f& value30, const sead::Vector3f& value48,
                                  const sead::Vector3f& value3c);
    // 0x7100f1a034 (placeholder name): sets bit 4 of map unit `id`'s flags to `visible` and always
    // sets bit 1; for type 3 units whose reference records contain 0xfe, updates bit 5 of every unit
    // of the group.
    void setMapUnitVisibleMaybe(s32 id, bool visible);
    // 0x7100f19928: destroys the model render data the renderer built.
    void sub_7100F19928(ksys::gfx::ModelRenderDataMaybe* data);
    // 0x7100f19a2c (declaration only; 176 B): stores the scene the renderer draws and the scene
    // model's gsys::ModelNW (+0x56d8), then hands that model to the shader context's
    // setSceneMaterial. Graphics::sub_7100F2C140 passes the scene it creates for the map.
    void sub_7100F19A2C(gsys::ModelScene* scene);
    // 0x7100f1f170: slot 11 of the object's gsys::IModelMgrCallback table; destroys a render data
    // through the three renderers, exactly like ksys::gfx::UkingModelRenderOptionsMgr.
    void sub_7100F1F170(ksys::gfx::ModelRenderDataMaybe* data);
    // 0x7100f1ab60: stores the two screen coordinates the map screen computes (each truncated to 16 bits).
    void setPosXY(s32 x, s32 y);
    // 0x7100f1ab70: sets camera A's direct matrix from `camera`, refreshes its view matrix, stores the
    // projection's field of view and, when `camera` is a look-at camera, copies its at vector.
    void setCameraMaybe(const sead::Camera& camera, f32 fov);
    // Inline-only in the original; name is a guess. ScreenAppMapDungeon 0x71009e78d8
    // changes bit 3 of the constructor's flags word at +8.
    void setMapModeMaybe(bool enabled) { mFlags.changeBit(3, enabled); }
    // 0x7100f1f278 is slot 3 of the object's gsys::IModelResourceCallback table (+0x10 of the
    // object); 0x7100f1f1f8 is slot 0x90 of the primary table and has the same signature. The
    // callback bases are not modelled, so both are declared as plain members.
    void m3(const gsys::IModelResourceCallback::MaterialArg& arg);
    void setMaterialReversePolygonOffsetMaybe(const gsys::IModelResourceCallback::MaterialArg& arg);

private:
    // +0 is the vptr inherited from hostio::Node.
    sead::BitFlag32 mFlags = 0;
    u8 _c[4];
    sead::CriticalSection mCS;
    // +0x50 / +0x54: both are 640 in the constructor.
    u32 _50 = 640;
    u32 _54 = 640;
    sead::DirectCamera mCameraA;
    sead::DirectCamera mCameraB;
    sead::PerspectiveProjection mProjection;
    // The projection's camera parameters.
    f32 _1e8 = 45.0f;
    f32 _1ec = 10.0f;
    f32 _1f0 = 1500.0f;
    u8 _1f4 = 0;
    u8 _1f5[3];
    // 0x7100f1ab70 stores a look-at camera's at vector here.
    sead::Vector3f _1f8 = {0.0f, 0.0f, 0.0f};
    u8 _204[4];
    agl::utl::DebugTexturePage mDebugPage;
    gsys::ModelRenderContext mRenderContext;
    gsys::ModelRenderUnitNodeArray mRenderUnitNodes;
    // +0x7e8: cleared by sub_7100F1AC58 with the frame flip.
    gsys::ModelRenderQueue mRenderQueue;
    // +0x828: cleared by sub_7100F1AC58 (purpose unknown).
    s32 _828 = 0;
    u8 _82c[4];
    agl::RenderBuffer mRenderBuffer;
    sead::Viewport mViewport;
    // Filled from DynamicTextureAllocator::alloc and freed by freeDynamicTextureMaybe.
    agl::TextureData* _8c0 = nullptr;
    agl::TextureSampler mSampler0;
    agl::RenderTargetColor mRenderTargetColor;
    agl::RenderTargetDepth mRenderTargetDepth;
    agl::TextureData mTextureData;
    agl::TextureSampler mSampler1;
    void* _fc0;
    void* _fc8;
    // 0xfd0: map-unit tables: the group is selected by the id's high half and each group is an
    // inline array of 0x68-byte entries indexed by the id's low 16 bits.
    sead::Buffer<UnitGroup*> mUnitGroups;
    u32 _fe0;
    u8 _fe4[4];
    // Two double-buffered id arrays at +0xfe8 / +0xff8 (the byte at +0x1008 selects one);
    // sub_7100F1AC58 clears the new one after flipping. The second word is padding.
    struct IdBuffer {
        s32 mSize;
        u8* mIds;
    };
    static_assert(sizeof(IdBuffer) == 0x10);
    IdBuffer mIdBuffers[2];
    u8 _1008;
    u8 _1009;
    u8 _100a[0x1010 - 0x100a];
};
KSYS_CHECK_SIZE_NX150(Unk_7100f185a4, 0x1010);
// Placeholder: the object at Unk_7100efd9b8::_120 (the destructor calls its third virtual slot).
class Unk_7100efd9b8Obj {
public:
    virtual void m0();
    virtual void m1();
    virtual void m2();

    u8 _8[0x638 - 0x8];
    // 0x7100f00018 clears bit 3 of this word.
    u32 _638 = 0;
};

class Unk_7100efd9b8 : public sead::hostio::Node {
public:
    // 0x7100efd9b8: the two-handle resource holder constructor.
    Unk_7100efd9b8();
    virtual ~Unk_7100efd9b8();

    void sub_7100EFE030();
    // 0x7100efdce8: destroys the model render data the renderer built.
    void sub_7100EFDCE8(void* data);
    // 0x7100eff5e8 (declaration only; placeholder name): draws the renderer's debug geometry.
    void sub_7100EFF5E8(agl::DrawContext* context, gsys::ModelRenderContext* render_context);

private:
    u32 _8 = 0;
    u8 _c[4];
    void* _10 = nullptr;
    u32 _18 = 0;
    u8 _1c[4];
    void* _20 = nullptr;
    u32 _28 = 0;
    u8 _2c[4];
    void* _30 = nullptr;
    u32 _38 = 0;
    u8 _3c[4];
    void* _40 = nullptr;
    ksys::res::Handle mHandleA;
    void* _98 = nullptr;
    u32 _a0 = 0;
    u8 _a4[4];
    void* _a8 = nullptr;
    u64 _b0 = ~0ull;
    ksys::res::Handle mHandleB;
    u32 _108 = 0;
    u8 _10c[4];
    void* _110 = nullptr;
    u32 _118 = ~0u;
    u8 _11c[4];
    Unk_7100efd9b8Obj* _120 = nullptr;
    void* _128 = nullptr;
    u32 _130 = 0;
    u32 _134 = ~0u;
    u32 _138 = ~0u;
    u32 _13c = ~0u;
    u32 _140 = ~0u;
    u32 _144 = ~0u;
    u32 _148 = ~0u;
    u32 _14c = ~0u;
    u32 _150 = ~0u;
    u32 _154 = ~0u;
    u32 _158 = ~0u;
    u32 _15c = 0;
    f32 _160 = -1.0f;
    f32 _164 = -1.0f;
    u32 _168 = 0xFFFFFFFF;
    u8 _16c[0x178 - 0x16c];
};
KSYS_CHECK_SIZE_NX150(Unk_7100efd9b8, 0x178);
// 0x7102519120 (placeholder name): the distance GrudgeRenderer::sub_710128F4BC resets _264 to.
// The original reaches it with a direct adrp + ldr, so it is a hidden-visibility object.
KSYS_VISIBILITY_HIDDEN extern const f32 cGrudgeResetDistance;
// 0x71025192d0 (placeholder name): the per-frame item-filter alpha step scale. Direct adrp + ldr
// in 0x7101293fc0, so a hidden-visibility object defined in another TU.
KSYS_VISIBILITY_HIDDEN extern const f32 cItemFilterFadeStep;

// Placeholder name (vtable 0x71025191c8): a hostio node the grudge renderer allocates 0x130-byte
// instances of (constructor 0x710128fcb8, dtor 0x710128fd48 / 0x710128fe88, cleanup 0x710128fd94).
// sub_7101290010 stores the reciprocal of `n` and that reciprocal scaled by _11c.
class Unk_71025191c8 : public sead::hostio::Node {
public:
    // 0x710128fedc: the parameters the renderer passes when it creates a unit (fields from
    // offset 0x10 on; only the ones the unit reads are named by offset).
    struct CreateArg {
        sead::Heap* mHeap;  // 0
        u8 _8[0x10 - 0x8];
        s32 _10;    // 0x10
        s32 _14;    // 0x14: formatted into the unit name
        s32 _18;    // 0x18
        u8 _1c;     // 0x1c: selects the extra flag bits
        u8 _1d[3];
        s32 _20;    // 0x20
        s32 _24;    // 0x24
    };

    Unk_71025191c8();
    virtual ~Unk_71025191c8();
    void sub_7101290010(s32 n);
    void sub_710128FD94();
    // 0x710128fedc: declares and creates the uniform block, names the unit and stores its
    // parameters.
    void sub_710128FEDC(const CreateArg& arg);

private:
    /* 0x08 */ agl::UniformBlock mUniformBlock;
    /* 0x80 */ sead::FormatFixedSafeString<32> mName;
    u8 _b8[0x30];
    /* 0xe8 */ f32 _e8 = sead::Mathf::maxNumber();
    /* 0xec */ f32 _ec = sead::Mathf::maxNumber();
    /* 0xf0 */ f32 _f0 = sead::Mathf::maxNumber();
    /* 0xf4 */ f32 _f4 = -sead::Mathf::maxNumber();
    /* 0xf8 */ f32 _f8 = -sead::Mathf::maxNumber();
    /* 0xfc */ f32 _fc = -sead::Mathf::maxNumber();
    /* 0x100 */ f32 _100 = -1.0f;
    /* 0x104 */ f32 _104 = sead::Mathf::maxNumber();
    /* 0x108 */ u32 _108;
    /* 0x10c */ s32 _10c = -1;
    /* 0x110 */ s32 _110 = -1;
    /* 0x114 */ s32 _114 = -1;
    /* 0x118 */ s32 _118 = -1;
    /* 0x11c */ s32 _11c = -1;
    /* 0x120 */ u16 _120 = 0;
    u8 _122[0x128 - 0x122];
    /* 0x128 */ void* _128 = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_71025191c8, 0x130);

class GrudgeRenderer {
public:
    // One per grudge material slot: the texture the renderer binds for it. 0x710128f2a4 refreshes
    // every entry whose flag bit 0 is set.
    struct Entry {
        agl::TextureData mTextureData;                 // 0x000
        agl::TextureSampler mSampler;                  // 0x128
        s32 mTextureIndex;                             // 0x298
        u8 _29c[4];
        ksys::res::TextureHandleList::Entry mHandle;   // 0x2a0
        u32 _350;
        u32 _354;
        u32 _358;
        u8 _35c[4];
        s32 mMaterialIndex;  // 0x360
        u8 mFlag;            // 0x364
        u8 _365[3];
        s32 _368;  // -1
        u8 _36c[4];
        sead::SafeString mName;  // 0x370: "Undefined"
        s32 _380;                // -1
        u8 _384[4];
        sead::SafeString mName2;  // 0x388: "Undefined"
    };
    static_assert(sizeof(Entry) == 0x398);

    // The 0xa40-byte render record at _ed0 (0x710128e804 builds it, 0x710128f148 destroys it):
    // the grudge units it draws followed by the three texture entries they sample.
    struct TextureSet {
        struct TextureEntry {
            agl::TextureData mTextureData;                 // 0x000
            agl::TextureSampler mSampler;                  // 0x128
            s32 mTextureIndex;                             // 0x298
            u8 _29c[4];
            ksys::res::TextureHandleList::Entry mHandle;   // 0x2a0
            u64 _350;
            u32 _358;
            u8 _35c[4];
        };
        static_assert(sizeof(TextureEntry) == 0x360);

        sead::PtrArray<Unk_71025191c8> mUnits;  // 0x000
        TextureEntry mEntries[3];              // 0x010
        u8 mFlags;                             // 0xa30: bits 3..5: entry needs its texture bound
        u8 _a31[3];
        s32 mTableIndex;     // 0xa34: index in _ed0
        s32 mMaterialIndex;  // 0xa38
        u8 _a3c[4];
    };
    static_assert(sizeof(TextureSet) == 0xa40);

    // The user data of a texture bind request (0x710128d550 reads it through the handle entry):
    // the record slot in _ed0, the entry index and what the request refers to.
    SEAD_ENUM(BindKind, Entry, TextureSet)
    struct TextureBindResult {
        s32 mTableIndex;  // 0: index in _ed0
        s32 mEntryIndex;  // 4: entry / material slot
        BindKind mKind;   // 8: Entry = renderer entry, TextureSet = render record
    };
    static_assert(sizeof(TextureBindResult) == 0xc);

    // 0x710128d550: marks the renderer entry or the render record of a finished texture bind.
    void sub_710128D550(ksys::res::TextureHandleList::Entry* entry);
    // 0x710128f88c: whether `unit` is a grudge model whose material `material` is Mt_Grudge.
    bool sub_710128F88C(gsys::ModelUnit* unit, s32 material);
    // 0x710128f41c: copies the view frustum of the render context and derives the grudge draw
    // distances from its near plane and field of view.
    void sub_710128F41C(const gsys::ModelRenderContext* context, f32 fov);
    // 0x710128f2a4: rebinds the textures of the entries whose flag bit 0 is set.
    void sub_710128F2A4();
    // 0x710128f698: binds the textures of the three texture entries of `set` on `model`.
    void sub_710128F698(gsys::ModelNW* model, TextureSet* set);
    // 0x710128f148: destroys the model render data the renderer built.
    void sub_710128F148(void* data);
    // 0x710128f4bc: once flag bit 0 of _2ef8 is set, records the camera's world position, resets the
    // distance at 0x264 to 20 and asks the model at 0x268 to draw.
    void sub_710128F4BC(const sead::Camera* camera);
    // 0x710128f9e0 (declaration only): walks the model's unit access array and marks the matching
    // name's flag.
    void sub_710128F9E0(gsys::Model* model);
    // 0x710128f888 (declaration only; placeholder name): draws the renderer's debug geometry.
    void sub_710128F888(agl::DrawContext* context, gsys::ModelRenderContext* render_context);

private:
    u8 _0[0x8];
    agl::cull::ViewFrustumCulling mFrustum;  // 0x008
    sead::Vector3f _240;
    f32 _24c;
    f32 _250;
    f32 _254;
    f32 _258;
    f32 _25c;
    s32 _260;
    f32 _264;
    gsys::Model* _268;
    u8 _270[0x280 - 0x270];
    gsys::ModelResource* _280;
    gsys::ModelNW* _288;
    u8 _290[0x3c0 - 0x290];
    sead::SafeArray<Entry, 3> mEntries;
    u8 _e88[0xed0 - 0xe88];
    sead::SafeArray<TextureSet*, 0x400> _ed0;
    u8 _2ed0[0x2ee8 - 0x2ed0];
    sead::Buffer<agl::utl::AtomicPtrArray<Unk_71025191c8>> mUnitArrays;
    u8 _2ef8;
    u8 _2ef9[0x2fb0 - 0x2ef9];
};
KSYS_CHECK_SIZE_NX150(GrudgeRenderer, 0x2fb0);

// 0x7101290034 (placeholder name; in GrudgeRenderer's TU): ray cast from `start` along `displacement` against
// the ground layer with the Grudge ground-hit filter; stores the hit position.
bool sub_7101290034(const sead::Vector3f& start, const sead::Vector3f& displacement, sead::Vector3f* hit_pos);

// F2C140 allocates 0x6c0 bytes, constructs this object at 129421C and stores it at
// Graphics + 0x370. Its source name is unknown (the parameter names are "ksysla" and the ground
// ambient light parameters).
class Unk_710129421c : public sead::hostio::Node, public agl::utl::IParameterIO {
public:
    // The 0x7e8-byte entries of the buffer at 0x1e0 (destruction order from 0x7101294870).
    struct Entry {
        agl::UniformBlock _0;          // 0x000
        agl::RenderBuffer _78;         // 0x078
        agl::RenderTargetColor _e0;    // 0x0e0
        agl::TextureSampler _258;      // 0x258
        agl::TextureSampler _3c8;      // 0x3c8
        agl::TextureSampler _538;      // 0x538
        agl::TextureData mTextureData;  // 0x6a8
        sead::Color4f _7d0;
        f32 _7e0;
        f32 _7e4;
    };
    static_assert(sizeof(Entry) == 0x7e8);

    // The ground ambient light parameter object at 0x440: ParameterObj plus eighteen float parameters.
    struct Params : agl::utl::ParameterObj {
        f32 _30 = 0.2f;
        f32 _34 = 0.25f;
        f32 _38 = 3.0f;
        u8 _3c[4];
        agl::utl::Parameter<f32> mParams[18];
    };
    static_assert(sizeof(Params) == 0x280);

    // 0x710129421c: the constructor (vtable 0x71025192d8, hostio::Node primary base and
    // IParameterIO second base at +8).
    Unk_710129421c();
    // 0x7101294870
    ~Unk_710129421c() override;

    // 0x71012955ac (placeholder name): stores value at +0x7e4 of entry index of the 0x7e8-byte entry
    // buffer at 0x1e0.
    // 0x7101295560 (placeholder name): stores the colour at +0x7d0 of entry index.
    void sub_7101295560(s32 index, const sead::Color4f& color);
    // 0x710129558c (placeholder name): stores value at +0x7e0 of entry index.
    void sub_710129558C(f32 value, s32 index);
    void sub_71012955AC(f32 value, s32 index);

    /* 0x1d8 */ u32 _1d8 = 2;
    /* 0x1e0 */ sead::Buffer<Entry> mEntries;
    /* 0x1f0 */ u64 _1f0 = 0;
    /* 0x1f8 */ agl::utl::DebugTexturePage mPage;
    /* 0x438 */ u8 _438 = 0;
    /* 0x440 */ Params mParams;
};
KSYS_CHECK_SIZE_NX150(Unk_710129421c, 0x6c0);

// Partial declaration only: F2C140 constructs this 0x258-byte item filter at
// 1293BAC and stores it at 398. Table 25192A8 inherits Node's class-type method;
// 1293BAC initializes the word at C to 2, and 1293D68 / 1293FC0 consume its flags.
// The DebugTexturePage at 10 and its lifetime remain unmodeled.
class Unk_7101293bac : public sead::hostio::Node {
public:
    // 0x7101293bac: the item filter constructor.
    Unk_7101293bac();
    // 0x7101293c9c: sets up the debug texture page with the "ItemFilter" name.
    void sub_7101293C9C(s32 unused, sead::Heap* heap);
    virtual ~Unk_7101293bac();
    // 0x7101293d68: selects one of the four named item-filter render units.
    void sub_7101293D68(u32 index, gsys::ModelScene* scene);
    // 0x7101293fc0: fades the item-filter alpha with the scene's rain ratio and applies it.
    void sub_7101293FC0();
    // 0x7101293ce8: selects filter index `index` and its GBuffer material-id mask.
    void sub_7101293CE8(u32 index, u8 value, gsys::ModelScene* scene);
    s32 _8;
    sead::BitFlag32 mFlags;
    agl::utl::DebugTexturePage mPage;
    u8 _250;
    u8 _251[3];
    // Graphics::setRainRatio 0x7100f2fcdc scales the rain ratio by 1 - this value.
    f32 _254;
};
KSYS_CHECK_SIZE_NX150(Unk_7101293bac, 0x258);

// Placeholder: the object at Graphics + 0xb70 (only the Vector3f that Graphics::sub_7100F3592C
// writes is modelled).
struct Unk_b70 {
    u8 _0[0x110];
    sead::Vector3f _110;
};

namespace gsys {

// The resource editor's callback interface (vtable 0x71024f4a20, all ten slots point at the empty
// out-of-line defaults 0x7100f36350 / 0x7100f36354 / 0x7100f36428 - 0x7100f36444). Graphics implements
// it as its first base: the primary vtable 0x71024f45c0 has the ten overrides at +0x10 and its
// destructor pair right after. Method names are from the original's symbols; the argument block is a
// placeholder.
class IResourceEditorCallback {
public:
    // The two models the editor callbacks work on. Both callees they reach walk the model's unit
    // access array (count at +0x38, elements at +0x40, as in gsys::Model): editorCallback3 forwards
    // +0x0 to the Grudge renderer and editorCallback8 passes +0x8 to the model effects manager.
    // Placeholder names.
    struct Arg {
        gsys::Model* _0;
        gsys::Model* _8;
    };

    virtual void editorCallback0(const Arg& arg);
    virtual void editorCallback1(const Arg& arg);
    virtual void getModelFmdbPath(const char** path, const Arg& arg);
    virtual void editorCallback3(const Arg& arg);
    virtual void editorCallback4(const Arg& arg);
    virtual void editorCallback5(const Arg& arg);
    virtual void editorCallback6(const Arg& arg);
    virtual void editorCallback7(const Arg& arg);
    virtual void editorCallback8(const Arg& arg);
    virtual void editorCallback9(const Arg& arg);
};

}  // namespace gsys

namespace gsys {
class Layer;

// Placeholder declaration: the copy-layer texture object at Graphics + 0xad8 (the copy pass).
// Only the two methods Graphics calls and the byte at +0x508 are modelled; the real class belongs
// in lib/gsys (request to gen).
class CopyLayerTexture {
public:
    void setLayer(Layer* layer);
    void adjustTrimViewportToLayer();

    u8 _0[0x508];
    u8 _508;
};
}  // namespace gsys

namespace agl {
class ShaderProgram;
}  // namespace agl

namespace gfx {

// 0x71024f43e0: the noise gauge's per-frame update constants, the draw constants and the gauge's
// shader program (stored at +0x28 by the setup at 0x7100f1fe6c).
struct NoiseGaugeParams {
    f32 speedScale;                 // +0x00
    f32 speedPerSound;              // +0x04
    s32 soundCountBias;             // +0x08
    f32 chaseRate;                  // +0x0c
    f32 drawScale;                  // +0x10
    s32 maxTextureSize;             // +0x14
    f32 lineWidth2;                 // +0x18
    f32 lineWidth1;                 // +0x1c
    s32 uniformCreated;             // +0x20
    u8 _24[4];                      // +0x24
    agl::ShaderProgram* program;    // +0x28
};
// 0x71024f43e0 (defined in gameUnk_710129175c.cpp): hidden visibility, so the loads are a direct
// adrp + ldr rather than a folded literal.
KSYS_VISIBILITY_HIDDEN extern NoiseGaugeParams sNoiseGaugeParams;
// 0x710260af30 is a bss word that the original never writes; defined in the same file.
KSYS_VISIBILITY_HIDDEN extern f32 cNoiseGaugeAngleSpeedMaybe;

// The noise gauge renderer at Graphics + 0x390 (the initializer F2C140 allocates 0xa38 bytes). Its
// ctor 0x7100f20000 gives the layout; vtable 0x71024f4368 (hostio::Node's type getter, then the dtor
// pair 0x7100f200b8 / 0x7100f201a8).
class NoiseGauge : public sead::hostio::Node {
public:
    NoiseGauge();
    virtual ~NoiseGauge();

    // 0x7100f201cc (declaration only): fills the 16 noise colours, sets up the debug texture page,
    // the uniform block, the vertex/index buffers and the vertex attribute.
    void initMaybe(sead::Heap* heap);
    // 0x7100f20580 (name is a guess): advances the gauge angle and the 16 noise points by the
    // frame delta and uploads the new parameters.
    void updateMaybe();
    // 0x7100f203d0 (placeholder name): allocates and fills the vertex and index GPU blocks.
    void sub_7100F203D0(sead::Heap* heap);
    // 0x7100f20774 (placeholder name): uploads the gauge parameters and the 16 noise points to
    // the uniform block, then flushes the block's GPU cache.
    void updateUniformBlockMaybe();
    // 0x7100f20874 (name is a guess): toggles the uniform block's buffer index each frame.
    void toggleUniformBufferMaybe();
    // 0x7100f208e4 (placeholder name): if no scratch texture is allocated yet, allocates it through
    // DynamicTextureAllocator, draws the gauge into it and applies it to mSampler.
    void drawMaybe(f32 scale, agl::DrawContext* context);
    // 0x7100f20c88: frees the scratch texture and puts the Black2D sampler back on mSampler, like
    // Unk_7100f185a4::freeDynamicTextureMaybe.
    void releaseMaybe();
    // The main screen's draw override passes this to SetupTextureInfoByAglTextureData (the
    // sampler's texture data is what the original reads at NoiseGauge + 0x40).
    agl::TextureData& getTextureDataMaybe() const { return mSampler.getTextureData(); }
    // +0xc: the gauge scale set by the main screen; the gauge setup reads it as a float.
    f32 getScaleMaybe() const { return mScale; }
    void setScaleMaybe(f32 scale) { mScale = scale; }

private:
    /* 0x08 */ u32 mFlags = 0xc00;
    /* 0x0c */ f32 mScale = 0;
    // 0x7100f20774 stores both words into the uniform data as floats, so they are f32.
    f32 _10 = 0;
    f32 _14 = 0;
    // 0x18: 16 four-component noise points, allocated by initMaybe. The element type is trivial
    // (the allocation in the original emits no element constructor), so use a plain vector.
    sead::Buffer<sead::Vector4f> mPoints;
    /* 0x28 */ agl::TextureData* mDynamicTexture = nullptr;
    /* 0x30 */ agl::TextureSampler mSampler;
    /* 0x1a0 */ agl::RenderBuffer mRenderBuffer;
    /* 0x208 */ agl::RenderTargetColor mRenderTargetColor;
    /* 0x380 */ sead::Viewport mViewport;
    /* 0x3a8 */ s32 _3a8 = 0;
    /* 0x3b0 */ agl::UniformBlock mUniformBlock;
    // 0x428 / 0x460: the 0x80-byte vertex bytes and the 0x80 u16 indices (allocated by 0x7100f203d0).
    agl::GPUMemBlock<u8> mVertexData;
    agl::GPUMemBlock<u16> mIndexData;
    /* 0x498 */ agl::VertexBuffer mVertexBuffer;
    /* 0x5b8 */ agl::IndexStream mIndexStream;
    /* 0x618 */ agl::VertexAttribute mVertexAttribute;
    /* 0x7f8 */ agl::utl::DebugTexturePage mDebugPage;
};
KSYS_CHECK_SIZE_NX150(NoiseGauge, 0xa38);

}  // namespace gfx

// Partial declaration: name from the CSV Graphics::createInstance (0x7100f2a1d0).
// Source namespace remains unknown; global spelling follows the existing scene placeholders.
// No instance layout or construction is modeled here.
class Graphics : public gsys::IResourceEditorCallback, public gsys::IModelScenePassCallback {
public:
    // Placeholder name: the block at Graphics + 0xa98 (shadow settings; lane3 s35, only the fields
    // EventChangeShadowNearAndFar::calc_ writes are modeled).
    struct Unk_a98 {
        u8 _0[0x11];
        /* 0x11 */ u8 mQuality;  // shadow quality index (1..4), set from Graphics' shadow mode switch
        /* 0x12 */ u16 mFlags;  // bit 8: near distance set manually, bit 9: far distance set manually
        // Split distances sub_710128BA24 compares a model's max box extent against.
        /* 0x14 */ f32 _14;
        u8 _18[0xc];
        /* 0x24 */ f32 _24;
        u8 _28[0xc];
        /* 0x34 */ f32 _34;
        u8 _38[0x7c - 0x38];
        /* 0x7c */ sead::Atomic<s32> mChangeCount;  // bumped by incrementChangeCountMaybe
        u8 _80[0x540 - 0x80];
        /* 0x540 */ f32 mShadowNear;
        /* 0x544 */ f32 mShadowFar;

        void setQuality(u32 quality);
        void incrementChangeCountMaybe();
        // 0x710128ba24: picks the depth-shadow cascade of `unit` from its box extent and the
        // three split distances.
        void sub_710128BA24(gsys::ModelUnit* unit, const sead::BoundBox3f& box);
    };

    // The debug render texture bank at Unk_378_18 + 0x6b0: two banks of four {TextureData,
    // GPUMemBlock<u8>} pairs, each bank followed by its own two matrices and parameters.
    // 0x710128ab14 constructs it and 0x710128aa50 destroys it (both out of line in the
    // render-block TU).
    struct Unk_378_18_6b0 {
        struct Unit {
            agl::TextureData mTexture;
            agl::GPUMemBlock<u8> mBlock;
        };
        static_assert(sizeof(Unit) == 0x160);
        struct Bank {
            Unit mUnits[4];
            sead::Matrix34f _580;
            sead::Matrix34f _5b0;
            f32 _5e0;
            f32 _5e4;
            f32 _5e8;
            u8 _5ec = 0;
            u8 _5ed[3];
        };
        static_assert(sizeof(Bank) == 0x5f0);

        Unk_378_18_6b0();
        ~Unk_378_18_6b0();

        Bank mBanks[2];
    };
    static_assert(sizeof(Unk_378_18_6b0) == 0xbe0);

    // Placeholder names (lane4 s64): the object at Graphics + 0x378 points (+0x18) to a block that holds two floats
    // at 0x1520 / 0x1524 (read by Camera::updateMatrix and sub_710079AE60 as clip distances).
    struct Unk_378_18 {
        struct Cell {
            u8 _0[0x18];
            f32 _18;
            u8 _1c[4];
        };
        static_assert(sizeof(Cell) == 0x20);
        // The debug render targets and their samplers (destruction order from 0x7101288710).
        /* 0x000 */ agl::UniformBlock _0;
        /* 0x078 */ agl::RenderBuffer _78;
        /* 0x0e0 */ agl::RenderTargetColor _e0;
        /* 0x258 */ agl::RenderTargetColor _258;
        /* 0x3d0 */ agl::TextureSampler _3d0;
        /* 0x540 */ agl::TextureSampler _540;
        /* 0x6b0 */ Unk_378_18_6b0 _6b0;
        /* 0x1290 */ sead::Vector3f _1290;
        /* 0x129c */ sead::Vector3f _129c;
        // 10D103C indexes 0x20-byte cells with Buffer's bounds fallback and reads f32 +0x18.
        /* 0x12a8 */ sead::Buffer<Cell> _12a8;
        u8 _12b8[0x14f0 - 0x12b8];
        /* 0x14f0 */ f32 _14f0;
        u8 _14f4[0x1500 - 0x14f4];
        // Bit 2 is the result of Graphics::sub_7100F35E5C.
        /* 0x1500 */ u8 _1500;
        u8 _1501[0x1504 - 0x1501];
        /* 0x1504 */ sead::Vector3f _1504;
        /* 0x1510 */ sead::Vector3f _1510;
        /* 0x151c */ f32 _151c;
        /* 0x1520 */ f32 _1520;
        /* 0x1524 */ f32 _1524;
        u8 _1528[4];
        /* 0x152c */ u32 _152c;
    };
    static_assert(sizeof(Unk_378_18) == 0x1530);
    struct Unk_378 : public sead::hostio::Node {
        // 0x7101288658: constructs the block (0x2b8 bytes; Graphics' initializer stores it at
        // Graphics + 0x378).
        Unk_378();
        // 0x7101288710 / 0x7101288860
        virtual ~Unk_378();
        // 0x7101289934 (declaration only; placeholder name and parameter types): updates record
        // `index` of the 0x1530-byte blocks with the two vectors and the frame delta.
        void sub_7101289934(s32 index, const sead::Vector3f* a, const sead::Vector3f* b, f32 value,
                            f32 delta);
        // 0x71012890fc (declaration only; placeholder name): refreshes record `view` of the blocks.
        void sub_71012890FC(s32 view);
        // 0x710128a988 (declaration only; placeholder name): draws the block's debug geometry.
        void sub_710128A988(agl::DrawContext* context, u8 view_index);
        // 0x710128aa30 (placeholder name): stores `value` at +0x14f0 of block `view`.
        void setValueMaybe(f32 value, s32 view);

        /* 0x008 */ u32 _8;  // set to 6 by the constructor
        /* 0x010 */ sead::Buffer<Unk_378_18> mBlocks;
        /* 0x020 */ void* _20;  // the "depth_analyzer" shader program (0x71012889a4)
        /* 0x028 */ agl::utl::DebugTexturePage mPage;
        /* 0x268 */ s32 _268;  // grid row width used by 10D103C
        /* 0x26c */ s32 _26c;  // grid column count
        /* 0x270 */ sead::Buffer<f32> mSamples;  // history of the analyzer's values
        /* 0x280 */ u32 mSampleIndex;
        /* 0x284 */ u8 _284;
        /* 0x288 */ f32 _288;
        /* 0x28c */ f32 _28c;
        /* 0x290 */ f32 _290;
        /* 0x294 */ f32 _294;
        /* 0x298 */ f32 _298;
        /* 0x29c */ f32 _29c;
        /* 0x2a0 */ f32 _2a0;
        /* 0x2a4 */ f32 _2a4;
        /* 0x2a8 */ f32 _2a8;
        /* 0x2ac */ f32 _2ac;
        /* 0x2b0 */ f32 _2b0;
    };
    static_assert(sizeof(Unk_378) == 0x2b8);

    // Placeholder (type unknown): the object at +0x668. WorldMgr::calcEntryJob writes the
    // byte at +0x19 and the float at +0x10 + 0x6c.
    // The 0x78-byte per-view record the object at +0x668 allocates (0x710128caec initializes it).
    struct Unk_668_10 {
        sead::Matrix34f mMatrix;
        sead::Matrix34f mPrevMatrix;
        sead::Vector3f _60;
        f32 mValue;
        // 0x710128cbcc chases the second float towards the first.
        f32 _70;
        f32 _74;
    };
    static_assert(sizeof(Unk_668_10) == 0x78);
    struct Unk_668 : public sead::hostio::Node {
        // 0x710128ca44: constructs the 0x20-byte object (vtable 0x71025190d0); its virtual dtor
        // pair is 0x710128ca70 / 0x710128cab0.
        Unk_668();
        virtual ~Unk_668();
        // 0x710128caec (placeholder name): allocates `count` 0x78-byte records and initializes them.
        void initMaybe(s32 count, sead::Heap* heap);
        // 0x710128cbcc (placeholder name): stores `value` at _10+0x70 and chases the value at
        // _10+0x74 towards it with the rate at +0x1c.
        void chaseValueMaybe(f32 value, f32 delta, bool snap);
        // 0x710128cf08 (declaration only; placeholder name): draws the object's debug geometry.
        void sub_710128CF08(agl::DrawContext* context, u8 view_index);

        u32 _8 = 0;
        Unk_668_10* _10 = nullptr;
        u8 _18 = 0;
        u8 _19 = 0;
        u8 _1a[2];
        f32 _1c = 0.1f;
    };

    // Original instance pointer 0x710260b060 (GOT 0x7102579d58).
    static Graphics* instance() { return sInstance; }
    Unk_668* get668Maybe() const { return _668; }
    // 0x7100f2a1d0: allocates the 0xfe8-byte instance and constructs it (SEAD_SINGLETON_DISPOSER).
    static Graphics* createInstance(sead::Heap* heap);
    static Graphics* sInstance;

    // 0x7100f2a6bc (placeholder name): the docked screen size (1920 x 1080). The UI layout scales it
    // down to the 1280 x 720 reference size below.
    static const sead::Vector2i& getScreenSize();
    // 0x7100f2a708 (placeholder name): the 1280 x 720 reference size of the UI layout.
    static const sead::Vector2i& getReferenceScreenSize();

    // Native F2E0F4 compares MaterialObj texture resources, or dirties all when texture is null.
    // Texture identity is also proved by initializer 128F724 and native finalizer FE0FE4.
    void sub_7100F2E0F4(gsys::ModelNW* model, const nn::gfx::ResTexture* texture);

    // 0x7100f2ddf0: declaration only; selects a lens-flare preset, negative disables it.
    // 0x7100f2dda0 (placeholder name): clears the first scene's cloud flag and, when the lens flare
    // effect exists, bit 10 of _284.
    void sub_7100F2DDA0();
    void sub_7100F2DDF0(s32 preset);

    // 0x7100f2b3dc: pushes the objects in the array at +0x178 into `array`.
    void sub_7100F2B3DC(sead::PtrArrayImpl* array);

    void sub_7100F2F1C8(Unk_7100f35df8* settings);
    void sub_7100F2F1E8(Unk_7100f35df8* settings);


    // 0x7100f2af70 (placeholder name; CSV Graphics::__auto0): stores the map kind (byte at +0xf59) under
    // the lock at +0xf18.
    void sub_7100F2AF70(u8 map);

    // 0x7100f300d0 (placeholder name): sets the demo toon light adjust colour parameter on the
    // environment unit's current material.
    void sub_7100F300D0(const sead::Color4f& color);

    // 0x7100f2e2a4 (placeholder name; CSV Graphics::__auto1): refreshes the registered settings from the
    // object at 0xb38 (if its flag is set), then updates the objects at 0x388 / 0x3a0 / 0x3a8.
    void sub_7100F2E2A4();
    // 0x7100f2dd98 / 0x7100f2dd9c (placeholder names; CSV nullsub_4128 / nullsub_4129): empty in this
    // build; initialise the graphics system for a stage generation.
    void initBeforeStageGenB();
    void initBeforeStageGenA();

    // 0x7100f2b424 (placeholder name): whether any material of the unit has render view option 4
    // enabled in view 0.
    bool sub_7100F2B424(gsys::ModelUnit* unit);

    // Callback argument of sub_7100F2DF04 (a model editor request: the mode at +4 picks the arm and
    // the word at +0 selects whether it applies).
    struct Unk_7100F2DF04Target {
        u8 _0[4];
        /* 0x04 */ u32 _4;
        u8 _8[0x28 - 0x8];
        /* 0x28 */ u32 _28;
        /* 0x2c */ u8 _2c;
        /* 0x2d */ u8 _2d;
        u8 _2e[0x64 - 0x2e];
        /* 0x64 */ u8 _64;
    };
    struct Unk_7100F2DF04Arg {
        /* 0x00 */ s32 _0;
        /* 0x04 */ s32 _4;
        u8 _8[0x10 - 0x8];
        /* 0x10 */ Unk_7100F2DF04Target* _10;
    };
    // 0x7100f2df04 (placeholder name): for mode 13 sets the target's bytes at +0x2c / +0x2d as well;
    // mode 14 only the common fields. Both set +0x64 last.
    void sub_7100F2DF04(Unk_7100F2DF04Arg* arg);

    // 0x7100f2afac / 0x7100f2afe8 / 0x7100f2b024 (lane4 s64; placeholder names; CSV Graphics::__auto9 / __auto14 / x):
    // store a byte at +0xf5b / +0xf5d / +0xf5f under the lock at +0xf18 (values 0 .. 2 seen).
    void sub_7100F2AFAC(u8 value);
    void sub_7100F2AFE8(u8 value);
    void sub_7100F2B024(u8 value);
    // 0x7100f35f28 / 0x7100f35f38 (lane4 s64): `_378->_18->_1520` / `_1524`.
    // 0x7100f3590c / 0x7100f35918 (placeholder names; SkyMgr::doCalc): set the value at +0x7e0 and
    // the colour at +0x7d0 of _370's first entry.
    void sub_7100F3590C(f32 value);
    // 0x7100f35e5c (unnamed in the CSV): updates the _378 blocks with the two Camera vectors and
    // the frame delta; returns bit 2 of the block's +0x1500 flag.
    bool sub_7100F35E5C(f32 value, const sead::Vector3f* a, const sead::Vector3f* b);
    void sub_7100F35918(const sead::Color4f& color);
    f32 sub_7100F35F28() const;
    f32 sub_7100F35F38() const;
    void sub_7100F35F50(agl::lyr::Layer* layer, bool value);
    void sub_7100F35F68(bool value);
    // 0x7100f3592c (placeholder name): copies three floats to the object at 0xb70 + 0x110.
    void sub_7100F3592C(const sead::Vector3f& value);

    // 0x7100f2f20c (placeholder name): the per-frame graphics update; takes the delta frame.
    void sub_7100F2F20C(f32 value);

    // 0x7100f35de8 (placeholder name; lane2 s47): called by ui::Manager::sub_7100A7F81C; sets a byte
    // at +0x508 of _ad8.
    void sub_7100F35DE8();
    // 0x7100f35dc0 (placeholder name): binds a layer to the copy-layer texture and re-adjusts its
    // trim viewport.
    void sub_7100F35DC0(gsys::Layer* layer);
    // 0x7100f35db0 (placeholder name): sets flag 0x10000 of _284.
    void sub_7100F35DB0();

    // 0x7100f2fb6c (placeholder name; CSV Graphics::__auto6): stores the ratio at 0xe84 and sets
    // uking_dynamic_proj_shadow_off to 1 - ratio.
    void sub_7100F2FB6C(f32 ratio);
    // 0x7100f2fc24 (placeholder name): stores the ratio at 0xe80 and sets
    // uking_dynamic_base_light_change_ratio to 1 - ratio.
    void sub_7100F2FC24(f32 ratio);
    // 0x7100f2fcdc (CSV name): sets uking_dynamic_rain_ratio and uking_dynamic_rainfall and picks the
    // environment unit's shader variation (2 when the first scene's _52e0 flag is set, else rain > 0).
    void setRainRatio(f32 ratio, f32 rainfall);
    // 0x7100f2fe38 (CSV Graphics::getDynamicCloudRatio; it sets the value): sets uking_dynamic_cloud_ratio to
    // 1 - ratio clamped to [0, 1].
    void setDynamicCloudRatio(f32 ratio);
    // 0x7100f2ff08 (placeholder name; CSV Graphics::__auto7): stores ratio at 0xe88, passes 1 - scale to the
    // object at 0x370 and sets the depth / world shadow uking_dynamic parameters.
    void sub_7100F2FF08(f32 ratio, f32 scale);
    // Placeholder name: the camera values 0x7100f30178 passes to sub_7100F309FC (camera +0x6c, the projection's
    // fovy from its virtual getter at +0x30, Graphics +0x358).
    struct DofCameraArg {
        f32 focus_distance;
        f32 fovy;
        f32 f_number;
    };
    // 0x7100f309fc (placeholder name; CSV Graphics::__auto8): computes the near / far blur ranges of the depth of
    // field from the camera and writes them to the first scene's agl::pfx::DepthOfField. False if the fovy is ~0.
    bool sub_7100F309FC(const DofCameraArg& arg);
    // 0x7100f2faac (placeholder name): sets uking_dynamic_exposure unless the byte at 0xf5a is 4 (force skips the test).
    void sub_7100F2FAAC(f32 exposure, bool force);

    // inline-only in the original; name is a guess: the same lock / searchMaterialParamIndex /
    // setMaterialParamF32 sequence is inlined in 0x7100f2fb6c, 0x7100f2fc24, 0x7100f2fcdc, 0x7100f2fe38,
    // 0x7100f2ff08, 0x7100f2faac and 0x7100f2e5cc.
    // inline-only in the original; name is a guess (searches a material parameter by name and sets it; part of
    // setEnvMaterialParamF32 below, same functions).
    static void setMaterialParamF32(gsys::ModelUnit* unit, s32 material, const sead::SafeString& name,
                                    f32 value) {
        const s32 index = unit->searchMaterialParamIndex(material, name);
        if (index != -1)
            unit->setMaterialParamF32(material, index, value);
    }
    void setEnvMaterialParamF32(const char* name, f32 value) {
        auto lock = sead::makeScopedLock(_ed8);
        setMaterialParamF32(_ea8, _f58, name, value);
    }
    // 0x7100f2e1e8 (name is a guess): the sead::SafeString overload of the setter above.
    void setEnvMaterialParamF32(const sead::SafeString& name, f32 value);
    // inline-only in the original; name is a guess: the Colour4f twin of setMaterialParamF32, inlined
    // in 0x7100f300d0 (the only user in this TU).
    static void setMaterialParamColor4f(gsys::ModelUnit* unit, s32 material,
                                        const sead::SafeString& name,
                                        const sead::Color4f& value) {
        const s32 index = unit->searchMaterialParamIndex(material, name);
        if (index != -1)
            unit->setMaterialParamColor4f(material, index, value);
    }

    // 0x7100f35e54: settings currently registered by the rune / magnesis managers.
    Unk_7100f35df8* sub_7100F35E54() const;

    // Placeholder name: read by Unk_710260af28::sub_7100F1D9B4 (0x7100f1d9b4) as the modulus of the
    // uk_special_effect_A wrap.
    f32 getSpecialEffectAWrapMaybe() const { return _f9c; }

    // 0x7100f35fa4 (lane2 request, s49; placeholder name): sets bit 12 (`second`) or 11 (not `second`) of
    // `_284` to `value`, then marks the settings dirty (`_280 |= 1`).
    void sub_7100F35FA4(bool value, bool second);

    // Graphics +0xab0, constructed at 0x7100f26b00. The five samplers at +0x18
    // and the mapping fields below are read by the height-map sampling path.
    struct Unk_ab0 : public sead::hostio::Node {
        bool sub_7100F29EB4(f32* height, const sead::Vector2f& pos);

        u8 _8[0x18 - 0x8];
        agl::TextureSampler mSamplers[5];
        u8 _748[0x750 - 0x748];
        f32 mMapSize;
        f32 _754;
        f32 mHeightScale;
        u8 _75c[0x76c - 0x75c];
        sead::Vector2f mMapCenter;
        u8 _774[0xe10 - 0x774];
        s32 mCurrentSampler;
        u8 _e14[0xe48 - 0xe14];
        u32 _e48;
    };

    // Placeholder name: the block that Graphics + 0xaa8 points to; ksys::act::sub_7100EEAFDC casts along the vector at
    // 0x7f8 (a down direction).
    struct Unk_aa8 {
        u8 _0[0x7f8];
        /* 0x7f8 */ sead::Vector3f _7f8;
    };
    Unk_aa8* getUnk_aa8() const { return _aa8; }

    // The object at 0xac0. Only SkyMgr::sub_71010E35D8 reads it: it copies the parameter block at
    // +0x18 through a temporary, writes the dusk/dawn blend factor at +0x30 and sets bit 1 of the
    // flag at +0xa0 while the blend is active.
    struct Unk_ac0 {
        struct Params {
            u32 _0;               // 0x18
            u8 _4[8];             // 0x1c
            sead::Vector3f _c;    // 0x24
            f32 _18;              // 0x30
            u8 _1c[0xc];          // 0x34
            sead::Color4f _28;    // 0x40
            u32 _38;              // 0x50
        };
        static_assert(sizeof(Params) == 0x3c);

        u8 _0[0x18];
        Params mParams;  // 0x18
        u8 _54[0x4c];
        u32 _a0;  // 0xa0
    };
    static_assert(sizeof(Unk_ac0) == 0xa4);
    Unk_ac0* getSkyEnvMaybe() const { return _ac0; }

    // Only a pointer to the (separately allocated) shadow settings is modeled.
    ksys::gfx::LocationalLightMgr* getLocationalLightMgr() const { return _aa0; }
    Unk_7100efd9b8* getFarModelRendererMaybe() const { return _3a8; }
    GrudgeRenderer* getGrudgeRendererMaybe() const { return _3a0; }
    Unk_a98* getUnk_a98() const { return _a98; }
    Unk_7100f185a4* getMapRendererMaybe() const { return _388; }
    // The noise gauge the main screen bakes and draws through (0x7100f208e4 / 0x7100f20c88).
    gfx::NoiseGauge* getNoiseGaugeMaybe() const { return _390; }
    Unk_ab0* getUnk_ab0() const { return _ab0; }

    // Read by ScreenAppMapDungeon::m95: nonzero skips the scale-factor conversion of the map screen
    // coordinates. The per-frame update 0x7100f2f2c8 latches the value of sub_7100F2AFE8's byte
    // (_f5d) here, so normally it is 0.
    u8 get_b5e() const { return _f5e; }

public:
    // Placeholder: the object at 0x118 (SkyMgr::sub_71010E37C8 copies the sky light direction to _1c0).
    struct Unk_118 {
        u8 _0[0x1c0];
        sead::Vector3f _1c0;
    };

private:
    // The primary vptr (the class has a virtual destructor) and the model-scene pass callback's vptr
    // (0x71024f45c0 + 0xf0) occupy 0x0 and 0x8; the unknown block follows them.
    u8 _10[0x19 - 0x10];
    // Pass-view-projection index stored for the procedural draw (drawProceduralPassMaybe).
    u8 _19;
    u8 _1a[0xf8 - 0x1a];

public:
    // SEAD_SINGLETON_DISPOSER expansion (createInstance 0x7100f2a1d0, disposer vtable 0x71024f45a0).
    class SingletonDisposer_ : public sead::IDisposer {
    public:
        using sead::IDisposer::IDisposer;
        virtual ~SingletonDisposer_();

        static SingletonDisposer_* sStaticDisposer;
    };

private:
    u32 mSingletonDisposerBuf_[sizeof(SingletonDisposer_) / sizeof(u32)];

public:
    /* 0x118 */ Unk_118* _118;

private:
    u8 _120[0x150 - 0x120];

public:
    // 0x150: the model scenes (lane5 s3: SystemApplyEnvSetAction::enter_).
    sead::PtrArray<gsys::ModelScene> mModelScenes;

private:
    u8 _160[0x170 - 0x160];
    // 0x7100f2b3dc iterates this array and pushes each element into a PtrArray.
    s32 _170;
    s32 _174;
    void** _178;
    u8 _180[0x280 - 0x180];
    u32 _280;
    sead::BitFlag32 _284;
    u8 _288[0x360 - 0x288];

public:
    // The player link (set by ksys::setPlayerLink).
    /* 0x360 */ ksys::act::PlayerLink* _360;

private:
    u8 _368[0x370 - 0x368];
    Unk_710129421c* _370;

public:
    // Read by the shooting-star grid predicate at 10D103C.
    Unk_378* _378;

private:
    u8 _380[0x388 - 0x380];
    Unk_7100f185a4* _388;
    gfx::NoiseGauge* _390;
    Unk_7101293bac* _398;
    GrudgeRenderer* _3a0;
    Unk_7100efd9b8* _3a8;
    agl::cull::OcclusionQueryDrawer* _3b0;
    u8 _3b8[0x660 - 0x3b8];
    s32 mLensFlarePreset;  // 0x7100f2ddf0 compares and updates this preset index.
    u8 _664[0x668 - 0x664];
    Unk_668* _668;
    u8 _670[0xa98 - 0x670];
    Unk_a98* _a98;
    ksys::gfx::LocationalLightMgr* _aa0;
    Unk_aa8* _aa8;
    Unk_ab0* _ab0;
    // EnvMgr reset/update and mode dispatch access this native field directly.
    friend class ksys::world::EnvMgr;
    Unk_71012a20e0* _ab8;
    // 0xac0: the sky environment parameters (only SkyMgr::sub_71010E35D8 reads them).
    Unk_ac0* _ac0;
    u8 _ac8[0xad8 - 0xac8];
    // Pointer whose byte +0x508 is set by sub_7100F35DE8.
    gsys::CopyLayerTexture* _ad8;
    Unk_7100f35df8* _ae0;
    u8 _ae8[0xb38 - 0xae8];
    Unk_710129175c* _b38;
    u8 _b40[0xb70 - 0xb40];
    // 0x7100f3592c: writes _b70->_110.
    Unk_b70* _b70;
    u8 _b78[0xe08 - 0xb78];

public:
    // 0xe08 (lane1 s44): the camera of the graphics system (read by SkyMgr::sub_71010E4EE0).
    sead::Camera* _e08;
    // 0xf32ac8 (CSV Graphics::__auto12; placeholder name): stores the camera at 0xe08 and an unknown object at 0xe10
    // (MainFieldDungeonStage::initForStageGen passes its members at 0x150 / 0x158).
    void sub_7100F32AC8(sead::Camera* camera, void* unk);

private:
    void* _e10;
    u8 _e18[0xe80 - 0xe18];
    f32 _e80;
    f32 _e84;
    f32 _e88;
    f32 _e8c;
    u8 _e90[0xe98 - 0xe90];
    // A model unit whose shader variation setRainRatio (0x7100f2fcdc) picks.
    gsys::ModelUnit* _e98;
    u8 _ea0[0xea8 - 0xea0];
    // The environment model unit whose material parameters the uking_dynamic_* setters change.
    gsys::ModelUnit* _ea8;
    u8 _eb0[0xed8 - 0xeb0];
    sead::CriticalSection _ed8;
    // Lock for the map kind below (placeholder name).
    sead::CriticalSection _f18;
    // Material index used by setEnvMaterialParamF32.
    s8 _f58;
    u8 _f59;  // map kind (Graphics::sub_7100F2AF70)
    u8 _f5a;
    u8 _f5b;  // sub_7100F2AFAC
    u8 _f5c;
    u8 _f5d;  // sub_7100F2AFE8
    u8 _f5e;
    u8 _f5f;  // sub_7100F2B024
    // Placeholder name: the modulus of the uk_special_effect_A wrap (Unk_710260af28::sub_7100F1D9B4
    // 0x7100f1d9b4 passes it as the second argument of fmodf).
    u8 _f60[0xf9c - 0xf60];
    /* 0xf9c */ f32 _f9c;
    // The rest of the 0xfe8-byte instance is not modelled.
    u8 _fa0[0xfe8 - 0xfa0];

public:
    // 0x7100f2a754 (declaration only). The original primary vtable 0x71024f45c0 has the ten
    // gsys::IResourceEditorCallback overrides at +0x10 and the destructor pair after them; only the
    // destructor and editorCallback6 (0x7100f2e06c) are modelled so far.
    // editorCallback0 is the vtable's key function and stays declared only: defining it here would emit
    // our own partial vtable, which does not have the original's other three base tables.
    void editorCallback0(const gsys::IResourceEditorCallback::Arg& arg) override;
    void editorCallback1(const gsys::IResourceEditorCallback::Arg& arg) override;
    void getModelFmdbPath(const char** path, const gsys::IResourceEditorCallback::Arg& arg) override;
    void editorCallback3(const gsys::IResourceEditorCallback::Arg& arg) override;
    void editorCallback4(const gsys::IResourceEditorCallback::Arg& arg) override;
    void editorCallback5(const gsys::IResourceEditorCallback::Arg& arg) override;
    // The CSV's former placeholder name sub_7100F2E06C (0x7100f2e06c).
    void editorCallback6(const gsys::IResourceEditorCallback::Arg& arg) override;
    void editorCallback7(const gsys::IResourceEditorCallback::Arg& arg) override;
    void editorCallback8(const gsys::IResourceEditorCallback::Arg& arg) override;
    void editorCallback9(const gsys::IResourceEditorCallback::Arg& arg) override;
    Graphics();
    virtual ~Graphics();

    // The model-scene pass callback overrides. Graphics is gsys::IModelScenePassCallback at +8; the
    // primary vtable holds each override's implementation (m12-m25) and the +8 table the adjusted
    // copies (m28-m41). Slots m12-m15: 0x7100f2e0a4 / 0x7100f2e0b4 / 0x7100f2e0c4 / 0x7100f2e0d4,
    // their +8 copies 0x7100f2e0ac / 0x7100f2e0bc / 0x7100f2e0cc / 0x7100f2e0e4. The methods read
    // the same members (the light manager at 0xaa0, the occlusion query drawer at 0x3b0).
    void initializeModelSceneEnvObj(gsys::ModelScene* scene,
                                    agl::env::EnvObjBuffer::AllocateArg* arg) override;
    void bindModelScene(gsys::ModelScene* scene) override;
    void unbindModelScene(gsys::ModelScene* scene) override;
    void clearModelSceneQueue() override;
    // The remaining model-scene pass overrides, in the original's primary-vtable order (slots m16-m21;
    // declaration only, so the primary table and the +8 table keep the original's slot layout).
    void calcModelSceneFrame(s32 view, gsys::ModelRenderContext* context) override;
    void calcModelSceneCalcRenderView(s32 view, gsys::ModelScene* scene,
                                      gsys::ModelRenderContext* context) override;
    void drawModelSceneBG(agl::DrawContext* draw_context, s32 pass, gsys::ModelScene* scene,
                          gsys::ModelRenderContext* context) override;
    void drawModelSceneOpa(agl::DrawContext* draw_context, s32 pass, gsys::ModelScene* scene,
                           gsys::ModelRenderContext* context) override;
    void drawModelSceneXlu(agl::DrawContext* draw_context, s32 pass, gsys::ModelScene* scene,
                           gsys::ModelRenderContext* context) override;
    void drawModelScenePfx(agl::DrawContext* draw_context, s32 pass, gsys::ModelScene* scene,
                           gsys::ModelRenderContext* context) override;
    // 0x7100f34de4 (slot m22): the final-image pass draws the debug geometry of the occlusion query
    // drawer and the four renderer blocks, for pass 0 only.
    void drawModelSceneFinalImage(agl::DrawContext* draw_context, s32 pass, gsys::ModelScene* scene,
                                  gsys::ModelRenderContext* context) override;
    // 0x7100f34e8c (slot m23; +8 copy 0x7100f34ed4): refreshes the view's records in the grid and
    // model renderer blocks.
    void calcModelSceneViewGPU(gsys::ModelRenderContext* context) override;
    // 0x7100f34f1c (IModelProcedural's +0x298 virtual; its _ZThn16_ thunk is 0x7100f35028): for
    // passes 2..7 stores `_19` in the procedural draw's render cache, for passes 0 / 1 invalidates
    // the first scene's GBuffer write cache, and for pass 8 stores the particle editor's value.
    virtual void drawProceduralPassMaybe(s32 pass, gsys::ModelRenderCache* cache) const;
    // 0x7100f35f48 (slot m25): empty in the original.
    void resetModelSceneHostIO(gsys::ModelRenderContext* context) override;

    // inline-only in the original; name is a guess: the map states 3 / 6 / 7 select the
    // pass-view-projection index for the procedural draw.
    bool usesPassViewProjMaybe() const {
        if (_f5a > 7)
            return false;
        return ((1u << _f5a) & 0xc8) != 0;
    }

    // The map state byte compared with 4 (sub_7100F2FAAC) and 7 (PlacementMgr::requestDraw).
    u8 getMapStateMaybe() const { return _f5a; }
};
KSYS_CHECK_SIZE_NX150(Graphics, 0xfe8);

namespace agl {
class ShaderProgramArchive;
}

// 0x710260b150 (singleton, vtable 0x71024f4cc0, 0x2f0 bytes, created by ksys::InitializeApp): the
// map footprint pass; GraphicsContext at +0x30, Viewport at +0xa8, OrthoProjection at +0xd0, the
// shader archive at +0x1b0. Only the shader setup Graphics::init runs is modelled.
class Unk_71024f4cc0 {
public:
    // 0x7100f37b5c: the "map_visit_mark" program's uniform block, uniform names, image location
    // and attribute names.
    void initShaderProgram(agl::ShaderProgramArchive* archive, sead::Heap* heap);
};

namespace ksys::gfx {
// 0x7101294a7c (called by Graphics::init): sets up the "light_analyzer" program's shader storage
// block, its five sampler locations and its "cContext" uniform block.
void sub_7101294A7C(agl::ShaderProgramArchive* archive, sead::Heap* heap);
// 0x7101288884 (called by Graphics::init): the "depth_analyzer" program's four-data storage block,
// four sampler locations and its cContext uniform block.
void sub_7101288884(agl::ShaderProgramArchive* archive, sead::Heap* heap);
// 0x71012a3240 (called by Graphics::init): the "star_render" program's Context and UnitInfo uniforms.
void sub_71012A3240(agl::ShaderProgramArchive* archive, sead::Heap* heap);
// 0x7101291958 (called by Graphics::init): the "analyze_actor" program's five texture sampler
// locations and its cContext uniform block.
void sub_7101291958(agl::ShaderProgramArchive* archive, sead::Heap* heap);
// 0x710129f984 (called by Graphics::init): the "preshading_filter" program's four sampler locations
// (indices 2/0/1/3) and its cContext uniform block.
void sub_710129F984(agl::ShaderProgramArchive* archive, sead::Heap* heap);

// One preshading-filter target (0x6b8 bytes): a texture sampler, a render buffer, two colour render
// targets, a depth target and a uniform block.
struct PreshadingTargetMaybe {
    agl::TextureSampler _0;
    agl::RenderBuffer _170;
    agl::RenderTargetColor _1d8;
    agl::RenderTargetColor _350;
    agl::RenderTargetDepth _4c8;
    agl::UniformBlock _640;
};
static_assert(sizeof(PreshadingTargetMaybe) == 0x6b8);

// 0x71012a1ffc: allocates `count` targets and stores them in `buffer`.
bool sub_71012A1FFC(sead::Buffer<PreshadingTargetMaybe>* buffer, s32 count, sead::Heap* heap,
                    s32 alignment);

// Placeholder: the 0x270-byte preshading filter object (constructor 0x710129f834); Graphics::SystemStuff
// allocates it at Graphics + 0x380.
class PreshadingFilterMaybe {
public:
    // 0x710129faa4: allocates `count` targets, declares their uniform blocks, finds the
    // "preshading_filter" program and sets up the debug texture page.
    void initialize(u32 count, agl::ShaderProgramArchive* archive, sead::Heap* heap);

private:
    u8 _0[0x10];
    sead::Buffer<PreshadingTargetMaybe> mTargets;
    agl::utl::DebugTexturePage mPage;
    agl::ShaderProgram* mProgram;
    u8 _268[8];
};
KSYS_CHECK_SIZE_NX150(PreshadingFilterMaybe, 0x270);
}  // namespace ksys::gfx
