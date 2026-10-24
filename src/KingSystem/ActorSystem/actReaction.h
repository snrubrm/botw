#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadObjArray.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <cstddef>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <mc/seadCoreInfo.h>
#include <prim/seadSafeString.h>
#include <xlink2/xlink2HandleSLink.h>

#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actActorUnk6b8.h"
#include "KingSystem/Physics/System/physLayerContactPointInfo.h"
#include "KingSystem/Physics/System/physUserTag.h"
#include "KingSystem/System/DebugMessage.h"

namespace xlink2 {
class Event;
class HandleELink;
}

namespace ksys::map {
struct Unk_71012497f8Entry;
}

namespace ksys::phys {
class LayerContactPointInfo;
class MaterialMask;
}

namespace ksys::xlink {
class XLink;
}

struct DamageReactionRequest;

namespace uking::act {
class PlayerBase;
}

namespace ksys::act {
class Actor;
class ActorCreator;
class ActorUnk6b8;
class BaseProcLink;
class Unk_71024f02a8;

// The size class of a reaction event name (the "Tiny" in "CmnObj_Land_TinySize_Body").
// The text must stay unspaced: the original's enum text is "None,Tiny,...,Huge" (46 bytes).
SEAD_ENUM(ReactionSizeClass, None,Tiny,Small,Half,Normal,Double,Giant,Huge)

// The kind of a reaction event, which selects the Land / Drag / Roll name prefix.
SEAD_ENUM(ReactionKind, Land, Drag, Roll)

// Placeholder name: an actor given either directly or through a proc link (the reaction code keeps one at
// +0xa8 of its request objects; 0x7100ec545c / 0x7101284954 read it). Accessors 0x7100ebf9e4..0x7100ebfad4.
struct Unk_7100ebf9e4 {
    xlink::XLink* getXLink() const;
    // Chemical::_c0 of the actor's chemical (0 if none).
    s32 getChemicalState() const;
    const sead::SafeString& getName() const;

    Actor* mActor;
    BaseProcLink* mLink;
};

// Partial declaration. Reaction::createInstance (0x7100ec0138) stores the
// singleton at 0x71026064c0; its 0x180-byte allocation and members remain unrecovered.
// Placeholder: the receiver at Reaction::_a0. 0x7101286868 emits the slanted water reaction
// (ReactionWaterOut / ReactionWaterOut_Slant assets) for a footstep; called by 0x7100ec241c.
class Unk_7101286868 {
public:
    // 0x71012847d0 (32 B, unnamed): zeroes the object and stores the class vtable.
    Unk_7101286868();
    // The Reaction destructor deletes the receiver through vtable slot 1.
    virtual ~Unk_7101286868();
    // 0x71012847f8 (20 B, unnamed): stores the physics system at +0x28.
    void init(sead::Heap* heap);
    void sub_7101286868(f32 speed, Actor* actor, const sead::Vector3f* pos,
                        const sead::Vector3f* dir, u64 size, u64 material, u64 flag);
    void sub_7101286BF8(xlink2::HandleELink* handle, ::DamageReactionRequest* request);
    u8 _0[0x30];
    // Fallback actor used when the request actor has no emitted effect.
    /* 0x38 */ Actor* _38;
    u8 _40[0x18];
};
KSYS_CHECK_SIZE_NX150(Unk_7101286868, 0x58);

// 0x7100f70990 (144 B, unnamed): allocates and registers the physics item list stored in
// Reaction::_d0. The class is a global-namespace placeholder (its vtable is 0x71024f6670).
class Unk_71024f6670;
Unk_71024f6670* sub_7100F70990(sead::Heap* heap);
// 0x7100f70a20 (unnamed): releases and unregisters the item list `sub_7100F70990` creates.
void sub_7100F70A20(Unk_71024f6670* item);

// The reaction sound setting built on the stack by ActorUnk6b8's slide/land reaction handlers
// (0x7100ebcd48, 0x7100ebdcb0) and passed to the sound emitters 0x7100ec72a0 / 0x7100ec7468.
// Defined in actActorUnk6b8.h, which has the MaterialMask definition.
struct ReactionSetting;

// One xlink event of the reaction queue below: the actor it was emitted for, the sound handle and
// whether the event has already been emitted. The class is 0x20 bytes (its pool is allocated with
// 0x20-byte elements at 0x7101287d68).
class ActorReactionHandle {
public:
    // User-provided (the original's emplaceBack does not zero the tail padding).
    ActorReactionHandle() {}
    // 0x7101287504: fades the event out and clears the flag when the handle is no longer active.
    void update();
    // 0x71012875dc: emits `name` through the xlink user of `source` for `actor` and fills the handle.
    bool emit(Actor* actor, Actor* source, const sead::SafeString& name);
    // 0x7101287880: emits `name` for `actor` when the held event is still the same one.
    bool resume(Actor* actor, Actor* source, const sead::SafeString& name);

