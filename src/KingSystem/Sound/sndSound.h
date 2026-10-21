#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"
#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <container/seadOffsetList.h>
#include <nn/util/util_IntrusiveList.h>
#include <container/seadObjArray.h>
#include <container/seadObjList.h>
#include <aal/aalHandle.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadAtomic.h>
#include <container/seadBuffer.h>
#include <prim/seadEnum.h>
#include <aal/aalGroupLimiter.h>
#include <aal/aalGroup.h>
#include <aal/aalListener.h>
#include <aal/aalListenerPoser.h>
#include <container/seadFreeList.h>
#include <aal/aalTimedFader.h>
#include <aal/aalUnifiablePosition.h>
#include <aal/aalAssetInfo.h>
#include <gfx/seadCamera.h>
#include <gfx/seadGraphicsContext.h>
#include <gfx/seadPrimitiveRenderer.h>
#include <gfx/seadProjection.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/System/DebugMessage.h"
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Sound/sndMiiSound.h"

namespace uking { class StatisticsMgr; }
namespace ksys::tera { class System; }
namespace ksys::phys { class SphereRigidBody; }

namespace ksys::snd {

// Named native zero-argument utility: classifies the current StageInfo map for sound.
s32 getEnvTypeForXlink();

// Placeholder name: a 46-entry SEAD_ENUM of voice kinds (text_ at 0x710105ec08; eft::sub_710105DFA4 emits the
// SLink named by it).
SEAD_ENUM(Unk_710105ec08, Greeting, CallFar, TalkPositive, TalkDeny, QuestionNormal, QuestionAngry, QuestionSurprise, LaughS, LaughL, Happy, Sad, Sigh, Angry, Shitauchi, Think, Trouble, Ease, Notice, SurpriseS, SurpriseM, SurpriseL, Admiration, Understand, Chat, Humming, CustomSavotta, CustomSavaaq, CustomSavsaaba, CustomVasaaq, Runaway, Tired, Sleep, Wakeup, LaughBad, Run, Cry, BecomeAssasin, SakuradaCM1, SakuradaCM2, SakuradaCM3, Scare, Unconscious, Painful, Work, WorkHeavy, Bukubuku)

class SoundResource {
    // Resource manager initialization assigns this resource heap to its overlay arena.
    friend struct ResourceManager;
    SEAD_SINGLETON_DISPOSER(SoundResource)
    SoundResource() = default;
    virtual ~SoundResource();

public:
    void init(sead::Heap* heap, sead::Heap* debug_heap, bool extra_large);
    sead::Heap* getSoundDebugHeap() const { return mSoundDebugHeap; }

private:
    sead::Heap* mSoundResourceHeap = nullptr;
    sead::Heap* _30 = nullptr;  // TODO find out what this does
    sead::Heap* mSoundDebugHeap = nullptr;
};
KSYS_CHECK_SIZE_NX150(SoundResource, 0x40);

}  // namespace ksys::snd

namespace sead {
class DirectResource;
class Thread;
}

namespace aal {
class AudioResource;
class Shape;
class Emitter;
class SpeakerBalanceUnifier;

// The primary base of ResourceManager (vtable at 0x7102502a68; the object's three vtable pointers at +0 / +0x8 /
// +0x10 come from one group). Its two named virtuals are IAssetList::isDirty / clearDirty (upstream's IDB names
// for 0x710105947c / 0x7101059484). The interface belongs in lib/aal (requested from the library worker); it is
// declared here so that the resource manager's hierarchy can be modelled.
class IAssetList {
public:
    virtual ~IAssetList() = default;
    virtual void sub_7101059468() = 0;
    virtual bool sub_710105946C() = 0;
    virtual bool sub_7101059474() = 0;
    virtual bool isDirty() const = 0;
    virtual void clearDirty() = 0;
    virtual bool sub_7101059458() = 0;
};
}  // namespace aal

namespace ksys::act {
class ActorCreator;
}

namespace xlink2 {
class HandleSLink;
class IUser;
class System;
class UserInstanceSLink;
}

namespace ksys::res {
class Handle;
}

namespace ksys {
class OverlayArena;
}

namespace ksys::snd {
class Unk_710251af10;
class Unk_710251af30;

// Placeholder name (SoundMgr::_2a0; the final output measure user, TU 0x71012c629c .. 0x71012c7350). Only the
// methods SoundMgr calls are declared.
class Unk_SoundMgr2a0 {
public:
    // 0x71012c629c (declared only): per-frame update (SoundMgr::calc).
    void sub_71012C629C();
    // 0x71012c6dc4 (declared only): activates the final output measure (Sound::init2).
    void sub_71012C6DC4();
};
}  // namespace ksys::snd

namespace ksys::act {
class Actor;
class ActorCreator;
}

namespace uking::act {
class EnvSeEmitPoint;
class SoundProxy;
}

// gameUnkRttiPlaceholders.h (the bars resource).
class ResourceBars;

namespace ksys::snd {

class Unk_7102502950;
class FxMgr;
class ExpressionSoundCtrl;


f32 sub_710105E3A4();
const char* sub_710105E7B4(bool* flag);
void sub_710105E534(sead::PtrArray<aal::Group>* groups, aal::Group* excluded, aal::Group* root);
void sub_710105E5CC(sead::PtrArray<aal::Group>* groups,
                   const sead::PtrArray<aal::Group>* excluded, aal::Group* root);
void sub_710105E614(sead::PtrArray<aal::Group>* groups,
                   const sead::PtrArray<aal::Group>* excluded, aal::Group* group);
s32 sub_710105E6CC(s32 position, const aal::AssetInfo* asset);
s32 sub_710105E75C(const aal::AssetInfo::LoopInfo* loop, s32 position, s32 offset);

struct Unk_SoundMgr30;
class OcclusionMgr;

// Only the interface needed by the UI sound wrapper is recovered.
class UiSoundMgr {
public:
    UiSoundMgr();
    virtual ~UiSoundMgr();
    void sub_710105D0E4(sead::Heap* heap);
    void sub_710105D0E8();
    // 0x710105d23c: requests its GetItemSound actor outside the TitleMenu map.
    void sub_710105D23C(sead::Heap* heap, act::ActorCreator* creator);
    void sub_710105D308();
    // 0x710105d1d0 (placeholder name): creates the user instance at _20 from the sound resource manager's
    // embedded asset info reader.
    void sub_710105D1D0(sead::Heap* heap);
    void sub_710105D9F8(aal::SoundSource* source);
    // 0x710105d5ac: stops the previous HeartUp sound and emits mc_HeartUp (`mode` picks the handle).
    bool sub_710105D5AC(const s32* mode);
    // 0x710105d7b0: mutes _38 and emits mc_ExtraHeartUp (mode 0 only).
    bool sub_710105D7B0(const s32* mode);
    void sub_710105D844(const s32* mode);
    // 0x710105d330: emits the SLink sound `label` through the user instance at +0x20; the handle is copied to
    // `handle` if given. Returns whether the emitted event is alive.
    bool playSound(const sead::SafeString& label, xlink2::HandleSLink* handle);
    // 0x710105d3bc (CSV uiSoundMgr::emitGetItemSound; declared only): emits the "get item" sound `label`.
    bool emitGetItemSound(const sead::SafeString& label);

    /* 0x08 */ act::BaseProcHandle _8;
    /* 0x18 */ act::Actor* _18 = nullptr;
    /* 0x20 */ xlink2::UserInstanceSLink* _20 = nullptr;
    /* 0x28 */ xlink2::HandleSLink _28;
    /* 0x38 */ xlink2::HandleSLink _38;
    /* 0x48 */ aal::Handle _48;
    /* 0x58 */ aal::TimedFader _58{1.0f, aal::FadeCurveType::Square, 1.0f};
    /* 0x80 */ u8 _80 = 0;
    /* 0x84 */ u32 _84 = 0;
    /* 0x88 */ DebugMessage _88;
    void* _118 = nullptr;
    void* _120 = nullptr;
};
KSYS_CHECK_SIZE_NX150(UiSoundMgr, 0x128);

// Placeholder name (SoundMgr::_38::_30). Holds the aal::SpeakerBalanceUnifier objects at +0x68 (count at +0x60,
// guarded by a CriticalSection at +0x20); shapes are registered with the one picked by a size threshold.
class SpeakerBalanceUnifierMgr {
public:
    // 0x7101027bbc (empty in the release build): per-frame update (Unk_SoundMgr38::sub_710102C098).
    void sub_7101027BBC();
    // 0x7101027d4c: adds `shape` to the unifier chosen by `size` (3 thresholds).
    void sub_7101027D4C(f32 size, aal::Shape* shape);
    // 0x7101027e0c: removes `shape` from every unifier.
    void sub_7101027E0C(aal::Shape* shape);
    // 0x7101027e90 (declared only): emits the SLink sound for `type` (1 or 2) picked by `size` and
    // attaches `shape` to its sound source.
    xlink2::HandleSLink sub_7101027E90(f32 size, int type, aal::Shape* shape);
    void sub_7101027CE8();
    // 0x7101027bc0 (placeholder name): requests the "BoxWaterSound" actor into mHandle unless it exists.
    void sub_7101027BC0(sead::Heap* heap, act::ActorCreator* creator);
    // 0x7101027bf4: empty in the release build (Unk_SoundMgr38::sub_710102AE50).
    void sub_7101027BF4();
    // 0x7101027bf8 (declared only)
    void sub_7101027BF8();
    static sead::SafeString sUnk_7102610618[4];
    static sead::SafeString sUnk_7102610658[4];

    // 0x7102501140: the sizes that separate the four unifiers.
    static f32 sSizeThresholds[3];

    // 0x7101027554 (declared only)
    SpeakerBalanceUnifierMgr();
    virtual ~SpeakerBalanceUnifierMgr();
    // 0x71010276f0 (declared only): called with the heap right after construction.
    void sub_71010276F0(sead::Heap* heap);

    // 0x710102780c obtains this actor through the handle; 0x7101027ce8 clears both.
    act::BaseProcHandle mHandle;
    act::Actor* mActor = nullptr;
    /* 0x20 */ sead::CriticalSection mCS;
    /* 0x60 */ sead::PtrArray<aal::SpeakerBalanceUnifier> mUnifiers;
    // 0x7101027554 (the constructor): the count of the unifiers and three (pointer, value) pairs.
    /* 0x70 */ u32 _70 = 0;
    /* 0x74 */ u32 _74 = 0;
    /* 0x78 */ u32 _78 = 0;
    /* 0x80 */ void* _80 = nullptr;
    /* 0x88 */ u32 _88 = 0;
    /* 0x90 */ void* _90 = nullptr;
    /* 0x98 */ u32 _98 = 0;
    /* 0xa0 */ void* _a0 = nullptr;
    /* 0xa8 */ u32 _a8 = 0;
};

// Placeholder name (SoundMgr::_38::_28; lane5 s6): the occlusion volume state of the sound manager, used by the
// SoundOcclusionTag* actions (the sound is occluded while the player is inside the box set by sub_7101037ED8).
class Unk_SoundMgr38_28 {
public:
    // 0x7101038d88 (declaration only; placeholder name): per-frame update (Unk_SoundMgr38::sub_710102C098).
    void sub_7101038D88();
    // 0x7101039208: empty in the release build (Unk_SoundMgr38::sub_710102AE50).
    void sub_7101039208();
    // 0x7101037ed8 (declared only; 132 B): sets the box (centre `pos`, size `size`) and stores both vectors.
    void sub_7101037ED8(const sead::Vector3f* pos, const sead::Vector3f* size);
    // 0x7101039920 (declaration only; placeholder name): queues a splash of `size` at `pos` (picks one of
    // two pools by the size; ElementWater::sub_71010E9A70).
    bool sub_7101039920(f32 size, const sead::Vector3f& pos);
    // 0x7101039588 (declaration only; placeholder name): the same for the moving water core
    // (ElementWater::m35).
    bool sub_7101039588(f32 size, const sead::Vector3f& pos);
    // 0x7101037f5c: stores `value` in the byte at +0x344.
    void sub_7101037F5C(u8 value);
    // 0x7101037f64: sets the enabled flag at +0x328 (clears the pointers at +0x3c0 / +0x3c8 when disabled).
    void sub_7101037F64(bool enabled);
    // 0x7101037f7c: stores `value` in the byte at +0x39c.
    void sub_7101037F7C(bool value);
    // 0x710103920c (placeholder name): fades the four sound handles.
    void sub_710103920C();
    // 0x7101039dd8 (placeholder name): draws the occlusion box in blue when _3d0 bit 0 is set.
    void sub_7101039DD8(sead::DrawContext* context, const sead::Camera& camera,
                        const sead::Projection& projection);
    // 0x71010391ac (placeholder name): requests the "WaterObjSound" actor once and clears the
    // occlusion state; called by sound::setEnv.
    void sub_71010391AC(sead::Heap* heap, act::ActorCreator* creator);
    // 0x710103937c / 0x71010375cc (declared only): called by Unk_SoundMgr38::sub_710102AF84 (the second before
    // deletion).
    void sub_710103937C();
    void sub_71010375CC();

