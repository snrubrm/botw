#pragma once
#include <common/aglGPUMemAddr.h>
#include <nn/gfx/gfx_ResTextureData.h>
#include <common/aglGPUMemBlock.h>
#include <common/aglIndexStream.h>
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglTextureSampler.h>
#include <common/aglUniformBlock.h>
#include <common/aglVertexAttribute.h>
#include <common/aglVertexBuffer.h>
#include <utility/aglDebugTexturePage.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <gfx/seadGraphicsContext.h>
#include <gfx/seadViewport.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include <cstddef>

namespace ksys::phys { class ContactLayerCollisionInfoGroup; }

class Unk_7102503ac0;

// Grass initialization at 0x710114eab0 allocates this 0xbe0-byte object at +0x28.
// Constructor 0x7101063728 installs table 0x7102503a50, which has only D1/D0 slots.
// No class name, namespace or nontrivial base is known.
class Unk_7102503a50 {
public:
    // Texture storage initialized by 0x7101061024; 0x71010615d4 uses a 0x460 stride.
    struct Cache {
        u32 _0;
        u32 mDimension;
        agl::GPUMemVoidAddr mAddress;               // +8
        agl::TextureData* mTextureData;              // +20
        agl::TextureSampler mSampler;               // +28
        nn::gfx::ResTextureData mResTexture;        // +198
        agl::RenderBuffer mRenderBuffer;            // +238
        agl::RenderTargetColor mRenderTarget;        // +2a0
        sead::Viewport mViewport;                   // +418
        sead::Vector3f mCenter;                     // +440
        f32 _44c;
        u64 _450;
        u64 _458;
        void initialize(sead::Heap* heap, u32 dimension, agl::TextureFormat format, u32 flags);
    };
    static_assert(sizeof(Cache) == 0x460);
    static_assert(offsetof(Cache, mAddress) == 8);
    static_assert(offsetof(Cache, mCenter) == 0x440);

    // Constructor 0x710106a7a4 runs on Record +0x20 and constructs three caches.
    struct NearCaches {
        NearCaches();                              //106a7a4
        void initialize(sead::Heap* heap, u32 dimension);
        u32 _0;                                    // queried as ==0 to select other cache
        u8 _4[4];
        Cache mCaches[3];                           // +8,+468,+8c8
        u32 _d28;
        u8 _d2c[4];
    };
    static_assert(sizeof(NearCaches) == 0xd30);

    // 0x71010642ac allocates count * 0x14 bytes and puts each entry in the free array.
    struct Event {
        sead::Vector2f mPosition;
        f32 mRadius;
        f32 mValue;
        u8 mKind;
        u8 mAge;
        u8 _12[2];
    };
    static_assert(sizeof(Event) == 0x14);
    static_assert(offsetof(Event, mRadius) == 8);
    static_assert(offsetof(Event, mAge) == 0x11);

    // Constructed within Record at +0x7258; initialized by 0x71010642ac.
    struct EventPool {
        void sub_71010642AC(s32 count, sead::Heap* heap);
        void process(Unk_7102503ac0* callback);

        sead::CriticalSection mCriticalSection;
        sead::Buffer<Event> mEvents;
        sead::PtrArray<Event> mFreeEvents;
        sead::PtrArray<Event> mActiveEvents;
        sead::PtrArray<Event> mRetiredEvents;
    };
    static_assert(sizeof(EventPool) == 0x80);
    static_assert(offsetof(EventPool, mEvents) == 0x40);
    static_assert(offsetof(EventPool, mFreeEvents) == 0x50);
    static_assert(offsetof(EventPool, mActiveEvents) == 0x60);
    static_assert(offsetof(EventPool, mRetiredEvents) == 0x70);