    /* 0x00 */ Actor* mActor = nullptr;
    /* 0x08 */ xlink2::HandleSLink mHandle;
    /* 0x18 */ bool mActive = false;
    u8 _19[7];
};
KSYS_CHECK_SIZE_NX150(ActorReactionHandle, 0x20);

// Placeholder name: the per-core reaction queue at Reaction::Unk1 + 0x30 (constructor 0x7101287a6c,
// 0xb8 bytes). Actors are queued per core on the core that registers the reaction; the queue is
// merged and sorted by the distance to the default sound listener in calc, which then emits one
// xlink event per actor. Its destructor installs vtable 0x7102519058 (D1 0x7101287afc).
class ActorReactionQueue {
public:
    ActorReactionQueue();
    virtual ~ActorReactionQueue();

    // 0x7101287d68: allocates the per-core queues for the platform core count, the merged actor
    // array and the handle pool, and stores `name` (copied into mName).
    void init(sead::Heap* heap, const sead::SafeString& name);

    // 0x7101288104: sets the actor the events are emitted for.
    void setActor(Actor* actor);
    // 0x710128810c: queues `actor` on the core `core`; false when that core's queue is full.
    bool queue(Actor* actor, const sead::CoreId& core);
    // 0x7101288184: merges the per-core queues, emits the reactions and updates the events.
    void calc();
    // 0x7101288224: merges the per-core queues into mActors and sorts them by distance to the listener.
    void merge();
    // 0x71012883e4: emits one reaction event for `actor`.
    void emit(Actor* actor);
    // 0x71012884e8: orders two actors by their distance to the default sound listener.
    static s32 compareDistance(const Actor* a, const Actor* b);

    // 0x7101287b10 (placeholder name): fades the held events and releases the queues; both
    // destructors of the queue tail-call it.
    void sub_7101287B10();

    /* 0x08 */ sead::ObjArray<sead::PtrArray<Actor>> mCoreQueues{};
    /* 0x28 */ sead::PtrArray<Actor> mActors{};
    /* 0x38 */ sead::ObjArray<ActorReactionHandle> mHandles{};
    /* 0x58 */ sead::FixedSafeString<64> mName;
    /* 0xb0 */ Actor* mActor = nullptr;
};
KSYS_CHECK_SIZE_NX150(ActorReactionQueue, 0xb8);

// Placeholder name: the list of reaction components (ActorUnk6b8) created for the current actors.
// ctor 0x7101287168, init 0x7101287218, calc 0x71012873a0 (each calc step runs ActorUnk6b8::m5).
class ActorReactions {
public:
    ActorReactions();
    // 0x7101287178: deletes the components and frees the list.
    ~ActorReactions();
    // Creates one component per actor of the list and links it at actor + 0x6b8.
    bool init(Actor* actor, sead::Heap* heap);
    void calc();
    // 0x7101287410 (placeholder name): runs m9 on every component.
    void sub_7101287410();
    // 0x7101287480 (placeholder name): runs m10 on every component once, then sets _10.
    void sub_7101287480();

    /* 0x00 */ sead::Buffer<ActorUnk6b8*> mComponents;
    /* 0x10 */ bool _10 = false;
};
KSYS_CHECK_SIZE_NX150(ActorReactions, 0x18);

class Reaction {
    SEAD_SINGLETON_DISPOSER(Reaction)
    // 0x7100ec01c0 / 0x7100ec0374 (declared only)
    Reaction();
    virtual ~Reaction();