    // 0x710103757c: runs 0x71010375cc first.
    virtual ~Unk_SoundMgr38_28();

    // One queued splash (0x20 bytes): its position, the 10.0 weight and its list node. The first
    // word is the free-list link while the entry is free.
    struct SplashEntry {
        union {
            struct {
                /* 0x00 */ sead::Vector3f mPos;
                /* 0x0c */ f32 _0c;
            };
            /* 0x00 */ SplashEntry* mNextFree;
        };
        /* 0x10 */ sead::ListNode mNode;
    };
    KSYS_CHECK_SIZE_NX150(SplashEntry, 0x20);
    // A splash pool (0x30 bytes) at +0x208: the active list, the free-list head and the capacity.
    struct SplashPool : sead::ListImpl {
        // 0x7101039920 (placeholder name): appends `entry` to the active list.
        void pushFront(SplashEntry* entry) { sead::ListImpl::pushFront(&entry->mNode); }

        /* 0x18 */ SplashEntry* mFree = nullptr;
        /* 0x20 */ u32 _20 = 0;
        /* 0x24 */ u32 _24 = 0;
        /* 0x28 */ u32 mMax = 0;
        /* 0x2c */ u32 _2c = 0;
    };
    KSYS_CHECK_SIZE_NX150(SplashPool, 0x30);

    /* 0x008 */ act::BaseProcHandle mProcHandle;
    /* 0x018 */ void* _18 = nullptr;
    u8 _20[0x1c0 - 0x20];
    // The four sound handles faded by sub_710103920C.
    /* 0x1c0 */ xlink2::HandleSLink _1c0[2];
    /* 0x1e0 */ xlink2::HandleSLink _1e0[2];
    u8 _200[0x208 - 0x200];
    /* 0x208 */ SplashPool mSplashPools[2];
    /* 0x268 */ sead::CriticalSection _268;
    /* 0x2a8 */ sead::CriticalSection _2a8;
    /* 0x2e8 */ sead::CriticalSection _2e8;
    /* 0x328 */ bool _328;
    /* 0x32c */ sead::Vector3f mBoxMin;
    /* 0x338 */ sead::Vector3f mBoxMax;
    /* 0x344 */ u8 _344;
    u8 _345[0x398 - 0x345];
    /* 0x398 */ f32 _398;
    /* 0x39c */ bool _39c;
    u8 _39d[0x3a8 - 0x39d];
    /* 0x3a8 */ void* _3a8 = nullptr;
    /* 0x3b0 */ void* _3b0 = nullptr;
    /* 0x3b8 */ void* _3b8 = nullptr;
    /* 0x3c0 */ void* _3c0;
    /* 0x3c8 */ void* _3c8;
    /* 0x3d0 */ u32 _3d0 = 0;
    /* 0x3d4 */ u8 _3d4 = 0;
    u8 _3d5[0x3d8 - 0x3d5];
    /* 0x3d8 */ sead::Vector3f mBoxCenter;
    /* 0x3e4 */ sead::Vector3f mBoxSize;
};

// Placeholder name (SoundMgr::_38::_20; ctor 0x7101029864, init 0x7101029958): the registry of the
// environment sound emit points (uking::act::EnvSeEmitPoint actors). Its two lists (0x18 bytes per entry, guarded by
// the CriticalSection at +0x38) are indexed by the `_83c` kind of the emit point (0 or 1).
class Unk_SoundMgr38_20 {
public:
    Unk_SoundMgr38_20();
    virtual ~Unk_SoundMgr38_20();
    void sub_7101029958(sead::Heap* heap);
    // 0x710102996c (was nullsub_4392): empty in the release build; called by Unk_SoundMgr38's update.
    void sub_710102996C();
    void sub_7101029970();
    void sub_71010299AC();
    void sub_7101029AA0();
    void sub_7101029B94();
    void sub_7101029BA0();
    void sub_7101029BA8();
    // 0x7101029bb0 (declared only; lane1 s47): registers `point` in the list of its kind (the kind is picked by the
    // actor's name); false if the name matches no kind.
    bool sub_7101029BB0(uking::act::EnvSeEmitPoint* point);
    // 0x7101029c98 (declared only; lane1 s47): removes `point` from the list of its kind.
    void sub_7101029C98(uking::act::EnvSeEmitPoint* point);
    // 0x71010299ac and 0x7101029aa0 pass their respective emit-point lists.
    void sub_7101029D3C(sead::OffsetList<uking::act::EnvSeEmitPoint>* points);

    /* 0x08 */ sead::OffsetList<uking::act::EnvSeEmitPoint> _8[2];
    /* 0x38 */ sead::CriticalSection mCS;
    bool _78 = false;
    bool _79 = false;
    bool _7a[2] = {};
    f32 _7c = 400.0f;
    f32 _80 = 600.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_SoundMgr38_20, 0x88);

// Placeholder name (SoundMgr::_38::_48; lane1 s47): a registry of actors (list at +0x1aa8, guarded by the CriticalSection
// at +0x1d58) used by the GrudgeEyeball AI.
class Unk_SoundMgr38_48 {
public:
    // 0x71010352f0 / 0x71010353b0
    virtual ~Unk_SoundMgr38_48();
    // 0x7101035b50 (declared only): adds `actor` to the list (if it has room).
    void sub_7101035B50(ksys::act::Actor* actor);
    // 0x7101035c50 (declared only): removes the entry of the actor with id `id` / hash id `hash_id`.
    void sub_7101035C50(u32 id, u32 hash_id);
    // 0x7101035a50: sets bit 0 of _1e08; the first time (bit 1 clear) also runs 0x7101035888 and sets _1dc0 to 1.
    void sub_7101035A50();
    // 0x71010359b0 (placeholder name): loads the asset info reader at _1da0 with an empty name and hands it to
    // the user instance at _1d98 once it is ready; releases both when the load fails.
    bool sub_71010359B0();
    // 0x7101035888 (placeholder name): creates the empty-name user instance and its asset info reader,
    // then loads the bars file for it; releases both when either step fails.
    void sub_7101035888();
    // 1036530: completes a sphere query; writes the indoor result only after execution status 1.
    bool sub_7101036530(bool* indoor, const sead::Vector3f& position);

    // 0x7101035a90 fills a 64-entry object list here.
    u8 _8[0xc38 - 0x8];
    /* 0xc38 */ sead::CriticalSection _c38;
    u8 _c78[0x1a88 - 0xc78];
    // Element type unknown (trivially destructible); the destructor frees the buffer.
    /* 0x1a88 */ sead::Buffer<u8> _1a88;
    // Element type unknown; the destructor frees the buffer.
    /* 0x1a98 */ sead::PtrArrayImpl _1a98;
    u8 _1aa8[0x1d58 - 0x1aa8];
    /* 0x1d58 */ sead::CriticalSection _1d58;
    /* 0x1d98 */ xlink2::UserInstanceSLink* _1d98 = nullptr;
    /* 0x1da0 */ Unk_7102502950* _1da0 = nullptr;
    u8 _1da8[0x1dc0 - 0x1da8];
    /* 0x1dc0 */ u32 _1dc0;
    u8 _1dc4[0x1dc8 - 0x1dc4];
    // Killed by the destructor.
    /* 0x1dc8 */ xlink2::HandleSLink _1dc8;
    u8 _1dd8[0x1e00 - 0x1dd8];
    // 1034A10 stores SphereRigidBody::make's result here; 1036530 borrows it for the query.
    /* 0x1e00 */ phys::SphereRigidBody* mSphere;
    /* 0x1e08 */ sead::BitFlag8 _1e08;
    // Allocation 102A3D0 is 0x1e20; 1034A10 initializes additional state in this tail.
    u8 _1e09[0x1e20 - 0x1e09];
};
KSYS_CHECK_SIZE_NX150(Unk_SoundMgr38_48, 0x1e20);

// Placeholder names (SoundMgr::_38 members at +0x8 / +0x10 / +0x18 / +0x38 / +0x40 / +0x50 / +0x58 / +0x60): only
// the method that Unk_SoundMgr38::sub_710102AEC4 calls on each is declared (all declared only).
// vtable 0x71025018c0: the pooled unifiable position of Unk_SoundMgr38_8 (D1 is aal::IUnifiable's, D0 is in
// this TU, calcUnifiablePositions is aal::UnifiablePosition's).
class Unk_71025018c0 : public aal::UnifiablePosition {};

class Unk_SoundMgr38_8 {
public:
    // 0x710102c1d8
    Unk_SoundMgr38_8();
    virtual ~Unk_SoundMgr38_8();
    // 0x710102c27c: deletes the forest shake handle, frees the speaker balance unifier and the positions.
    void sub_710102C27C();
    // 0x710102c388: called with the heap right after construction (50 positions, the "ForestShake" unifier, the forest shake handle).
    void sub_710102C388(sead::Heap* heap);
    // 0x710102c4b0: once the "EnvSoundTree" actor is ready, keeps it in mTree (NoDistanceCheck) and wakes it.
    void sub_710102C4B0();
    // 0x710102c7c0: requests the "EnvSoundTree" actor unless it exists.
    void sub_710102C7C0(sead::Heap* heap, act::ActorCreator* creator);
    // 0x710102c810
    void sub_710102C810();
    // 0x710102c81c: fades the forest shake sound out.
    void sub_710102C81C();
    // 0x710102c594: runs the update 0x710102c5ac while _68 is set and there is a tree actor.
    void sub_710102C594();
    // 0x710102c5ac: plays / fades the forest shake sound and unifies its speaker balance.
    void sub_710102C5AC();
    // 0x710102c8f8: deletes the proc and clears mTree / _68.
    void sub_710102C8F8();
    // 0x710102c9e8 (declared by lane1 s95; placeholder name): releases a handle obtained from this object
    // (LumberjackTree::_2e0): removes it from the speaker balance unifier and returns it to the free list.
    void sub_710102C9E8(void* handle);
    // 0x710102c924 (placeholder name): hands out a position from the pool and adds it to the unifier (null when
    // the pool is not set up or full).
    Unk_71025018c0* sub_710102C924();

    /* 0x08 */ act::BaseProcHandle mProcHandle;
    // The "EnvSoundTree" actor (0x710102c4b0 casts it to SoundSystemActor).
    /* 0x18 */ act::Actor* mTree = nullptr;
    // 50 positions (0x710102c388); handed out by 0x710102c924 and taken back by sub_710102C9E8.
    /* 0x20 */ sead::ObjList<Unk_71025018c0> mPositions;
    /* 0x50 */ u32 _50 = 0;
    /* 0x58 */ aal::SpeakerBalanceUnifier* mUnifier = nullptr;
    // Forest shake sound (faded by 0x710102c81c).
    /* 0x60 */ xlink2::HandleSLink* _60 = nullptr;
    /* 0x68 */ bool _68 = false;
    /* 0x70 */ sead::CriticalSection mCS;
    /* 0xb0 */ bool _b0 = false;
};
class Unk_SoundMgr38_10 {
public:
    // 0x7101032870: resets the positions when the manager is running and has a proc.
    void sub_7101032870();
    // 0x7101031010 (declared only)
    Unk_SoundMgr38_10();
    virtual ~Unk_SoundMgr38_10();
    // 0x71010317b4 (declared only): called with the heap right after construction.
    void sub_71010317B4(sead::Heap* heap);
    void sub_71010333F0();
    // 0x710103362c: stops the proc and resets the positions (called by Unk_SoundMgr38::sub_710102AF84).
    void sub_710103362C();
    // 0x7101032940 (declared only; 2536 B): the per-frame position update called by sub_7101032870.
    void sub_7101032940();

    // 0x71010333e0: sets _10c1 (Unk_SoundMgr38::sub_710102AE50).
    void sub_71010333E0();

    /* 0x0008 */ act::BaseProcHandle mProcHandle;
    /* 0x0018 */ void* _18 = nullptr;
    /// The fixed positions handed to the speaker balance unifier.
    /* 0x0020 */ aal::UnifiablePosition mPositions[32];
    /* 0x0720 */ bool mPositionActive[32];
    /* 0x0740 */ aal::SpeakerBalanceUnifier* mUnifier = nullptr;
    u8 _748[0x10];
    /* 0x0758 */ bool _758 = false;
    /* 0x075c */ f32 _75c = 0.0f;
    u8 _760[0x14];
    /* 0x0774 */ f32 _774 = 0.0f;
    u8 _778[0x10];
    /// The per-position cache (0x38 bytes each); the three search results are at +0x28.
    struct PositionCache {
        u8 _0[0x28];
        f32 _28[3];
        u8 _34[4];
    };
    /* 0x0788 */ PositionCache _788[32];
    /* 0x0e88 */ bool _e88[32];
    u8 _ea8[0x10c0 - 0xea8];
    /* 0x10c0 */ bool _10c0 = false;
    /* 0x10c1 */ bool _10c1 = false;
    u8 _10c2[0x18f8 - 0x10c2];
    /* 0x18f8 */ bool _18f8 = false;
    u8 _18f9[0x1900 - 0x18f9];
    /* 0x1900 */ sead::CriticalSection mCS;
    u8 _1940[0x1950 - 0x1940];
};
class Unk_SoundMgr38_18 {
public:
    // 0x710102cfdc (declared only)
    Unk_SoundMgr38_18();
    virtual ~Unk_SoundMgr38_18();
    // 0x710102d9c0 (declared only): called with the heap right after construction.
    void sub_710102D9C0(sead::Heap* heap);
    void sub_710102EE60();
    // 0x710102effc (declared only): called by Unk_SoundMgr38::sub_710102AF84.
    void sub_710102EFFC();
    // 0x710102eb9c (empty in the release build): per-frame update (Unk_SoundMgr38::sub_710102C098).
    void sub_710102EB9C();