    // Initializer 0x7101063904 allocates records with an array cookie and a 0x7448 stride.
    // Constructor 0x710106a5d4 and destructor 0x710106ab30 remain declared only.
    struct Record {
        Record();                                  //106a5d4
        ~Record();                                 //106ab30
        sead::Vector3f mPosition;
        u8 _c[0x1c - 0xc];
        // Bit 0 is cleared by 0x71011509ec.
        u32 _1c;
        NearCaches mNear;                          // +20
        Cache mFar;                                // +d50
        f32 mFarRadius;                            // +11b0
        sead::Vector3f mFarBoundsCenter;            // +11b4
        u8 _11c0[0x30];
        u8 _11f0[0x160];  // Uniform-block owner with table 0x7102503a30; lifetime unresolved.
        u8 _1350[0x70e0 - 0x1350];                 // real ctor106a914, size5d90; unresolved interior
        agl::UniformBlock _70e0;
        u8 _7158[8];
        bool _7160;
        u8 _7161[7];
        agl::UniformBlock _7168;
        agl::UniformBlock _71e0;
        EventPool mEventPool;                      // +7258
        u8 _72d8[0x10];
        u8 _72e8[0x160];  // Second instance of the same uniform-block owner.
    };
    static_assert(sizeof(Record) == 0x7448);
    static_assert(offsetof(Record, mFar) == 0xd50);
    static_assert(offsetof(Record, mFarRadius) == 0x11b0);
    static_assert(offsetof(Record, _11f0) == 0x11f0);
    static_assert(offsetof(Record, _70e0) == 0x70e0);
    static_assert(offsetof(Record, mEventPool) == 0x7258);
    static_assert(offsetof(Record, _72e8) == 0x72e8);

    Unk_7102503a50();                                //1063728
    virtual ~Unk_7102503a50();                       //1063808
    struct InitArg { sead::Heap* mHeap; s32 mCount; };
    void sub_7101063904(const InitArg* arg);
    f32 sub_7101069760(const sead::Vector2f* position);
    f32 sub_71010699D0(const sead::Vector2f* position);
    f32 sub_7101069C44(const sead::Vector2f* position);
    u32 sub_7101069DB8(const sead::Vector2f* position, f32 radius);
    bool queueEvent(f32 radius, f32 value, s32 kind, const sead::Vector2f* position, bool flag);
    bool sub_710106A2C4();
    // 0x710106a0c8 (unnamed in the CSV): walks the near-set records, checks `position` against each
    // record's near position (a/2 as the extent) and, on a hit, appends the position to the record's
    // buffer under its critical section. b is the radius. Called by Core::Grass::sub_7101150FCC.
    bool sub_710106A0C8(f32 a, f32 b, const sead::Vector2f* position);
    // 0x71010657dc (unnamed in the CSV): writes the grass fade of the entry nearest to `pos`.
    void sub_71010657DC(const sead::Vector3f* pos, f32 a, f32 b);
    // 0x71010658e8 (unnamed in the CSV): stores `entry` and the position in the record for `index`
    // (the entry type is Core::Grass::Entry, which this header cannot see, so the pointer is void).
    void sub_71010658E8(s32 index, void* entry, const sead::Vector3f& pos);

    sead::Heap* mHeap;                              // +8
    sead::Buffer<Record> mRecords;                  // +10
    u32 _20;
    f32 mNearRadius;                                // +24, ctor32, queries/producer verified
    f32 _28;
    f32 _2c;
    agl::utl::DebugTexturePage mDebugPages[2];         // +30,+270
    u32 _4b0;
    u16 _4b4;
    u8 _4b6[2];
    ksys::phys::ContactLayerCollisionInfoGroup* _4b8;
    ksys::phys::ContactLayerCollisionInfoGroup* _4c0;
    sead::GraphicsContext mGraphicsContexts[3];       // +4c8,+53c,+5b0
    u8 _624[4];
    u8 _628[0x38];                                 // genuine GPUMemBlockT, exact T unresolved
    u8 _660[0x38];                                 // genuine GPUMemBlockT, exact T unresolved
    agl::VertexBuffer mVertexBuffer;                 // +698
    agl::IndexStream mIndexStream;                   // +7b8
    agl::VertexAttribute mVertexAttribute;           // +818
    u8 _9f8[0x1e0];
    f32 _bd8;
    u8 _bdc[4];
};
static_assert(sizeof(Unk_7102503a50) == 0xbe0);

// The stack object in 0x71010658e8 installs table 0x7102503ac0 and copies its
// center to +8. The table has these three methods and no virtual destructor.
class Unk_7102503ac0 {
public:
    virtual void update(Unk_7102503a50::Event* event);
    virtual bool shouldRetire(Unk_7102503a50::Event* event);
    virtual bool shouldDiscard(Unk_7102503a50::Event* event);

    sead::Vector2f mCenter;
};
static_assert(sizeof(Unk_7102503ac0) == 0x10);
static_assert(offsetof(Unk_7102503ac0, mCenter) == 8);