    // 0x7100ec0458: empty in the original (CSV name).
    void initStubbed();
    // 0x7100ec0ed4 (placeholder name): resets the reaction state before the stage is generated.
    void x();
    // 0x7100ec0e7c (placeholder name): runs `x`, resets the reaction receiver, then caches the
    // player link's player in _d8.
    void sub_7100EC0E7C();
    // 0x7100ec045c: true while the five queued procs are not all ready, or when _b8 bit 9 is clear.
    bool __auto3();

public:
    // 0x7100ec0d1c (placeholder name; CSV nullsub_4046): empty in this build.
    void initBeforeStageGenB();
    // 0x7100ec07b4 (declared only): requests the reaction actors; `creator` creates them on `create_heap`.
    void initBeforeStageGen(sead::Heap* heap, sead::Heap* debug_heap, ActorCreator* creator,
                            void* param);
    // Placeholder: the object at _a8 (class unknown). 0x7100ec66fc sets its _110 to 2; the actor
    // argument is unused. Called by OctarockOptionRoot::calc_ when the player touches the rock.
    struct Unk1 {
        Unk1();
        virtual ~Unk1();
        // 0x7100ec3088: copies the current actors from the Reaction instance and hands them to
        // the reaction queue.
        void setActor();
        // 0x7100ec2fdc: sets the reaction labels on the two actors' XLinks, creates the SLink
        // limiter and initialises the reaction queue.
        void init(sead::Heap* heap);
        // 0x7100ec30c4 (placeholder name): resets the per-core reaction queues and counters.
        void sub_7100EC30C4();
        // 0x7100ec313c (placeholder name): forwards the request to the reaction handlers.
        void sub_7100EC313C(::DamageReactionRequest* request);
        // The damage-kind handlers of sub_7100EC313C (all declared only).
        void sub_7100EC4594(::DamageReactionRequest* request);
        void sub_7100EC4880(::DamageReactionRequest* request);
        void sub_7100EC4C00(xlink2::HandleSLink* handle, ::DamageReactionRequest* request);
        void sub_7100EC513C(::DamageReactionRequest* request);
        void sub_7100EC5294(Actor* actor, ::DamageReactionRequest* request);
        void sub_7100EC66FC(Actor* actor);
        // Constant getters (0.7f / 7 / 5); placeholder names.
        f32 sub_7100EC877C() const;
        s32 sub_7100EC87A4() const;
        s8 sub_7100EC89BC() const;
        // The remaining constant getters of the same group (callers are inlined, so no call sites).
        f32 sub_7100EC8770() const;
        f32 sub_7100EC8788() const;
        f32 sub_7100EC8790() const;
        s32 sub_7100EC879C() const;
        f32 sub_7100EC87AC() const;
        f32 sub_7100EC87B8() const;
        f32 sub_7100EC89B4() const;
        s32 sub_7100EC8C18() const;
        s32 sub_7100EC8C20() const;
        f32 sub_7100EC8C28() const;
        // 0x7100ec6dd0: queues `actor` for the reaction of the current core (0x710128810c); false when full.
        bool sub_7100EC6DD0(Actor* actor);
        // 0x7100ec6e30 (placeholder name): emits the "ObjHit" event and then the object-hit reaction
        // event (named from the reaction kind and the material) for `request`.
        void sub_7100EC6E30(::DamageReactionRequest* request);
        // 0x7100ec6708 (placeholder name): emits the WaterTrack event for the actor at the request
        // position; the event name depends on the water material or the grudge property.
        void sub_7100EC6708(Actor* actor, ::DamageReactionRequest* request);
        // 0x7100ec6070: emits the GrassTrack effect and the xlink properties for `request`.
        void sub_7100EC6070(f32 value, ::DamageReactionRequest* request, bool flag);
        // 0x7100ec61f8: fills the receiver from `request` (position, link, xlink properties).
        void sub_7100EC61F8(::DamageReactionRequest* request);
        // 0x7100ec8f78: emits the water reaction asset for a footstep on `actor` (sets xlink
        // properties 4 / 6 / 0 / 9 or 10, 608 B).
        void sub_7100EC8F78(f32 speed, Actor* actor, const sead::Vector3f* pos, u64 size,
                            u64 material, u64 flag);
        // 0x7100ec87c4: emits the "RagdollLand" effect for the reaction's second actor and scales
        // its volume from how far the fall exceeded the landing threshold.
        // The mask is passed by value: the caller copies it into the argument slot.
        xlink2::HandleSLink sub_7100EC87C4(Actor* actor, const sead::Vector3f& position,
                                           phys::MaterialMask mask, f32 offset, bool flag);
        // 0x7100ec8c30: the "OutCarryBoxLand" reaction of a carried box that lands. Casts a ray
        // down from the actor and applies the hit material properties to its SLink user.
        bool sub_7100EC8C30(Actor* actor);
        // 0x7100ec89d8 (declared only): emits the water flow splash event `name` with the limiter
        // group `size` for `actor` at `position`; `value` is the reaction size from EC2278.
        void sub_7100EC89D8(f32 a, Actor* actor, const sead::Vector3f& position, ReactionSize size,
                            const phys::MaterialMask& mask, const char* name, int group);
        // 0x7100ec89c4 / 0x7100ec8c04: "WaterFlowSplashMove" (group 11) and "WaterFlowSplash"
        // (group 5) wrappers around sub_7100EC89D8.
        void sub_7100EC89C4(f32 a, Actor* actor, const sead::Vector3f& position, u64 value,
                            const phys::MaterialMask& mask);
        void sub_7100EC8C04(f32 a, Actor* actor, const sead::Vector3f& position, u64 value,
                            const phys::MaterialMask& mask);