    // 0x710102ee40: sets three flags (Unk_SoundMgr38::sub_710102AE50).
    void sub_710102EE40();

    bool sub_710102F1E4();
    bool sub_710102F33C(const sead::Vector2i& shift, bool* updated);
    bool sub_710102F884(s32 x, s32 z, const sead::Vector2f& origin, tera::System* terrain,
                        uking::StatisticsMgr* statistics, bool* updated);

    // Native 102D9C0 allocates 1089 cells and initializes only their type words.
    struct Cell {
        f32 _0;
        f32 _4;
        f32 _8;
        sead::Vector3f mPosition;
        u32 _18 = 0;
    };
    KSYS_CHECK_SIZE_NX150(Cell, 0x1c);

    u8 _8[0x20 - 0x8];
    /* 0x20 */ sead::SafeArray<sead::SafeArray<Cell*, 33>, 33> mCells;
    /* 0x2228 */ Cell* mCellStorage;
    /* 0x2230 */ sead::Vector2i mGridCenter;
    /* 0x2238 */ sead::Vector2i mGridShift;
    /* 0x2240 */ sead::Vector2f mGridPosition;
    u8 _2248[0x7400 - 0x2248];
    /* 0x7400 */ sead::Vector3f mListenerPosition;
    u8 _740c[0x9624 - 0x740c];
    /* 0x9624 */ bool _9624;
    u8 _9625[0x9627 - 0x9625];
    /* 0x9627 */ bool _9627;
    u8 _9628;
    /* 0x9629 */ bool _9629;
    u8 _962a[0x962c - 0x962a];
    /* 0x962c */ u32 _962c;
    u8 _9630[0x96b8 - 0x9630];
    /* 0x96b8 */ void* mWaterFlowStats;
    u8 _96c0[0xa828 - 0x96c0];
};
KSYS_CHECK_SIZE_NX150(Unk_SoundMgr38_18, 0xa828);
static_assert(offsetof(Unk_SoundMgr38_18, mCells) == 0x20);
static_assert(offsetof(Unk_SoundMgr38_18, mCellStorage) == 0x2228);
static_assert(offsetof(Unk_SoundMgr38_18, mGridCenter) == 0x2230);
static_assert(offsetof(Unk_SoundMgr38_18, mListenerPosition) == 0x7400);
static_assert(offsetof(Unk_SoundMgr38_18, _962c) == 0x962c);
static_assert(offsetof(Unk_SoundMgr38_18, mWaterFlowStats) == 0x96b8);
class Unk_SoundMgr38_38 {
public:
    // 0x7101039f00 (declared only)
    Unk_SoundMgr38_38();
    // 0x710103a02c (empty) / 0x710103a030
    virtual ~Unk_SoundMgr38_38();
    // 0x710103a034 (empty in the release build): called with the heap right after construction.
    void sub_710103A034(sead::Heap* heap);
    // 0x710103a084 (placeholder name): fades the three effect handles.
    void sub_710103A084();
    // 0x710103a294 (empty in the release build): called by Unk_SoundMgr38::sub_710102AF84.
    void sub_710103A294();
    // 0x710103a038 (placeholder name): resets the vectors, the first handle and the unit scale;
    // called by sound::setEnv on _38.
    void sub_710103A038();

    /* 0x08 */ void* _8 = nullptr;
    /* 0x10 */ u32 _10 = 0;
    /* 0x14 */ sead::Vector3f _14;
    /* 0x20 */ sead::Vector3f _20;
    /* 0x2c */ sead::Vector3f _2c;
    /* 0x38 */ sead::Vector3f _38;
    /* 0x44 */ sead::Vector3f _44;
    /* 0x50 */ sead::Vector3f _50;
    // The three sound handles faded by sub_710103A084.
    /* 0x60 */ xlink2::HandleSLink _60;
    /* 0x70 */ xlink2::HandleSLink _70;
    /* 0x80 */ xlink2::HandleSLink _80;
    /* 0x90 */ f32 _90 = 0;
    /* 0x94 */ f32 _94 = 0;
    /* 0x98 */ s32 _98 = 0;
    /* 0x9c */ s32 _9c = 0;
    /* 0xa0 */ s32 _a0 = 0;
    /* 0xa4 */ f32 _a4 = 0;
    /* 0xa8 */ f32 _a8 = 0;
    /* 0xac */ f32 _ac = 0;
    /* 0xb0 */ f32 _b0 = 0;
    /* 0xb4 */ f32 _b4 = 0;
    /* 0xb8 */ f32 _b8 = 0;
    /* 0xbc */ f32 _bc = 0;
    /* 0xc0 */ u32 _c0 = 0;
    /* 0xc4 */ u32 _c4 = 0;
    /* 0xc8 */ u32 _c8 = 0;
    /* 0xcc */ u32 _cc = 0;
    /* 0xd0 */ u16 _d0 = 0;
    u8 _d2[0xd8 - 0xd2];
};
class Unk_SoundMgr38_40 {
public:
    // 0x71012be294 (declared only)
    Unk_SoundMgr38_40();
    // 0x71012be5ec (empty) / 0x71012be5f0 (vtable 0x710251ac60 only has the destructor pair)
    virtual ~Unk_SoundMgr38_40();
    // 0x71012be5f4 (empty in the release build): called with the heap right after construction.
    void sub_71012BE5F4(sead::Heap* heap);
    void sub_71012BEC28();
    // 0x71012bed18 (empty in the release build): called by Unk_SoundMgr38::sub_710102AF84.
    void sub_71012BED18();

    u8 _8[0x2f0 - 0x8];
};
class Unk_SoundMgr38_50 {
public:
    // 0x7101036748
    Unk_SoundMgr38_50();
    virtual ~Unk_SoundMgr38_50();
    // 0x7101036840: sub_7101036848(-1).
    void sub_7101036840();
    // 0x7101036848: fades the three SLink handles.
    void sub_7101036848(s32 value);
    // 0x7101036a68 (empty in the release build): called before deletion.
    void sub_7101036A68();
    // 0x71010367e8: resets the state and both faders.
    void sub_71010367E8();

    // The three SLink handles (mpResource / mCreateId pairs) at +0x8, +0x18, +0x28.
    /* 0x08 */ xlink2::HandleSLink _8;
    /* 0x18 */ xlink2::HandleSLink _18;
    /* 0x28 */ xlink2::HandleSLink _28;
    /* 0x38 */ u32 _38 = 0;
    /* 0x3c */ bool _3c = false;
    /* 0x40 */ u32 _40 = 0;
    /* 0x44 */ s32 _44 = -1;
    /* 0x48 */ u32 _48 = 0;
    /* 0x50 */ aal::SimpleTimedFader _50{1.0f};
    /* 0x68 */ aal::SimpleTimedFader _68{1.0f};
    /* 0x80 */ u16 _80 = 0;
    /* 0x84 */ u32 _84 = 0;
    /* 0x88 */ bool _88 = false;
    /* 0x8c */ f32 _8c = 50.0f;
    /* 0x90 */ f32 _90 = 500.0f;
    /* 0x94 */ bool _94 = false;
    /* 0x98 */ u32 _98 = 0;
};
class Unk_SoundMgr38_58;
class Unk_SoundMgr38_60;

// Placeholder name (SoundMgr::_38; vtable 0x7102501880 with D1 / D0 only, ctor 0x7101029fe0).
class Unk_SoundMgr38 {
public:
    Unk_SoundMgr38();
    virtual ~Unk_SoundMgr38();

    // 0x710102c098 (placeholder name): runs the per-frame update of each sub-manager.
    void sub_710102C098();
    // 0x710102c104: returns `_28`.
    Unk_SoundMgr38_28* sub_710102C104() const;
    // 0x710102c10c: unavailable while the manager's mode byte is set.
    Unk_SoundMgr38_28* sub_710102C10C() const;
    // 0x710102b11c: forwards to the cleanup operation.
    void sub_710102B11C();
    // 0x710102af84: finalizes and deletes the sub-managers and releases the xlink2 user and its asset reader.
    void sub_710102AF84();
    void sub_710102B4B8();
    // 0x710102ae50: starts the sub-managers (_8 / _10 / _18 only while _70 is set).
    void sub_710102AE50();
    // 0x710102aec4: stops the sub-managers (only while _70 is set) and the xlink2 user's events.
    void sub_710102AEC4();
    // 0x710102a28c: creates the sub-managers _8 / _10 / _18 / _20 / _30 / _38 / _40 on `heap`.
    void init(sead::Heap* heap);

    Unk_SoundMgr38_8* _8 = nullptr;
    Unk_SoundMgr38_10* _10 = nullptr;
    Unk_SoundMgr38_18* _18 = nullptr;
    /* 0x20 */ Unk_SoundMgr38_20* _20 = nullptr;
    /* 0x28 */ Unk_SoundMgr38_28* _28 = nullptr;
    /* 0x30 */ SpeakerBalanceUnifierMgr* _30 = nullptr;
    Unk_SoundMgr38_38* _38 = nullptr;
    Unk_SoundMgr38_40* _40 = nullptr;
    /* 0x48 */ Unk_SoundMgr38_48* _48 = nullptr;
    Unk_SoundMgr38_50* _50 = nullptr;
    Unk_SoundMgr38_58* _58 = nullptr;
    Unk_SoundMgr38_60* _60 = nullptr;
    xlink2::UserInstanceSLink* _68 = nullptr;
    // Read by 0x710102c10c and the cleanup operation 0x710102af84.
    /* 0x70 */ bool _70 = false;
    u32 _74 = 0;
    u32 _78 = 0;
    u32 _7c = 0;
    // Released through SoundMgr::_60 (0x7101059354) by the destructor.
    /* 0x80 */ Unk_7102502950* _80 = nullptr;
    /* 0x88 */ u32 _88 = 0;
    u32 _8c = 0;
    u32 _90 = 0;
    /* 0x98 */ u64 _98 = 0;
    /* 0xa0 */ u8 _a0 = 0;
    /* 0xa4 */ u32 _a4 = 0;
    /* 0xa8 */ u32 _a8 = 0x80000000;
    /* 0xac */ u32 _ac = 0x80000000;
    /* 0xb0 */ aal::TimedFader _b0{1.0f, aal::FadeCurveType(0), 1.0f};
    /* 0xd8 */ aal::TimedFader _d8{1.0f, aal::FadeCurveType(0), 1.0f};
    /* 0x100 */ u16 _100 = 2;
    /* 0x108 */ aal::TimedFader _108{1.0f, aal::FadeCurveType(0), 1.0f};
    // Whole 102b120 passes it as a float to 1036a6c.
    /* 0x130 */ f32 _130 = 0;
    u32 _134 = 0;
    /* 0x138 */ void* _138 = nullptr;
    /* 0x140 */ f32 _140 = -1.0f;
    /* 0x144 */ s32 _144 = -1;
    /* 0x148 */ u8 _148 = 0;
    /* 0x14c */ u32 _14c = 0;
    /* 0x150 */ u32 _150 = 0;
    /* 0x154 */ f32 _154 = 50.0f;
    /* 0x158 */ f32 _158 = 500.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_SoundMgr38, 0x160);

// Placeholder (a target of one of the per-ducker settings: the group name at +0 and the target settings at +0x58;
// Ducker::setup passes the name and 0x710103e020 reads the settings).
struct Unk_7102612758 {
    /* 0x00 */ sead::FixedSafeString<32> mName;
    /* 0x38 */ u8 _38[0x20];
    /* 0x58 */ aal::GroupDucker::TargetSettings mSettings;
};

// Placeholder (the per-ducker settings DuckingMgr::init passes to DuckingMgr::Ducker::setup; the static instances
// start at 0x7102612628 and are 0x130 bytes apart). A name string at +0, the group ducker settings at +0x58, the
// ducking duration at +0x64, a flag at +0x68, the target count at +0x6c and the target array at +0x70.
struct Unk_7102612628 {
    /* 0x00 */ sead::FixedSafeString<32> mName;
    /* 0x38 */ u8 _38[0x20];
    /* 0x58 */ aal::GroupDucker::Settings mSettings;
    /* 0x64 */ f32 mDuration;
    /* 0x68 */ bool _68;
    /* 0x6c */ s32 mTargetNum;
    /* 0x70 */ Unk_7102612758* mTargets[24];
};
KSYS_CHECK_SIZE_NX150(Unk_7102612628, 0x130);

// Placeholder (the ducking request of 0x71010421f0: a buffered name at +0, the group ducker settings at +0x58, the
// group list at +0x68, one target setting at +0x70 and a flag at +0x80).
struct Unk_71025022a0 {
    /* 0x00 */ sead::FixedSafeString<64> mName;
    /* 0x58 */ aal::GroupDucker::Settings mSettings;
    /* 0x68 */ sead::PtrArray<aal::Group>* mGroups;
    /* 0x70 */ aal::GroupDucker::TargetSettings mTargetSettings;
    /* 0x80 */ bool _80;
};
KSYS_CHECK_SIZE_NX150(Unk_71025022a0, 0x88);
static_assert(offsetof(Unk_71025022a0, mSettings) == 0x58);
static_assert(offsetof(Unk_71025022a0, mGroups) == 0x68);
static_assert(offsetof(Unk_71025022a0, mTargetSettings) == 0x70);
static_assert(offsetof(Unk_71025022a0, _80) == 0x80);

// The secondary polymorphic base of DuckingMgr::Ducker (vtable at 0x7102502200).
class Unk_7102502200 {
public:
    virtual ~Unk_7102502200() = default;
};

// Root subobject at 0x5e0 of Unk_710103b704, constructed at 0x710105abc0.
// Its original vtable has only the two destructor slots.
class Unk_710105abc0 {
public:
    explicit Unk_710105abc0(sead::Heap* heap);
    virtual ~Unk_710105abc0();
    void sub_710105ACEC();
    // 0x710105ae80 (placeholder name): the play position of _10 in frames (30 per second), or -1 when it is not
    // playing or has no sample rate.
    f32 sub_710105AE80() const;
    void sub_710105AF00(const sead::SafeString& name, bool skip_event_info);
    bool sub_710105B090();
    void sub_710105B37C();
    // 0x710105b0c8: loads the RelicBeamBgm control resources when `mask` is set, otherwise loads the
    // named bars resource through the 0x828 list.
    void sub_710105B0C8(const sead::SafeString& name, res::Handle* pack, u8 mask);
    // 0x710105b0f0: holds RelicBeamBgm and loads the Demo143 resources selected by `mask`.
    void sub_710105B0F0(const sead::SafeString& name, u8 mask);
    // 0x710105b224: whether the RelicBeamBgm and the Demo143 resources selected by _39 have finished.
    bool sub_710105B224(const sead::SafeString& name);
    // 0x710105b7d0: releases RelicBeamBgm and releases the Demo143 resources selected by _39.
    void sub_710105B7D0();
    void sub_710105B5D4(const sead::SafeString& name, bool use_barefoot, bool);
    void sub_710105B934(const sead::SafeString&, bool defer_bgm);
    void sub_710105B394(const sead::SafeString& type);
    void sub_710105B8EC();
    // 0x710105ba88: this control guard and the shared RelicBeamBgm stop path.
    void sub_710105BA88();

    aal::Emitter* _8;
    aal::Handle _10;
    aal::SimpleTimedFader _20{1.0f};
    sead::BitFlag8 _38;
    // 0x710105abc0 clears this byte alongside _38.
    u8 _39;
    u8 _3a[2];
    f32 _3c;
};
KSYS_CHECK_SIZE_NX150(Unk_710105abc0, 0x40);

// Embedded record constructed at +8 by 0x710103b704. Its native constructor
// initializes the fixed strings; the remaining layout is still opaque.
class Unk_710103b76c {
public:
    // 0x710103b76c: only the strings are initialised.
    Unk_710103b76c();

    struct Entry {
        sead::FixedSafeString<64> _0;
        sead::FixedSafeString<64> _58;
        // 0x710103c03c stores the bit-0-normalized start argument here.
        bool _b0;
        u8 _b1[7];
    };

    static_assert(sizeof(Entry) == 0xb8);
    static_assert(offsetof(Entry, _b0) == 0xb0);

    // Eight records are constructed at 0x710103b76c; the source container identity is unknown.
    Entry _0[8];

    // inline-only in the original; name is a guess. 0x710103ceb0 / 0x710103d0d8 /
    // 0x710103d324 repeat this unsigned <8 check and index-0 fallback.
    Entry& getEntry(s32 index) {
        if (u32(index) < 8)
            return _0[index];
        return _0[0];
    }
};
KSYS_CHECK_SIZE_NX150(Unk_710103b76c, 0x5c0);
static_assert(offsetof(Unk_710103b76c, _0) == 0);

// Placeholder (lane2 s46): the sound kind (0..5) the UI hands to SoundMgr (a 4-byte class: passed in a full register).
struct UiSoundKind {
    s32 value;
};

// Placeholder name (ctor 0x710103b704; SoundMgr::_98): starts / stops the two custom duckers (indices 0x30 / 0x31
// of the DuckingMgr). Used by CustomDuckingStartAction / CustomDuckingEndAction.
class Unk_710103b704 {
public:
    // Native scene-control switches spill/reload these four-byte enum wrappers.
    // Enumerator names are unknown; the switches cover 0..9 and 0..5.
    SEAD_ENUM(BgmCtrlType, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9)
    SEAD_ENUM(SeCtrlType, _0, _1, _2, _3, _4, _5)
    explicit Unk_710103b704(sead::Heap* heap);
    void sub_710103BA44();
    void sub_710103BD88(const sead::SafeString& name, bool skip_event_info);
    void sub_710103BE18(const sead::SafeString& name, const sead::SafeString& type,
                        bool mixed, bool start_control, bool use_barefoot, bool flag);
    void sub_710103C334(const sead::SafeString& name, const sead::SafeString& type,
                        bool defer_bgm);
    void sub_710103C7D0();
    // Whole 103BDD8 / 103BDE0 operate on the embedded control at +5e0.
    bool isBgmReady();
    void setWorldMuteType(bool movie, const sead::SafeString& type);
    void sub_710103BD3C();
    bool sub_710103CE1C();
    void sub_710103CEB0();
    void sub_710103C5F4(bool defer_bgm);
    virtual ~Unk_710103b704();
    struct StartParam {
        sead::SafeString _0;
        sead::SafeString _10;
        f32 _20;
        f32 _24;
        f32 _28;
        f32 _2c;
    };

    // 0x710103cff4 (declared only)
    void sub_710103CFF4(StartParam& param);
    // 0x710103d094 (declared only)
    void sub_710103D094();
    // 0x710103d0d8 / 0x710103d324 (declared only): the UI sound kind handed over by SoundMgr (see sub_71011FC0C0).
    void sub_710103D0D8(UiSoundKind kind);
    // 0x710103d324: applies and clears the event skip duckers; for the "Demo346_4" entry, _620 = 1 for kind 1,
    // else 0.5.
    void sub_710103D324(UiSoundKind kind);
    // 0x710103d418: starts the ducker 0x1f.
    void sub_710103D418();

    // 0x710103bb00 (declared only; CSV unnamed): applies the scene sound controls (bgm type, se type) now.
    void sub_710103BB00(BgmCtrlType bgm_type, SeCtrlType se_type);
    // 0x710103cfe8: stores the two types in _5d0 / _5d4 for later (used while _5cc is set).
    void sub_710103CFE8(int bgm_type, int se_type);

    /* 0x8 */ Unk_710103b76c _8;
    /* 0x5c8 */ s32 _5c8;
    /* 0x5cc */ u8 _5cc;
    u8 _5cd[0x5d0 - 0x5cd];
    /* 0x5d0 */ int _5d0;
    /* 0x5d4 */ int _5d4;
    // Set by SceneSoundSetEndProcAction ("SkipAll"); name unknown.
    /* 0x5d8 */ bool _5d8;
    // Whole constructor clears the pair at +5d8; BD3C clears this control byte.
    bool _5d9;
    u8 _5da[0x5e0 - 0x5da];
    /* 0x5e0 */ Unk_710105abc0 _5e0;
    /* 0x620 */ f32 _620;
};
KSYS_CHECK_SIZE_NX150(Unk_710103b704, 0x628);

// Name from the CSV (snd::DuckingMgr::startDucking 0x7101042078; ctor 0x710103e404, init 0x710103e58c).
// SoundMgr::_80. A buffer (size at +8, data at +0x10) of 50 duckers (0xd0 bytes each: aal::GroupDucker at +0x68,
// `_c0` / `_c8` state) indexed by a SEAD_ENUM of ducker names (the enum's text function is 0x7101042f30);
// entries 0x30 / 0x31 are the "custom" duckers used by Unk_710103b704.
// TODO: incomplete.
class DuckingMgr {
public:
    DuckingMgr();
    virtual ~DuckingMgr();

    // The names are the strings at 0x7101e26516 (the SEAD_ENUM text; text function 0x7101042f30).
    // clang-format off
    // (the original text has a space before each comma: `text_all` is 737 bytes)
    SEAD_ENUM(DuckerType,
              cSlowBgm , cSlowSe , cFocus , cSquat , cPauseIngame , cPauseEvent , cBattleEnv , cGrudgeEnv ,
              cGrudgeEnvBoost , cBloody , cBossDialogHero , cBossDialogZelda , cFieldRemainsFire ,
              cFieldRemainsOrGanon , cRaceAudience , cTalk , cDialog , cScreenFadeS , cScreenFadeM ,
              cScreenFadeL , cScreenFadeLogo , cScreenFadeForce , cHomeMenu , cEvtBgmReduce , cEvtBgmMute ,
              cEvtEnvReduce , cEvtWorldMute , cTmlnWorldMute , cTmlnThruShake , cTmlnThruShakeWeather ,
              cTmlnMovie , cTmlnLoading , cTitleMute , cEventSkip , cEventSkipBeam , cPlayTimeOver ,
              cExplosion , cImpact , cLocationUI , cWaveShockL , cParasailOpen , cDive , cHorseJump ,
              cFairyRecover , cLightningNear , cExplosionRemote , cEnemyWeaponSwing , cEnemyImpact ,
              cCustomEvt , cCustomEvt2)
    // clang-format on

    // The ducking settings of an attenuation entry (Unk_710251aef0::calc; 0xc bytes, an array in
    // DuckingMgr::init 0x710103e58c).
    struct AttenuationParam {
        // Whether the entry keeps ducking while the ducker is already on.
        /* 0x0 */ bool _0;
        // Multiplies the volume by the spatial volume of positioned sounds.
        /* 0x1 */ bool _1;
        // Starts from the value given with the handle.
        /* 0x2 */ bool _2;
        /* 0x4 */ f32 _4;
        /* 0x8 */ f32 _8;
    };

    struct Ducker : public aal::IDuckingSource, public Unk_7102502200 {
        // Vtable order (0x71025021b8): destructor pair and the ducking source interface.
        bool isOnDucking() const override;
        void invalidateORNode() override {}
        const sead::SafeString& getDuckingSourceName() const override { return mName; }
        ~Ducker() override;
        bool sub_710103E368() const;
        // 0x710103e00c: sets the active bit and clears _c0.
        void activateMaybe();
        // 0x710103e2a8: clears the active bit (`suspend`: also suspends mDucker).
        void deactivateMaybe(bool suspend);
        // 0x710103e2c4: activateMaybe() and resets mDucker's state.
        void activateAndResetMaybe();
        // 0x710103df60: per-frame update while active or ducking.
        void calc();
        // 0x710103ddf0: copies the settings' name and sets the group ducker up from them.
        void setup(sead::Heap* heap, Unk_7102612628* settings);
        // 0x710103e128 (placeholder name): the same setup from a request, adding every group of the request.
        void sub_710103E128(sead::Heap* heap, Unk_71025022a0* request);
        // 0x710103e2dc (placeholder name) and 0x710103e020 (the target volume update it calls).
        void sub_710103E2DC(f32 f);
        void sub_710103E020(f32 f);

        // The ducker's name (the ducker array allocator 0x7101041a5c constructs it over its own buffer).
        /* 0x10 */ sead::FixedSafeString<64> mName;
        /* 0x68 */ aal::GroupDucker mDucker;
        /* 0xb0 */ Unk_7102612628* _b0 = nullptr;
        // Set by DuckingMgr::init 0x710103e58c for the duckers of the attenuation entries (Unk_710251aef0).
        /* 0xb8 */ AttenuationParam* mAttenuationParam;
        /* 0xc0 */ f32 _c0;
        /* 0xc4 */ f32 _c4;
        /* 0xc8 */ u8 _c8;  // bit 0: active
    };

    // 0x7101041f4c (placeholder name): suspends every ducker that asked to be suspended and clears the flag.
    void sub_7101041F4C();
    // 0x7101042078: starts the ducker called `type` (looked up by name); null when there is none.
    Ducker* startDucking(const sead::SafeString& type);
    // 0x71010421f0: selects custom ducking roots, exclusions, and targets.
    Ducker* sub_71010421F0(DuckerType type, Unk_710103b704::StartParam& param);
    // 0x7101042db4: stops the ducker called `type` (`suspend`: also suspends its aal::GroupDucker).
    void sub_7101042DB4(const sead::SafeString& type, bool suspend);
    // 0x7101042024: starts the ducker `type`.
    // 0x7101041fec: updates every ducker.
    void calc();
    Ducker* sub_7101042024(DuckerType type);
    // 0x7101042d6c: clears bit 0 of the ducker `type`'s flags byte (+0xc8) and suspends its aal::GroupDucker if
    // `suspend`.
    void sub_7101042D6C(DuckerType type, bool suspend);