        // Sound emission and property setup for the request source.
        void sub_7100EC539C(::DamageReactionRequest* request, xlink2::HandleSLink* handle,
                           const char* name);
        void sub_7100EC447C(Actor* actor, ::DamageReactionRequest* request,
                           xlink2::HandleSLink* handle, const char* name);
        void sub_7100EC56D8(xlink::XLink* xlink, ::DamageReactionRequest* request);
        void sub_7100EC545C(xlink2::HandleSLink* handle, ::DamageReactionRequest* request);
        bool sub_7100EC6408(map::Unk_71012497f8Entry* entry);
        bool sub_7100EC64FC(f32 speed, xlink::XLink* xlink, const sead::Vector3f& position);
        void sub_7100EC5B64(const sead::Vector3f& position);
        bool sub_7100EC5C30(f32 speed, f32 value, Actor* actor, const sead::Vector3f& position);
        bool sub_7100EC5C40(f32 speed, f32 value, Actor* actor, const sead::Vector3f& position,
                           s32 size, u32 flags, const phys::MaterialMask* mask);
        // EC6C00 forwards the same receiver to the puddle-sound emitter. Body remains
        // undecompiled while the SLink property-pointer null-check protocol is unresolved.
        bool sub_7100EC696C(f32 speed, Actor* actor, const sead::Vector3f& position,
                           bool stone_bottom, bool flag);
        // Two AI callers pass Reaction::_a8, their actor and its matrix translation.
        void sub_7100EC6C00(Actor* actor, const sead::Vector3f& position);

        // 0x7100ec7aa0 (placeholder name): sets the material and wetness properties of the effect
        // link from the material mask.
        bool sub_7100EC7AA0(const phys::MaterialMask& mask, s32 flag, f32 value);
        // 0x7100ec7edc (placeholder name): emits the roll-drag asset of the size class for `speed`.
        bool sub_7100EC7EDC(f32 speed, xlink2::HandleSLink* handle);
        // 0x7100ec86f4 (placeholder name): sets the event position of `handle`, then applies the
        // volume and pitch scales from the four values (sub_7100EC7D50).
        // The parameter order is (handle, position, volume base, distance, volume factor, pitch factor).
        void sub_7100EC86F4(xlink2::HandleSLink* handle, const sead::Vector3f& position, f32 a, f32 b,
                            f32 c, f32 d, bool flag);
        // Volume / pitch scale calculation behind sub_7100EC86F4.
        // The second and third floating-point inputs are unused by the native callee.
        void sub_7100EC7B90(f32 a, f32, f32, f32 d, f32 e, f32 f, f32 g,
                            xlink2::HandleSLink* handle, const xlink2::HandleSLink* other,
                            f32* volume, f32* pitch);
        void sub_7100EC7D50(f32 a, f32 b, f32 c, f32 d, xlink2::HandleSLink* handle, f32* volume,
                            f32* pitch);
        // 0x7100ec88f8 (placeholder name): sets the volume scale of `handle` from the incoming
        // value: the value is shifted by -0.2 and scaled by 1/8 (flag) or 1/4, clamped to [0, 1],
        // squared and floored at 0.2 / 0.4.
        void sub_7100EC88F8(f32 value, xlink2::HandleSLink* handle, bool flag);
        // 0x7100ec72a0 (declared only): emits the reaction sound described by `setting` for
        // `handle` at `position` (slide/land reaction handlers 0x7100ebcd48 / 0x7100ebdcb0).
        void sub_7100EC72A0(xlink2::HandleSLink* handle, const sead::Vector3f& position,
                            const ReactionSetting& setting);
        // 0x7100ec7468 (declared only): builds the reaction event name from the setting's kind and
        // size class; false when the name is empty.
        bool sub_7100EC7468(sead::FixedSafeString<64>& name, const ReactionSetting& setting);
        // 0x7100ec7fbc: builds the "CmnObj_" reaction event name of a size class and a material
        // name for the auto-sized reaction settings.
        void sub_7100EC7FBC(sead::FixedSafeString<64>* name, ReactionKind kind, ReactionSizeClass size,
                            const sead::SafeString& material);