    // inline-only in the original; name is a guess (the type is copied to the stack before indexing in
    // 0x710103aa3c, 0x710103ab10, 0x710103ab98 and 0x710103acc8).
    Ducker& getDucker(DuckerType type) { return mDuckers[type]; }

    /* 0x08 */ sead::Buffer<Ducker> mDuckers;
    // The heap of the duckers, destroyed with them (the destructor calls destroy() through its vtable).
    /* 0x18 */ sead::Heap* mHeap = nullptr;
    /* 0x20 */ bool _20 = false;
};

// Actual sound-owned B8 allocation in 0x710105590C and embedded stream-path callback.
class Unk_710105fe78 {
public:
    Unk_710105fe78();
    virtual ~Unk_710105fe78();
    // Native lookup/provider use this existing resource-cache receiver.
    ResourceBars* sub_7101060C04(const sead::SafeString& name);
    bool sub_7101060D14(aal::AssetInfo* info, const sead::SafeString& path,
                        const sead::SafeString& asset);
    // Lookup 0x7101060C04 proves the hash/handle pair and sixteen-byte stride.
    struct Entry {
        u32 mHash;
        res::Handle* mHandle;
    };
    static_assert(sizeof(Entry) == 0x10);
    class Callback : public aal::Unk_7100BA1AEC {
    public:
        bool sub_7100BA1AEC(sead::BufferedSafeStringBase<char>* path, aal::AssetInfo* info) override;
        // 0x710105fe08: variadic formatter for this callback's actual path string.
        void sub_710105FE08(const char* format, ...);
        sead::FixedSafeString<128> mString;
    };
    static_assert(sizeof(Callback) == 0xa0);
    /* 0x08 */ sead::Buffer<Entry>* _8 = nullptr;
    /* 0x10 */ s32 _10 = 0;
    u8 _14[4];
    /* 0x18 */ Callback mCallback;
};
KSYS_CHECK_SIZE_NX150(Unk_710105fe78, 0xb8);

// 0x710105ffc4 (placeholder name; 3,136 B, declared only): loads the regional voice pack into the
// resource cache (x1 is the heap, x2 a flag).
void StaticVoicePackStuff(Unk_710105fe78* cache, sead::Heap* heap, bool flag);

// Placeholder name (SoundMgr::_48), used by the UI message screens.
class Unk_SoundMgr48 {
public:
    Unk_SoundMgr48();
    virtual ~Unk_SoundMgr48();
    void sub_710105590C(sead::Heap* heap);
    void sub_7101055B44();
    void sub_710105598C(const sead::SafeString& path, const sead::SafeString& name, s32 suffix);
    // Outside-TU callers pass SoundMgr::_48. The unused bool and formal FP order
    // are interface inferences from the handle / 0-or-1 / delay argument protocol.
    void sub_7101055B88(aal::Handle* handle, bool flag, f32 delay);
    f32 sub_7101055E3C() const;

    /* 0x08 */ Unk_710105fe78* _8 = nullptr;
    /* 0x10 */ aal::Emitter* _10 = nullptr;
    /* 0x18 */ aal::Handle _18;
    /* 0x28 */ aal::Handle _28;
};
KSYS_CHECK_SIZE_NX150(Unk_SoundMgr48, 0x38);



// Placeholder name (ctor 0x710104e5b4; SoundMgr::_90; the object has a byte at +0x2a0 whose bit 2 means "ducking
// is allowed"). Used by the message-dialog / talk actions (NPCTalk, OpenMessageDialog*, SimpleUniqueTalk).
// Placeholder name (0x710103ac60 / 0x710103ac84, in the sndSoundMgr38.cpp TU): a ducking request at
// ExpressionSoundCtrl +0x28c, held by the Remains battle BGMs while they play (Unk_71025ce3a0::m6).
// Ducks while a message sound (SoundMgr::_48) plays (owned by value by the Remains boss and dungeon BGMs).
class Unk_710103AB10 {
public:
    explicit Unk_710103AB10(s32 type) : mType(DuckingMgr::DuckerType::ValueType(type)) {}
    // 0x710103ab10: stops the ducker if it is active.
    ~Unk_710103AB10();
    // Stops the ducker if it is active. ICF-folded with the destructor at 0x710103ab10 in the original (the BGM
    // m13 overrides call it directly).
    void stop();
    // 0x710103aa3c: starts the ducker while a message sound plays and stops it afterwards.
    void calc();

    DuckingMgr::DuckerType mType;
};

struct Unk_710103AC60 {
    // 0x710103ab98: while requested, the ducker runs except during events.
    void calc();
    // 0x710103ac60: unless already active, requests cFieldRemainsFire (kind 1) or cFieldRemainsOrGanon.
    void start(s32 kind);
    // 0x710103ac84: releases the requested ducker.
    void stop();

    DuckingMgr::DuckerType mType;
    bool mActive;
};
KSYS_CHECK_SIZE_NX150(Unk_710103AC60, 0x8);

// Placeholder: like Unk_710103AC60, but the ducker can be kept for a number of frames after a stop.
struct Unk_710103ACC8 {
    // 0x710103acc8: while requested, the ducker runs except during events; then counts the hold frames down.
    void calc();
    // 0x710103adb4: requests the ducker (and cancels a pending hold).
    void start();
    // 0x710103adcc: releases the request (`hold`: keeps the ducker for 120 more frames).
    void stop(bool hold);

    DuckingMgr::DuckerType mType;
    s32 mHoldFrames;
    bool mActive;
};

class ExpressionSoundCtrl {
    // Native 0x710104e5b4 constructs the singleton disposer at +8; vtable 0x71025024d0.
    SEAD_SINGLETON_DISPOSER(ExpressionSoundCtrl)

public:
    virtual ~ExpressionSoundCtrl();

    // 0x710104ed9c: re-enables emission in the root group, un-pauses it, stops the pause duckers and restores the
    // stream fader (used when the pause menu / event pause ends).
    void sub_710104ED9C();
    // 0x710104ee4c (was nullsub_4416): empty in the release build; called by SoundMgr::sub_71011FBD58.
    void sub_710104EE4C(bool a);
    // 0x710104f4bc / 0x710104f4c0 (were nullsub_4417 / nullsub_4418): empty in the release build; called on the
    // instance by 0x71009ebec8.
    void sub_710104F4BC();
    void sub_710104F4C0();
    // 0x710104f86c: starts the dialogue ducker (SoundMgr::_80 ducker 0x10) while an event is active.
    void sub_710104F86C();
    // 0x710104f8c4: `suspend` the dialogue ducker (SoundMgr::_80 ducker 0x10).
    void sub_710104F8C4(bool suspend);
    // 0x710104f8e0: starts the ducker 0xf unless ducking is not allowed (bit 2 of `_2a0`).
    void sub_710104F8E0();
    // 0x710104f98c: pauses the ingame or event groups and fades the stream down.
    void sub_710104F98C();
    // 0x710104f904: stops the ducker 0xf without suspending it.
    void sub_710104F904();
    // 0x710104f920: with `on`: stops the duckers 0x10 and 0xf and disables ducking (sets bit 2 of `_2a0`); else clears it.
    void sub_710104F920(bool on);
    void sub_710104FD4C();
    // 0x710104fd68: collects into `groups` the groups of the `type` bit (bit `type` of aal::Group::_13c), or the
    // leaves of `group`'s subtree when the bit is clear.
    void sub_710104FD68(aal::Group* group, sead::PtrArray<aal::Group>* groups, s32 type);
    void sub_710104FD38(const xlink2::HandleSLink& handle);
    void sub_710104EA7C();
    // 0x710104e964: per-frame update (user instance calc, volume state, handles, duckers).
    void sub_710104E964();
    // 0x710104ebbc (declared only)
    void sub_710104EBBC();
    // inline-only (see sndDialogue.cpp)
    inline void updateHandles();
    // 0x710104e92c: creates the "ExpressionSound" SLink user instance _28 on `heap`.
    void sub_710104E92C(sead::Heap* heap);
    void sub_710104EE50();
    void sub_710104EE64();
    // 0x710104f030: fades the two SLink handles out, clears _b8 and bit 3 of _2a0 and releases the Remains and
    // Ganon ducking requests.
    void sub_710104F030();
    // Whole F1B8 transitions from state 2 to the supplied scalar after emitting sound;
    // VFR 11C16EC supplies 0 for index 0 and 1 for index 4. Factory E5B4 starts at 2.
    void sub_710104F1B8(s32 state);
    // CameraNotify2Sound whole initializer 791680 and whole m8/m9 consumers
    // store and dispatch the eight nonvirtual member callbacks on this singleton.
    void sub_710104F354();
    void sub_710104F39C();
    void sub_710104F3EC();
    void sub_710104F404();
    void sub_710104F420();
    void sub_710104F438();
    void sub_710104F454();
    void sub_710104F46C();
    void sub_710104F488();
    void sub_710104F4A0();
    // 0x710104f4c4 also sets mask 8 of `_2a0`.
    void sub_710104F4C4();
    void sub_710104F518();
    void sub_710104F65C();
    void sub_710104F788();
    void sub_710104F614();
    void sub_710104F740();
    void sub_710104FA78(const xlink2::HandleSLink& handle);
    void sub_710104FB40(xlink2::HandleSLink* handle);

    xlink2::HandleSLink sub_710104F30C(const sead::SafeString& label);

    // The SLink user instance the sound triggers (SoundTrigger / SoundTriggerFadeAction) fall back to.
    /* 0x28 */ xlink2::UserInstanceSLink* _28;
    // Whole factory 104E5B4 initializes 2; whole EE64 reads and sets the state.
    s32 _30;
    u8 _34[4];
    // Faded by 0x710104f030 together with mFilter.
    /* 0x38 */ xlink2::HandleSLink _38;
    // Groups whose volume / pitch / filter follow the slow motion state (0x710104ebbc).
    /* 0x48 */ sead::Buffer<aal::Group*> _48;
    u8 _58[0x98 - 0x58];
    /* 0x98 */ aal::Group* _98;
    u8 _a0[0xa8 - 0xa0];
    // 0x710104f4c4 / 0x710104f614 / 0x710104f740 store searchAndEmit("Filter") here; the larger
    // 0x710104f518 family reads the resource and create id back.
    /* 0xa8 */ xlink2::HandleSLink mFilter;  // 16 bytes
    // 0x710104e0a0 / 0x710104e004 / 0x710104df54 (declared only) read the listeners at
    // 0x548 / 0x550 / 0x558 and store a four-level value through 0x528 / 0x530 / 0xc0 / 0x200.
    s32 _b8;
    u8 _bc[4];
    // Native 104FA78 emplaces a 16-byte handle and links its +0x10 list node.
    // Whole constructor initializes ObjList at +0xc0 and CriticalSection at +0xf0.
    sead::ObjList<xlink2::HandleSLink> mHandles;
    sead::CriticalSection mHandleCS;
    // Pause groups: the factory binds 16 pointers to each embedded array.
    /* 0x130 */ sead::FixedPtrArray<aal::Group, 16> mPauseIngameGroups;
    /* 0x1c0 */ sead::FixedPtrArray<aal::Group, 16> mPauseEventGroups;
    /* 0x250 */ u32 _250;
    u8 _254[4];
    /* 0x258 */ aal::SimpleTimedFader _258;
    /* 0x270 */ f32 _270;
    u8 _274[4];
    /* 0x278 */ xlink2::HandleSLink _278;
    u8 _288[0x28c - 0x288];
    /* 0x28c */ Unk_710103AC60 mRemainsDucking;
    // Requested by the Ganon beast BGM (Unk_71024fec18) while it waits to start a level.
    /* 0x294 */ Unk_710103ACC8 _294;
    /* 0x2a0 */ sead::BitFlag8 _2a0;
};
KSYS_CHECK_SIZE_NX150(ExpressionSoundCtrl, 0x2a8);

enum class AudioChannelType {
    Mono = 1,
    Stereo = 2,
    _5_1ch = 6,
    Other = -1  // TODO: does Other have a definite value?
};

// Name from the CSV (snd::ListenerPoser::ctor 0x71010549d8, init 0x7101054b30): size 0xe0, created
// in SoundMgr's init (CSV Sound::init) and stored in SoundMgr::_58. It owns an aal::Listener and the aal::ListenerPoser
// that positions it (named "snd::ListenerPoser"; the listener is the default listener).
// TODO: incomplete.
class Unk_710251b1f0;

class ListenerPoser {
public:
    // 0x71010549d8
    ListenerPoser();
    // 0x7101054a88 (D1) / 0x7101054adc (D0)
    virtual ~ListenerPoser();

    void sub_7101055100();
    // 0x7101055110 (declared only; 952 bytes): called with the event name when an event flow starts
    void sub_7101055110(const sead::SafeString& event_name);
    void sub_71010554C8();
    // 0x7101055538 (CSV unnamed): if `_70` is clear, sets it and stores `value` in `_74`.
    void sub_7101055538(s32 value);
    // 0x7101054c10: fades _a8 to 1 (`on`) or 0 in 0.5 s and stores the flag in _85.
    void sub_7101054C10(bool on);
    // 0x7101054b30 (declaration only): creates the poser (in `heap`) and the default listener.
    void init(sead::Heap* heap);

    /* 0x08 */ aal::Listener* mListener = nullptr;
    /* 0x10 */ Unk_710251b1f0* mPoser = nullptr;
    /* 0x18 */ f32 _18 = 22.5f;
    /* 0x1c */ f32 _1c = 45.0f;
    /* 0x20 */ f32 _20 = 1.0f;
    /* 0x24 */ f32 _24 = 5.0f;
    /* 0x28 */ f32 _28 = 0.25f;
    /* 0x2c */ f32 _2c = 1.0f;
    /* 0x30 */ u64 _30[4] = {};
    u8 _50[8];
    /* 0x58 */ aal::SimpleTimedFader _58{0.0f};
    /* 0x70 */ bool _70 = true;
    /* 0x74 */ s32 _74 = 0;
    /* 0x78 */ s32 _78 = 0;  // mode: 0 Normal, 5 Gyro, 6 EvtBack (ListenerSetModeAction)
    /* 0x7c */ u32 _7c = 0;
    // set to 1 / 0 by uking::action::CameraAction enter_ / leave_
    /* 0x80 */ u32 _80 = 0;
    /* 0x84 */ u8 _84 = 0;
    /* 0x85 */ bool _85 = false;
    /* 0x88 */ u32 _88 = 1;
    /* 0x90 */ aal::SimpleTimedFader _90{1.0f};
    /* 0xa8 */ aal::SimpleTimedFader _a8{0.0f};
    /* 0xc0 */ f32 _c0 = 1.0f;
    /* 0xc4 */ u32 _c4 = 0;
    /* 0xc8 */ u32 _c8 = 0;
    /* 0xcc */ u32 _cc = 0;
    /* 0xd0 */ u32 _d0 = 0;
    /* 0xd4 */ u32 _d4 = 0;
    /* 0xd8 */ u32 _d8 = 0;
    u8 _dc[4];
};
static_assert(sizeof(ListenerPoser) == 0xe0);

// Placeholder (vtable 0x7102502950; D1 0x7101056bc8, readAssetInfo 0x7101056cac): an asset info reader. At +0x68 of
// Unk_710260f248, and embedded at ResourceManager +0x28 (its address is the xlink2 SLink resource list the UI screens
// hand to their sound link users). The D1 frees a buffer of 0x50-byte res::Handle objects (`_8` count, `_10` pointer).
// Moved here from sndBgmMgr.h so that ResourceManager can embed it.
class Unk_7102502950 : public aal::IAssetInfoReadable {
public:
    // 0x7101057258 (declared only; 712 B): loads the asset info for `name`; true when done.
    bool sub_7101057258(const sead::SafeString& name, sead::Heap* heap);
    // 0x71010571a4: allocates `count` res::Handle objects (0x50 bytes each) into mHandles.
    void sub_71010571A4(s32 count, sead::Heap* heap);
    bool readAssetInfo(aal::AssetInfo* asset_info, const sead::SafeString& name, bool flag) override;
    // 0x7101056bc8
    virtual ~Unk_7102502950();

    // The loaded asset info resources (0x50-byte res::Handle objects).
    sead::Buffer<res::Handle> mHandles;
    // Bit 0 makes the owner pass this reader to its xlink2 user instance (0x7101020988).
    u8 _18 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102502950, 0x20);

// Placeholder (vtable 0x710251b500; constructor 0x71012c8968, destructor 0x71012c89e8): the 0xc8-byte member at
// ResourceManager +0x48. Owns the material entry buffers, active list, request queue and static bars handle.
class Unk_71025a36b0 {
public:
    // Native 0x71012c8968, called by ResourceManager construction.
    Unk_71025a36b0();
    virtual ~Unk_71025a36b0();
    void sub_71012C8A30(sead::Heap* heap);

    // 0x71012c911c / 0x71012c917c (declared only; both large): the entry work run before the bars loads.
    void sub_71012C911C();
    void sub_71012C917C();
    // 0x71012cbb90: unloads mHandle and the handles of the asset list at +0x8.
    void sub_71012CBB90();
    // 0x71012cbc3c / 0x71012cacd4 / 0x71012cabb4 (declared only).
    void sub_71012CBC3C();
    void sub_71012CACD4();
    void sub_71012CABB4();

    struct Entry {
        sead::FixedSafeString<40> mName;
        res::Handle mHandle;
        s16 mMaterialIndex = -1;
        u8 mState = 0;
        u8 mFlags = 0;
        s32 mPriority = -1;
        sead::ListNode mNode;
    };
    bool sub_71012CB14C();
    void sub_71012CB3A0(Entry* entry);
    bool sub_71012CB95C(aal::AssetInfo* info, Entry* entry, const sead::SafeString& asset_name,
                        bool use_static_bars);

    KSYS_CHECK_SIZE_NX150(Entry, 0xa8);
    static_assert(offsetof(Entry, mHandle) == 0x40);
    static_assert(offsetof(Entry, mState) == 0x92);
    static_assert(offsetof(Entry, mNode) == 0x98);

    /* 0x08 */ sead::Buffer<Entry> mEntries;
    /* 0x18 */ sead::Buffer<s32> mEntryIndices;
    /* 0x28 */ sead::OffsetList<Entry> mActiveEntries;
    /* 0x40 */ s32 mQueueCapacity = 0;
    /* 0x48 */ Entry** mQueueEntries = nullptr;
    /* 0x50 */ sead::Atomic<u32> mQueueWrite;
    /* 0x54 */ sead::Atomic<u32> mQueueRead;
    /* 0x58 */ Entry* mCurrentEntry = nullptr;
    /* 0x60 */ sead::Vector2i mGridCell = sead::Vector2i::zero;
    /* 0x68 */ s32 mEntryCount = 0;
    // Native 12CACD4 tests this counter modulo the update interval and increments it.
    /* 0x6c */ s32 mFrameCount = 0;
    /* 0x70 */ res::Handle mHandle;
    /* 0xc0 */ bool mUseAudioArena = true;
    /* 0xc1 */ bool mEnabled = true;
};
KSYS_CHECK_SIZE_NX150(Unk_71025a36b0, 0xc8);
static_assert(offsetof(Unk_71025a36b0, mEntries) == 0x8);
static_assert(offsetof(Unk_71025a36b0, mActiveEntries) == 0x28);
static_assert(offsetof(Unk_71025a36b0, mQueueWrite) == 0x50);
static_assert(offsetof(Unk_71025a36b0, mFrameCount) == 0x6c);
static_assert(offsetof(Unk_71025a36b0, mHandle) == 0x70);
static_assert(offsetof(Unk_71025a36b0, mEnabled) == 0xc1);

// The primary base of ResourceManager (vtable at 0x7102502a68; the object's three vtable pointers at +0 / +0x8 /
// +0x10 come from one group). Its two named virtuals are aal::IAssetList::isDirty / clearDirty (upstream's
// IDB names for 0x710105947c / 0x7101059484). This interface belongs in lib/aal (requested from the library
// worker); it is declared in the aal namespace above so the resource manager's hierarchy can be modelled.

// Placeholder (the second base of ResourceManager; its secondary vtable address point is 0x7102502ac8). A concrete
// asset info reader that never finds an asset: readAssetInfo is 0x7101059460 and the constructor stores its vtable
// at +0x8. The derived class does not override readAssetInfo, so the vtable slot points at this class's function
// directly (the original has no adjusting thunk for it).
class Unk_7102502ac0 : public aal::IAssetInfoReadable {
public:
    bool readAssetInfo(aal::AssetInfo* asset_info, const sead::SafeString& name, bool flag) override {
        return false;
    }
};

// Placeholder (the third base of ResourceManager; its vtable at 0x7102502ae0 holds only the destructor pair, so the
// interface is empty apart from its virtual destructor).
class Unk_7102502ae0 {
public:
    virtual ~Unk_7102502ae0() = default;
};

class BarslistArchive;

// Placeholder name (SoundMgr::_60): `_28` is the address of the xlink2 SLink resource list the UI screens
// (uking::ui::ScreenBase::getSlink2ResourceList_) hand to their sound link users.
// Placeholder (the member at ResourceManager +0x828, built by the ResourceManager constructor 0x7101057c4c):
// a list of named sound resources (0x710105c3d0 adds entries; 0x710105c70c / ca84 / cd4c walk the list).
struct Unk_SoundMgr60_828 {
    Unk_SoundMgr60_828();
    virtual ~Unk_SoundMgr60_828();

    struct Entry {
        sead::FixedSafeString<40> mName;
        res::Handle mHandle;
        aal::Handle mSoundHandle;
        bool _a0 = false;
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0xa8);

    class StreamPathResolver : public aal::Unk_7100BA1AEC {
    public:
        bool sub_7100BA1AEC(sead::BufferedSafeString* path, aal::AssetInfo* info) override;
    };

    // 0x710105c96c (placeholder name): sets _a0 of the entry named `name`.
    void sub_710105C96C(const sead::SafeString& name);
    // 0x710105c3d0 (declared only; 828 B): adds an entry for `name` and loads "M_<name>.bars" (`pack` is passed
    // through to ResourceManager::loadBars).
    void sub_710105C3D0(const sead::SafeString& name, res::Handle* pack);
    bool sub_710105C70C(const sead::SafeString& name);
    bool sub_710105CA84(aal::AssetInfo* info, const sead::SafeString& name, bool use_barefoot);
    void sub_710105CD4C(const sead::SafeString& name, aal::Handle handle);
    // 0x710105bd04 (declared only; 1,740 B): loads the bars the entry list refers to.
    void sub_710105BD04();

    // The constructor links 16 free slots of 0xb8 bytes at +0x34. Each slot
    // contains the 0xa8-byte entry and the ObjList node at its end.
    sead::FixedObjList<Entry, 16> mEntries;
    StreamPathResolver mStreamPathResolver;
};
KSYS_CHECK_SIZE_NX150(Unk_SoundMgr60_828, 0xbc0);

struct ResourceManager : public aal::IAssetList, public Unk_7102502ac0, public Unk_7102502ae0 {
    ResourceManager();
    // 0x7101057ed4 (CSV Sound_initBarsFactoryAndHeap).
    void initBarsFactoryAndHeap(sead::Heap* heap);
    ~ResourceManager() override;

    // The aal::IAssetList slots (0x7101059468 ... 0x7101059458): the resource manager answers "nothing to list /
    // not dirty".
    void sub_7101059468() override {}
    bool sub_710105946C() override { return false; }
    bool sub_7101059474() override { return false; }
    bool isDirty() const override { return false; }
    void clearDirty() override {}
    bool sub_7101059458() override { return false; }