        /* 0x08 */ Actor* _8 = nullptr;
        /* 0x10 */ Actor* _10 = nullptr;
        /* 0x18 */ Actor* _18 = nullptr;
        /* 0x20 */ xlink2::HandleSLink mGrassCutHandle;
        // The per-core reaction queue.
        /* 0x30 */ ActorReactionQueue mReactions;
        /* 0xe8 */ Unk_71024f02a8* mSLinkLimiter = nullptr;
        // The BushTrack request producer stores its position, speed and emitted state here.
        /* 0xf0 */ sead::Vector3f mBushTrackPosition = sead::Vector3f::zero;
        /* 0xfc */ f32 mBushTrackSpeed = 0;
        /* 0x100 */ bool mHasBushTrack = false;
        // Player::m377 writes whether lower armor is Armor_Default_Lower; footstep assets use it.
        /* 0x101 */ bool mIsPlayerBarefoot = false;
        u8 _102 = 0;
        /* 0x103 */ u8 _103 = 0;
        // Per-reaction-kind emitted flags: bit 0 for the Hit kind, bit 1 for the others.
        /* 0x104 */ u8 _104 = 0;
        u8 _105[3];
        // Sound-reaction counter pair: 0x7100ebdcb0 skips the slide reaction while the sum exceeds
        // 2 and increments _10c after emitting.
        /* 0x108 */ s32 _108 = 0;
        /* 0x10c */ s32 _10c = 0;
        /* 0x110 */ s32 _110 = 0;
        /* 0x114 */ s32 _114 = 0;
        /* 0x118 */ s32 _118 = 0;
        u8 _11c[4]{};
    };

    // 0x7100ec1c24 (placeholder name): sets the material, sub material and wetness properties of
    // both xlink user instances of `actor`. Called twice by 0x7100ec134c.
    void sub_7100EC1C24(Actor* actor, const phys::MaterialMask& mask) const;
    // 0x7100ec1d98 (placeholder name): terrain height below `pos`, or -9999 while the terrain is
    // not shown. Called twice by 0x7101285930, which passes its +0x28 pointer as the receiver.
    f32 sub_7100EC1D98(const sead::Vector3f& pos) const;
    // 0x7100ec10b8 (CSV __auto6): passes `request` on to the reaction targets when the instance's
    // +0xb0 flag is set (bits 2 / 1 of request->_c4 select 0x7101284954 / 0x7100ec313c); true.
    bool sub_7100EC10B8(::DamageReactionRequest* request);
    // 0x7100ec2980 / 0x7100ec299c / 0x7100ec29b8: forwarded to the receiver at _a8 while _b0 is set.
    bool sub_7100EC2980(Actor* actor);
    void sub_7100EC299C(f32 value, ::DamageReactionRequest* request, bool flag);
    void sub_7100EC29B8(::DamageReactionRequest* request);
    // Surface raycast/XLink update called by GolemRootBase::calc_; declaration only.
    void sub_7100EC29D0(Actor* actor);
    // 0x7100ec2278 (placeholder name): size class 0-4 of the actor from the local AABB of its main body
    // (2 or 3 from the height alone without one). `is_long` (optional) is set when the body is longer than
    // 4.5 and much thinner in the other two directions.
    u64 sub_7100EC2278(Actor* actor, bool* is_long);
    // 0x7100ec2598: the moving water footstep reaction: casts 5 / 10 units along the velocity and
    // forwards the speed along the hit normal with flag 1.
    void sub_7100EC2598(Actor* actor);
    // 0x7100ec27fc: the water footstep reaction: casts down 5 / 10 units on the water layer and
    // forwards the hit position and normal to the two receivers with flag 2.
    void sub_7100EC27FC(Actor* actor);
    // 0x7100ec241c: the footstep reaction of `actor` on contact `info`: stores 15.0 in the footstep
    // timer, picks the material mask from the contact type and forwards the speed to the two receivers.
    void sub_7100EC241C(Actor* actor, phys::UserTag::Unk5* info);