    // 0x7101058348 (placeholder name): removes mArena from the resource manager task.
    void sub_7101058348();
    // 0x7101058364 (placeholder name): loads the four UI bars files into the SLink reader's buffer and the
    // three handle members.
    void sub_7101058364();
    // 0x7101058b74 (placeholder name): submits a low-priority request that runs mDelegate's function
    // 0x7101057e74 (clears the ".bars" cache and loads the title BGM pack voices).
    bool sub_7101058B74(TaskPostRunCallback* callback);
    // 0x7101058bf4 (placeholder name): runs the +0x48 entry work and the Mii voice queue hook.
    void sub_7101058BF4();
    // 0x7101058c1c (placeholder name): the same pair of hooks with the other entry and queue methods.
    void sub_7101058C1C();
    // 0x710105936c (placeholder name): unloads the SLink reader's handle and the scene static bars handle,
    // then the +0x48 member's handles.
    void sub_710105936C();
    // 0x71010593a0 (placeholder name): loads the UI bars into the SLink reader and the scene static bars into
    // _1408, then the +0x48 member's bars.
    void sub_71010593A0();
    // 0x7101059420 (placeholder name): runs the +0x48 entry work, the Mii voice queue reset and the +0x828
    // entry loads.
    void sub_7101059420();
    // 0x7101058650 (placeholder name): reloads the scene static bars, the voice cache and the expression
    // sound bars, then the title BGM pack voices.
    void sub_7101058650();
    // 0x7101057e74 (placeholder name): mDelegate's function: clears the "bars" cache and loads the title BGM
    // pack voices. Always true.
    bool sub_7101057E74(void* arg);
    // 0x7101059120 (placeholder name): loads `name` into `handle` (with `pack` as the pack handle) and sets the
    // bars file name when it is a loaded ResourceBars.
    void sub_7101059120(res::Handle* handle, res::Handle* pack, const sead::SafeString& name);
    // 0x7101058f20 (placeholder name): loads "<dir>/<name>.bars" into `handle` and returns it as a bars resource.
    ResourceBars* sub_7101058F20(res::Handle* handle, const sead::SafeString& name,
                                   const sead::SafeString& dir, bool use_audio_arena, bool lane2);
    // ResourceBars construction/destruction notifications (empty in the release build).
    void sub_7101059450(aal::AudioResource* resource);
    void sub_7101059454(aal::AudioResource* resource);
    // 0x7101058c44 (declared only; CSV SoundResourceMgrMaybe::loadBars): loads the bars file `name`
    // into `reader` (lane4 finding; the two bools are unknown). The list lane4 described (a buffer of 0x50-byte
    // entries at +8 and a flags byte at +0x18) is the asset info reader Unk_7102502950 (its res::Handle buffer),
    // which is also the type of EventXlinkInfo::_a0.
    bool loadBars(const sead::SafeString& name, Unk_7102502950* reader, sead::Heap* heap, bool a4, bool a5,
                  res::Handle* pack);
    // 0x7101058d8c: requests a bars handle, optionally from a pack or the audio arena.
    bool requestLoadBars(res::Handle* handle, const sead::SafeString& name, bool use_audio_arena,
                         bool lane2, u32 buffer_size, res::Handle* pack);
    // 0x7101058734 (declared only; 248 B): loads the asset info of `name` into `reader`.
    void sub_7101058734(const sead::SafeString& name, Unk_7102502950* reader, sead::Heap* heap, bool flag);
    // 0x710105844c: loads "Sound/Resource/<name>" into `handle` (on the audio arena when `use_audio_arena`, lane 2
    // when `lane2`) and returns it as a bars resource; once it is loaded (status 4) its file name is set.
    ResourceBars* sub_710105844C(res::Handle* handle, const sead::SafeString& name, bool use_audio_arena,
                                   bool lane2);
    // 0x7101059354 (CSV Curl_protocol_getsock was wrong): deletes the asset info reader (vtable slot 2 is its D0).
    void sub_7101059354(Unk_7102502950* reader);
    // 0x7101058198 (CSV sound::tryLoadResource): loadDirectResource into a local; null when it fails.
    sead::DirectResource* tryLoadResource(const sead::SafeString& path, sead::Heap* heap, s32 alignment);
    // 0x7101059248 (CSV soundStuff_2): loads `path` through ResourceMgrTask (on mHeap when `heap` is null) and stores
    // the resource in `out` when it is a sead::DirectResource.
    bool loadDirectResource(sead::DirectResource** out, const sead::SafeString& path, sead::Heap* heap,
                            s32 alignment);

    // The default heap of loadDirectResource.
    /* 0x18 */ sead::Heap* mHeap = nullptr;
    /* 0x20 */ OverlayArena* mArena = nullptr;
    // An asset info reader; its address is the xlink2 SLink resource list (see above).
    /* 0x28 */ Unk_7102502950 mSlinkResources;
    /* 0x48 */ Unk_71025a36b0 _48;
    /* 0x110 */ Unk_710251b710 mMiiSoundRequests;
    /* 0x828 */ Unk_SoundMgr60_828 _828;
    /* 0x13e8 */ Unk_7102502950 _13e8;
    /* 0x1408 */ res::Handle _1408;
    /* 0x1458 */ res::Handle _1458;
    /* 0x14a8 */ res::Handle _14a8;
    // Allocated with 16 slots by Sound_initBarsFactoryAndHeap (0x7101057ed4) and freed by the destructor.
    /* 0x14f8 */ sead::PtrArrayImpl mBars;
    /* 0x1508 */ sead::CriticalSection _1508;
    // The delegate of the low-priority request submitted by sub_7101058B74; its function is 0x7101057e74.
    /* 0x1548 */ sead::Delegate1R<ResourceManager, void*, bool> mDelegate;
    /* 0x1568 */ sead::CriticalSection _1568;
    /* 0x15a8 */ sead::FixedSafeString<32> _15a8;
    /* 0x15e0 */ sead::DirectResource* _15e0 = nullptr;
    /* 0x15e8 */ BarslistArchive* _15e8;
    // Native ResourceManager construction clears this whole word.
    /* 0x15f0 */ u64 _15f0 = 0;
    /* 0x15f8 */ res::Handle _15f8;
    /* 0x1648 */ res::Handle _1648;
};
KSYS_CHECK_SIZE_NX150(ResourceManager, 0x1698);

// 0x710105882c: loads the voices of the title BGM pack.
void loadVoiceFromTitleBGPack(ResourceManager* resource_manager);

// Placeholder: the property definition source passed to sub_710105E3D0 (it reads the definitions and their
// count through vtable slots 3 and 4).
class Unk_710105E3D0Arg;
// 0x710105e3d0 (declaration only; placeholder name): creates an SLink user instance `name` on `heap`
// (null when sound is disabled).
xlink2::UserInstanceSLink* sub_710105E3D0(const char* name, sead::Heap* heap,
                                          aal::IAssetInfoReadable* reader, xlink2::IUser* user,
                                          Unk_710105E3D0Arg* defs);

// Placeholder name = vtable address (0x7102502410; only the destructor pair). A buffer of shared xlink user
// instances (the members built by the Unk_SoundMgr38_* constructors: 0x710102eba0, 0x71012c153c, ...).
class Unk_7102502410 {
public:
    // 0x60-byte entry: a reference-counted SLink user instance with its asset info reader.
    struct Entry {
        // 0x7101049660 / 0x71010496e8 (vtable 0x71025023f0).
        virtual ~Entry() { finalize(); }
        // 0x7101049778 (placeholder name): once the bars are loaded, attaches the asset info reader (_18 = 2),
        // or frees it when loading failed.
        void sub_7101049778();
        // 0x7101049824 (placeholder name): loads the bars of the user instance's user name into a new asset
        // info reader once (_18 becomes 1).
        bool sub_7101049824();

        // inline-only in the original; name is a guess. The destructor and Unk_7102502410::sub_710104993C
        // both free the asset info reader and destroy the user instance this way.
        void finalize();

        /* 0x08 */ xlink2::UserInstanceSLink* mUserInstance = nullptr;
        /* 0x10 */ Unk_7102502950* mAssetInfoReader = nullptr;
        // 0: not loaded, 1: bars loading (sub_7101049824), 2: asset info reader attached (sub_7101049778).
        /* 0x18 */ u32 _18 = 0;
        /* 0x1c */ s32 mRefCount = 0;
        /* 0x20 */ sead::CriticalSection mCS;
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0x60);

    // 0x710104990c
    Unk_7102502410();
    // 0x7101049928 / 0x7101049ac4
    virtual ~Unk_7102502410();
    // 0x710104993c (declaration only; placeholder name): releases the entries (the destructor's body).
    void sub_710104993C();
    // 0x7101049c60 (placeholder name): updates every entry and runs preCalc / postCalc of the referenced ones.
    void sub_7101049C60();
    // 0x7101049af8 (placeholder name): once, creates one entry per name with a sleeping SLink user instance.
    void sub_7101049AF8(const sead::Buffer<const char*>& names, Unk_710105E3D0Arg* defs, sead::Heap* heap);
    // 0x7101049cec (placeholder name): the entry whose user name is `name`, with a new reference (the first
    // one activates the user instance and starts loading its bars); null when there is none.
    Entry* sub_7101049CEC(const sead::SafeString& name);

    sead::Buffer<Entry> mEntries;
};
KSYS_CHECK_SIZE_NX150(Unk_7102502410, 0x18);

// Placeholder name = vtable address (0x7102502430; only the destructor pair): a named reference to an
// Unk_7102502410::Entry (12 owners destroy it inline).
class Unk_7102502430 {
public:
    // 0x7101049ea0
    Unk_7102502430();
    // 0x710104a014 / 0x710104a058
    virtual ~Unk_7102502430();
    // 0x710104a0d4 (placeholder name): releases the entry and clears the owner.
    virtual void sub_710104A0D4();
    // 0x710104a1b8 (placeholder name): when _10 is set and the handle is no longer active, takes a reference
    // to the owner's entry named _10; once that entry is ready, emits mName on its user instance.
    virtual void sub_710104A1B8();
    // 0x710104a964 / 0x710104a968 (empty): called before / after the emit.
    virtual void m4(xlink2::UserInstanceSLink* user_instance) {}
    virtual void m5(xlink2::UserInstanceSLink* user_instance, xlink2::HandleSLink* handle) {}
    // 0x710104a098 (placeholder name): stores `owner` and `name` once.
    void sub_710104A098(Unk_7102502410* owner, const sead::SafeString& name);
    // 0x710104a108 (placeholder name): drops the reference to _98; the last one frees its asset info reader
    // and puts the user instance to sleep.
    void sub_710104A108();
    // 0x710104a308 (placeholder name): fades a looping emit and clears _10; if `name` is the referenced entry's
    // user name, emits mName once the entry is ready (else sets _68), otherwise stores `name` in _10.
    void sub_710104A308(const sead::SafeString& name);
    // 0x710104a5e8 (placeholder name): when the entry is ready, fades a looping emit and emits mName again.
    void sub_710104A5E8();
    // 0x710104a76c (placeholder name): fades the emitted event over `frame` frames and clears _10.
    void sub_710104A76C(s32 frame);
    // 0x710104a2e8 (placeholder name): whether the referenced entry's state _18 is 2.
    bool sub_710104A2E8() const;
    // 0x710104a858 (placeholder name)
    bool sub_710104A858() const;
    // 0x710104a8ac (placeholder name): no entry referenced and _10 empty.
    bool sub_710104A8AC() const;
    // 0x710104a94c (CSV name SLinkSoundEmitter::getUserInstance): the user instance of the referenced entry.
    xlink2::UserInstanceSLink* getUserInstance() const;

    /* 0x08 */ bool mIsSet = false;
    /* 0x10 */ sead::FixedSafeString<64> _10{sead::SafeString::cEmptyString};
    /* 0x68 */ u8 _68 = 0;
    /* 0x70 */ sead::SafeString mName{sead::SafeString::cEmptyString};
    /* 0x80 */ xlink2::HandleSLink mHandle;
    /* 0x90 */ Unk_7102502410* mOwner = nullptr;
    /* 0x98 */ Unk_7102502410::Entry* _98 = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_7102502430, 0xa0);

class Unk_SoundMgr38_58 {
public:
    // 0x71010284c4 / 0x7101028524
    virtual ~Unk_SoundMgr38_58();
    void sub_71010289CC();
    // 0x7101028690: resets every entry, then frees and deletes mInstances (called before deletion).
    void sub_7101028690();
    // 0x7101028710 (placeholder name): per-frame update of the time zone and the entries (under mCS).
    void sub_7101028710();
    // 0x7101028954 (placeholder name): stops all events of the entries' user instances.
    void sub_7101028954(s32 arg);
    // 0x710102880c (placeholder name): stores the time zone (from the world time, or Unk_SoundMgr38::_140 when it
    // is not negative) in mTimeZone.
    void sub_710102880C();

    // CSV name (BirdChirpSoundEmitter::onPreEmit at 0x7101029104): a named sound reference with a position and a
    // property value (0xc0 bytes; four of them from +8).
    struct BirdChirpSoundEmitter : Unk_7102502430 {
        // 0x71010290dc / 0x71010290e0
        ~BirdChirpSoundEmitter() override;
        // 0x7101029104 (CSV onPreEmit): sets property 0 of the user instance to mPropertyValue.
        void m4(xlink2::UserInstanceSLink* user_instance) override;
        // 0x710102911c: moves the emitted event to mPos.
        void m5(xlink2::UserInstanceSLink* user_instance, xlink2::HandleSLink* handle) override;

        /* 0xa0 */ u32 _a0 = 0;
        /* 0xa4 */ sead::Vector3f mPos = sead::Vector3f::zero;
        /* 0xb0 */ f32 mPropertyValue = 0.0f;
        u8 _b4[0xc0 - 0xb4];
    };
    using Entry = BirdChirpSoundEmitter;

    /* 0x008 */ Entry mEntries[4];
    /* 0x308 */ u8 mTimeZone : 3;
    /* 0x310 */ Unk_7102502410* mInstances;
    /* 0x318 */ sead::CriticalSection mCS;
};

class Unk_SoundMgr38_60 {
public:
    // A named sound reference with a position (0xb8 bytes; six of them from +8).
    struct Entry : Unk_7102502430 {
        // 0x71012c1ef0 / 0x71012c1ef4
        ~Entry() override;
        // 0x71012c1f18 (empty)
        void m4(xlink2::UserInstanceSLink* user_instance) override;
        // 0x71012c1f1c: moves the emitted event to mPos.
        void m5(xlink2::UserInstanceSLink* user_instance, xlink2::HandleSLink* handle) override;

        /* 0xa0 */ sead::Vector3f mPos = sead::Vector3f::zero;
        /* 0xac */ s32 mId = 0;
        /* 0xb0 */ s32 _b0 = -1;
        u8 _b4[0xb8 - 0xb4];
    };

    // 0x71012c1308
    Unk_SoundMgr38_60();

    virtual ~Unk_SoundMgr38_60();
    // 0x71012c17b4 (empty in the release build)
    void sub_71012C17B4();
    // 0x71012c167c (declared only): called before deletion.
    void sub_71012C167C();
    // 0x71012c171c (placeholder name): under mCS, updates mInstances and every entry.
    void sub_71012C171C();
    // 0x71012c17b8 (placeholder name): under mCS, takes a free entry for `name`, sets its position, rebinds it
    // to `name` and gives it the next id (returned; -1 without a free entry).
    s32 sub_71012C17B8(const sead::SafeString& name, const sead::Vector3f& pos, s32 value);
    // 0x71012c1d2c (placeholder name): fades out (over `frame` frames) and frees the entry with id `id`.
    void sub_71012C1D2C(s32 id, s32 frame);
    // 0x71012c1e3c (placeholder name): whether the entry with id `id` is still playing.
    bool sub_71012C1E3C(s32 id) const;
    // 0x71012c1860 (declaration only; placeholder name): the entry to use for `name` (null if none is free).
    Entry* sub_71012C1860(const sead::SafeString& name);

    /* 0x008 */ Entry mEntries[6];
    // The shared user instance buffer the entries reference (updated by sub_71012C171C).
    /* 0x458 */ Unk_7102502410* mInstances = nullptr;
    /* 0x460 */ sead::CriticalSection mCS;
    /* 0x4a0 */ s32 mNextId = 0;
    /* 0x4a4 */ bool _4a4 = false;
    /* 0x4a8 */ f32 _4a8 = 20.0f;
    /* 0x4ac */ f32 _4ac = 120.0f;
    /* 0x4b0 */ u64 _4b0 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_SoundMgr38_60, 0x4b8);

// Placeholder name: the sound instances the AreaActionBase family (Shielding / Occlusion / Reverb) get from
// SoundMgr::_a8.
struct Unk_SoundInstance {
    explicit Unk_SoundInstance(s32 id);
    ~Unk_SoundInstance();
    bool sub_710104ACB4();
    void sub_710104ABE8();
    // Placeholder names; the callers are the Unk_SoundMgra8 list queries:
    bool sub_710104AFBC(int a);    // 0x710104afbc
    bool sub_710104AFC0(act::Actor* a);  // 0x710104afc0
    bool sub_710104B10C(act::Actor* a);
    bool sub_710104B1D8(act::Actor* a);  // 0x710104b1d8
    bool sub_710104ADB8(int a);
    bool sub_710104ACF8(map::Object* object);
    bool sub_710104AE6C(int id);
    // 0x710104ac00: the volume this instance gives `actor` (negative: none).
    f32 sub_710104AC00(ksys::act::Actor* actor);

    // 0x710104A9A0 initializes two pools; 0x710104AC00 compares map hashes and actor IDs.
    sead::FixedObjArray<u32, 32> _0;
    sead::FixedObjArray<u32, 32> _220;
    /* 0x440 */ f32 _440 = 0.0f;
    /* 0x448 */ sead::CriticalSection mCS;
    /* 0x488 */ s32 _488 = 0;
    /* 0x48c */ s32 _48c;
    /* 0x490 */ bool _490 = false;
    /* 0x491 */ bool _491 = false;
    /* 0x494 */ s32 _494 = 0;
};
static_assert(sizeof(Unk_SoundInstance) == 0x498);

// Placeholder name (SoundMgr::_a8): the manager of the sound instances the AreaActionBase family hold at +0xa0.
class Unk_SoundMgra8 {
public:
    Unk_SoundMgra8();
    virtual ~Unk_SoundMgra8();
    void sub_710104B404(sead::Heap* heap);
    void sub_710104B408();
    Unk_SoundInstance* sub_710104B480(s32 id);
    // 0x710104b554 (CSV nullsub_4415): releases `instance`.
    void sub_710104B554(Unk_SoundInstance* instance);
    // 0x710104b558 (132 B): the volume the sound instance list gives `actor` (the first non-negative value of the
    // instances' 0x710104ac00 query, else -1).
    f32 sub_710104B558(ksys::act::Actor* actor);
    // 0x710104b5dc: `idx` is below the count at +0x4a70.
    bool sub_710104B5DC(u32 idx) const;
    // 0x710104b68c: the first instance for which sub_710104B1D8(a) holds, passed on to sub_710104ADB8(b); false if none.
    bool sub_710104B5F0(act::Actor* actor);
    bool sub_710104B68C(act::Actor* a, int b);
    // 0x710104b708 / 0x710104b76c: whether any instance answers sub_710104AFBC(a) / sub_710104AFC0(a).
    bool sub_710104B708(int a);
    bool sub_710104B76C(act::Actor* a);
    // 0x710104b7d0: increments (under the critical section) and returns the counter at +0x4a70.
    int sub_710104B7D0();

    /* 0x8 */ sead::CriticalSection mCS;
    /* 0x48 */ bool _48;
    /* 0x49 */ bool _49;
    u8 _4a[0x50 - 0x4a];
    /* 0x50 */ sead::PtrArray<Unk_SoundInstance> _50;
    /* 0x60 */ sead::FreeList mFreeList;
    /* 0x70 */ u8 mPoolStorage[16 * sizeof(Unk_SoundInstance)];
    /* 0x49f0 */ Unk_SoundInstance* mPointerStorage[16];
    /* 0x4a70 */ u16 _4a70;
    /* 0x4a72 */ u16 _4a72;
};
KSYS_CHECK_SIZE_NX150(Unk_SoundMgra8, 0x4a78);

// 2026-10-07: constructor 0x710105a6f0 and node-offset setup 0x710105a718 identify
// the SoundMgr +0xa0 proxy list manager. Bodies remain owned by the sound subsystem.
class Unk_710105a6f0 {
public:
    Unk_710105a6f0();
    ~Unk_710105a6f0();
    void sub_710105A718();
    void sub_710105A734(uking::act::SoundProxy* proxy);
    void sub_710105A7B4(uking::act::SoundProxy* proxy);
    uking::act::SoundProxy* sub_710105A830(map::Object* object);

    bool _0 = false;
    sead::OffsetList<uking::act::SoundProxy> mProxies;
    sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(Unk_710105a6f0, 0x60);

// Placeholder name: game-side BGM condition queries (game data flags), implemented by GameSceneSubsys15
// (vtable 0x710246be28, created by 0x710089469c, which stores itself at SoundMgr::_c8). The interface has no vtable
// of its own in the binary.
class Unk_710246be38 {
public:
    virtual ~Unk_710246be38() = default;
    virtual void m2() = 0;
    virtual void m3() = 0;
    virtual s32 m4() = 0;
    virtual bool m5() = 0;
    virtual bool m6() = 0;
    virtual bool m7() = 0;
    virtual s32 m8() = 0;
    virtual bool m9() = 0;
};

// The parts whose playing state Unk_SoundMgrStatus::mPlayingPart tracks (SEAD_ENUM text 0x7101e26605, its
// out-of-line text function 0x7101048f38; snd::debugReportStatus prints all eight). 3 / 4 are the environment
// BGM's day / night parts, 5 the riding-horse part and 6 the horse BGM part. Every marking call site spills
// and range-checks the index because the SEAD_ENUM conversion loads it from memory.
SEAD_ENUM(PlayingPart, PlayingFieldBattleBgmEasy, PlayingFieldBattleBgmMiddle, PlayingFieldBattleBgmHard,
          PlayingEnvBgmDay, PlayingEnvBgmNight, RidingHorse, PlayingHorseBgm, PlayingSpotBgm)

// The status object at SoundMgr::_288 (snd::debugReportStatus 0x7101048b94 reads it; the environment BGM's
// hm15 marks the playing part in the byte array at +8).
class Unk_SoundMgrStatus {
public:
    // inline-only in the original; name is a guess (the environment BGM's hm15 0x7101005abc keeps the part in a
    // stack slot above its own locals, as an inlined by-value parameter).
    void setPlaying(PlayingPart part) { mPlayingPart[part] = 1; }

    u8 _0[8];
    sead::SafeArray<u8, 8> mPlayingPart;
};

// FIXME: incomplete
struct SoundMgr {
    SEAD_SINGLETON_DISPOSER(SoundMgr)

    virtual ~SoundMgr();

public:
    f32 sub_71011FC31C();
    f32 sub_71011FC310();
    bool sub_71011FC2DC();

public:
    // 0x71011fc29c (lane2 request, s49; placeholder name): starts the ducker 0x23 of the DuckingMgr and sets bit 1 of
    // `_238`. (Public: called by uking::ui::sub_7100A9F8B0.)
    void sub_71011FC29C();
    // 0x71011fbecc: cleanup forwarding to the spatial and UI sound managers.
    void sub_71011FBECC();
    aal::Listener* sub_71011FC2D0();
    f32 sub_71011FC338();
    f32 sub_71011FC340();
    // 0x71011fc288 (declared only; lane2 s46): called by ScreenFadeDemo's slot 101 (nothing happens while the byte at 0xf8 is set)
    void sub_71011FC288();
    // 0x71011fc0c0 / 0x71011fc17c (CSV Sound::__auto4 / __auto5; declared only): `kind` 0..5, `bit` the bit set in the byte at 0xf8
    void sub_71011FC0C0(UiSoundKind kind, s32 bit);
    void sub_71011FC17C(UiSoundKind kind, s32 bit);
    // 0x71011fb5ac (CSV Sound::calc2; declaration only): called by MCMgr::invoked4.
    void sub_71011FB5AC();
    // 0x71011fbd58 (CSV Sound::__auto3; placeholder name): stops the sound work and marks state 1.
    void sub_71011FBD58(bool a);
    bool calc();
    void sub_71011FBDA8();
    sead::Thread* sub_71011FC348();
    void sub_71011FC394(sead::Thread* thread);

    // Tested by calc (nothing runs before Sound::init sets it).
    /* 0x28 */ bool _28;
    u8 _29[0x30 - 0x29];
    /* 0x30 */ Unk_SoundMgr30* _30;
    /* 0x38 */ Unk_SoundMgr38* _38;
    /* 0x40 */ UiSoundMgr* mUiSoundMgr;
    /* 0x48 */ Unk_SoundMgr48* _48;
    /* 0x50 */ FxMgr* _50;
    ListenerPoser* _58;
    /* 0x60 */ ResourceManager* _60;
    /* 0x68 */ xlink2::System* _68;
    /* 0x70 */ Unk_710251af30* _70;
    /* 0x78 */ OcclusionMgr* mOcclusionMgr;
    /* 0x80 */ DuckingMgr* mDuckingMgr;
    /* 0x88 */ Unk_710251af10* _88;
    /* 0x90 */ ExpressionSoundCtrl* _90;
    /* 0x98 */ Unk_710103b704* _98;
    /* 0xa0 */ Unk_710105a6f0* _a0;
    /* 0xa8 */ Unk_SoundMgra8* _a8;
    u8 _b0[0xc8 - 0xb0];
    /* 0xc8 */ Unk_710246be38* _c8;
    u8 _d0[0xd8 - 0xd0];
    // Created by 0x71011fab7c and queried through the Heap virtual interface.
    sead::Heap* mSLinkUserCreateHeap;
    // The number of calc calls.
    /* 0xe0 */ u32 _e0;
    // Whole factory 11FA364 sets 3; whole 11FB748 tests state 2.
    u32 _e4;
    u8 _e8[4];
    u32 _ec;
    u8 _f0[8];
    sead::BitFlag8 _f8;
    u8 _f9[0x198 - 0xf9];
    // Read by 0x7101035888 as the heap of the empty-name user instance and bars load.
    /* 0x198 */ sead::Heap* _198 = nullptr;
    u8 _1a0[0x238 - 0x1a0];
    u8 _238;
    // Cleared by calc after it ran sub_71011FB5AC.
    /* 0x239 */ bool _239;
    u8 _23a[0x23c - 0x23a];
    // Bit 0 is set while calc runs (an atomic test-and-set: calc returns false if it was already set).
    /* 0x23c */ sead::Atomic<u32> _23c;
    u8 _240[0x270 - 0x240];
    AudioChannelType mAudioChannelType;
    u8 _274[4];
    // Whole allocator 11FC348 passes the heap at 278 to new and the thread constructor.
    sead::Heap* _278;
    u8 _280[8];
    /* 0x288 */ Unk_SoundMgrStatus* _288;
    void* _290;
    void* _298;
    /* 0x2a0 */ Unk_SoundMgr2a0* _2a0;
};
KSYS_CHECK_SIZE_NX150(SoundMgr, 0x2a8);

// 0x7101048b94 (CSV snd::debugReportStatus; declared only): prints the status (debug report).
void debugReportStatus(Unk_SoundMgrStatus* status);

// Defined here because it needs SoundMgr.
inline void Unk_7102502410::Entry::finalize() {
    if (mAssetInfoReader) {
        SoundMgr::instance()->_60->sub_7101059354(mAssetInfoReader);
        if (mUserInstance)
            mUserInstance->setAssetInfoReader(nullptr);
        mAssetInfoReader = nullptr;
        _18 = 0;
    }
    if (mUserInstance) {
        mUserInstance->destroy();
        mUserInstance = nullptr;
    }
}

// Sound helper 105DF10 forwards a label to the dialogue sound user instance.
xlink2::HandleSLink sub_710105DF10(const sead::SafeString& label);

}  // namespace ksys::snd