    // EC04D0 stores an Actor cast from the released handle; EC0D20 deletes the same actor.
    // EC04D0 releases the first handle and dynamically casts it to Actor here.
    Actor* _28;
    Actor* _30;
    Actor* _38;
    u8 _40[8];
    /* 0x48 */ Actor* _48 = nullptr;
    /* 0x50 */ BaseProcHandle mHandles[5];
    /* 0xa0 */ Unk_7101286868* _a0;
    /* 0xa8 */ Unk1* _a8;
    /* 0xb0 */ bool _b0;
    u8 _b1[0xb8 - 0xb1];
    /* 0xb8 */ u32 _b8;
    /* 0xbc */ u32 _bc;
    // Contact point managers created by initBeforeStageGen.
    /* 0xc0 */ phys::LayerContactPointInfo* _c0 = nullptr;
    /* 0xc8 */ phys::LayerContactPointInfo* _c8 = nullptr;
    /* 0xd0 */ Unk_71024f6670* _d0 = nullptr;
    /* 0xd8 */ uking::act::PlayerBase* _d8 = nullptr;
    // The dtor's second vtable store (0x7100ec0374) is this member's DebugMessage vtable.
    /* 0xe0 */ DebugMessage _e0;
    u8 _170[0x180 - 0x170];
};
static_assert(offsetof(Unk_7101286868, _38) == 0x38);
static_assert(offsetof(Reaction, _28) == 0x28);
KSYS_CHECK_SIZE_NX150(Reaction, 0x180);
static_assert(offsetof(Reaction::Unk1, _8) == 0x8);
static_assert(offsetof(Reaction::Unk1, _10) == 0x10);
static_assert(offsetof(Reaction::Unk1, mGrassCutHandle) == 0x20);
static_assert(offsetof(Reaction::Unk1, mSLinkLimiter) == 0xe8);
static_assert(offsetof(Reaction::Unk1, mBushTrackPosition) == 0xf0);
static_assert(offsetof(Reaction::Unk1, mBushTrackSpeed) == 0xfc);
static_assert(offsetof(Reaction::Unk1, mHasBushTrack) == 0x100);
static_assert(offsetof(Reaction::Unk1, mIsPlayerBarefoot) == 0x101);
static_assert(offsetof(Reaction::Unk1, _118) == 0x118);
static_assert(offsetof(ActorReactionQueue, mActors) == 0x28);
static_assert(offsetof(ActorReactionQueue, mHandles) == 0x38);
static_assert(offsetof(ActorReactionQueue, mName) == 0x58);
static_assert(offsetof(ActorReactionQueue, mActor) == 0xb0);

// 0x7100ebfea8 (CSV unnamed; named by its address): builds the matrix of a footstep reaction
// request from the contact axis / up / position and copies `scale` into the three floats at
// 0x3c / 0x40 / 0x44.
void sub_7100EBFB5C(f32 scale, ::DamageReactionRequest* request, const sead::Vector3f& up,
                    const sead::Vector3f& position);
void sub_7100EBFD08(f32 scale, ::DamageReactionRequest* request, const sead::Vector3f& up,
                    const sead::Vector3f& position);
void sub_7100EBFEA8(f32 scale, ::DamageReactionRequest* request, const sead::Vector3f& axis,
                    const sead::Vector3f& up, const sead::Vector3f& pos);

}  // namespace ksys::act
