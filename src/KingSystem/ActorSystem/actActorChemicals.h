#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadBoundBox.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include <prim/seadScopedLock.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Chemical/chmRoot.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::world {
class ChemicalMgr;
}

namespace ksys::xlink {
class XLink;
class ChemicalEventState;
}

namespace ksys::phys {
class RigidBody;
class RigidBodySet;
class InstanceSet;
class SystemGroupHandler;
class UserTag;
}

namespace ksys::act {

class Actor;
// E40448 selects the shape centre from real Sphere / Box / Cylinder / Capsule bodies.
void sub_7100E40448(sead::Vector3f* out, phys::RigidBody* body);
f32 sub_7100E40698(phys::RigidBody* body);
void sub_7100E3F3E8(phys::RigidBody* body, const Chemical* chemical, world::ChemicalMgr* manager);

// Placeholder name (vtable 0x71024e6560, 37 slots): the interface the Chemical calls back through its owner
// (Chemical::_18) and the base class of Unk_71024e6428. All virtuals have trivial default bodies (the
// out-of-line copies sit at 0x7100e3f1e0-0x7100e3f3ac); the signatures are guesses from the overrides of
// Unk_71024e6428 (arguments are only known for m4 / m14).
class Unk_71024e6560 {
    SEAD_RTTI_BASE(Unk_71024e6560)
public:
    Unk_71024e6560() = default;
    virtual ~Unk_71024e6560();

    // Element override 0x7100e3e328: the transform of the first rigid body.
    virtual void m4(sead::Matrix34f* out, Chemical* chemical) {}
    // Element overrides return the vectors at +0x2a4 / +0x2b0.
    virtual const sead::Vector3f& m5() const { return sead::Vector3f::zero; }
    virtual const sead::Vector3f& m6() const { return sead::Vector3f::zero; }
    virtual void m7() {}
    virtual void m8(const void* a1) {}
    virtual void m9() {}
    virtual void m10() {}
    virtual void m11() {}
    virtual void m12() {}
    virtual const sead::SafeString& getName() const { return sead::SafeString::cEmptyString; }
    virtual void m14(sead::BufferedSafeString* out) const {}
    virtual bool m15(u32 a1) const { return false; }
    virtual bool m16() const { return false; }
    virtual bool m17() const { return false; }
    virtual bool m18() const { return false; }
    virtual bool m19() const { return false; }
    virtual bool m20() const { return false; }
    virtual bool m21() const { return false; }
    virtual bool m22(u32 a1) const { return true; }
    virtual f32 m23() const { return 1.0f; }
    virtual f32 m24() const { return 1.0f; }
    virtual f32 m25() const { return 1.0f; }
    virtual f32 m26() const { return 1.0f; }
    virtual void m27(f32 a1) {}
    virtual bool m28() { return false; }
    virtual bool m29(const void* a1) { return true; }
    virtual f32 m30(const void* a1) { return 1.0f; }
    virtual bool m31() { return true; }
    virtual void m32(bool a1) {}
    virtual bool m33() { return false; }
    virtual void m34() {}
    virtual bool m35() { return false; }
    virtual bool m36() { return true; }
};

// Declared only (lane4 s50; placeholder names, signatures from Unk_71024e6428::m28 / m30): 0x7100e41470 casts a ray
// (RayCastBodyQuery) at the vector with the actor's group handler; 0x7100e40b7c computes a value per rigid body entry.
bool sub_7100E41470(const sead::Vector3f& pos, phys::SystemGroupHandler* handler);
f32 sub_7100E40B7C(phys::RigidBody* body, const void* a1, const void* entry_24);

// Placeholder name (vtable 0x71024e6428, 37 slots; ctor 0x7100e399c0; size 0x2d8): an element of
// ActorChemicals' arrays and the owner of its Chemical (Chemical::_18).
// TODO: complete the remaining virtual and initialization bodies.
class Unk_71024e6428 : public Unk_71024e6560 {
    SEAD_RTTI_OVERRIDE(Unk_71024e6428, Unk_71024e6560)
public:
    Unk_71024e6428();
    ~Unk_71024e6428() override;
    // E39BF0 fades the state, removes every body and returns whether the chemical was reset.
    bool sub_7100E39BF0(bool force);
    // E37224 supplies the actual root, physics instance and optional actor to this full setup.
    void sub_7100E39E8C(s32 index, const chm::IRoot* root, phys::InstanceSet* instance,
                       Actor* actor, sead::Heap* heap);
    // Full E3B708 copies chemical event state; independent carried-record transfers supply both elements.
    void sub_7100E3B708(const Unk_71024e6428& other);
    void sub_7100E3AA34(sead::Heap* heap);
    // Native caller passes zero; the full callee does not consume its second input.
    void sub_7100E3AE40(u32 unused);
    void sub_7100E3B144();
    void sub_7100E3B3F4(Chemical* chemical);
    void sub_7100E3B87C();
    void sub_7100E3BE78();

    // 0x7100e3e2e8: marks the element and resets each linked rigid body.
    void sub_7100E3E2E8();
    // E3B79C: the parent actor chemical, consumed by the wind/rigid-body update.
    Chemical* sub_7100E3B79C() const;
    void sub_7100E3B6D8(phys::UserTag* tag);
    // E3D4E8 stops one chemical effect and optionally emits its end sound.
    void sub_7100E3D4E8(u32 kind, bool emit_end);
    // E39DF4 stops all twenty-one event slots; E3ECA4 stops slots 0 / 19 and their slot-20 alias.
    void sub_7100E39DF4();
    void m34() override;

    // Slot numbering: mN is the virtual at vtable slot N + 2 (the first two are the RTTI functions), as in the CSV.
    // Native table 24e6438 retains these declarations even where their bodies are still U.
    void m7() override;
    void m8(const void* arg) override;
    void m9() override;
    void m10() override;
    void m11() override;
    void m12() override;
    void m14(sead::BufferedSafeString* out) const override;
    bool m29(const void* arg) override;
    void m32(bool on) override;
    bool m35() override;

    void m4(sead::Matrix34f* out, Chemical* chemical) override;
    const sead::Vector3f& m5() const override;
    const sead::Vector3f& m6() const override;
    const sead::SafeString& getName() const override;
    bool m15(u32 a1) const override;
    bool m16() const override;
    bool m17() const override;
    bool m18() const override;
    bool m19() const override;
    // 0x7100e3e8d0: whether the first rigid body is on a sensor layer (HitOnlyInDoor / NoHit); true without one.
    bool m20() const override;
    bool m21() const override;
    bool m22(u32 a1) const override;
    f32 m23() const override;
    f32 m24() const override;
    f32 m25() const override;
    f32 m26() const override;
    void m27(f32 value) override;
    bool m28() override;
    f32 m30(const void* a1) override;
    bool m31() override;
    bool m33() override;
    bool m36() override;

    // The rigid bodies of the element (stride 0x40; the entry's first member is the body).
    struct BodyEntry {
        phys::RigidBody* body;
        // E3A570 keeps the source body and its actual InstanceSet body set.
        /* 0x08 */ phys::RigidBody* original_body;
        /* 0x10 */ phys::RigidBodySet* body_set;
        // E3A570 sets this for a cloned body; E39A70 deletes only owned bodies.
        /* 0x18 */ bool owns_body;
        /* 0x19 */ u8 _19;
        u8 _1a[2];
        /* 0x1c */ f32 original_scale;
        // E40698 supplies this radius; m32 restores it when the parent condition changes.
        /* 0x20 */ f32 original_radius;
        // E3AE40 fills this bounds record with RigidBody::getAabbInLocal.
        /* 0x24 */ sead::BoundBox3f aabb;
        u8 _3c[4];
    };

    static_assert(sizeof(BodyEntry) == 0x40);
    static_assert(offsetof(BodyEntry, original_body) == 0x8);
    static_assert(offsetof(BodyEntry, body_set) == 0x10);
    static_assert(offsetof(BodyEntry, original_radius) == 0x20);
    static_assert(offsetof(BodyEntry, aabb) == 0x24);

    /* 0x008 */ Actor* mActor;
    // E3AA34 and carried activation copy the placement EffectEntry's XLink here.
    /* 0x010 */ xlink::XLink* mPlacementXLink;
    // 2026-10-07: setup E37224 passes Root's IRoot base to E39E8C; E3AA34 calls getShape.
    /* 0x018 */ const chm::IRoot* _18;
    /* 0x020 */ xlink::ChemicalEventState* _20;
    /* 0x028 */ world::ChemicalMgr* _28;
    /* 0x030 */ u32 _30;  // flags (bit 9 set by ChemicalWeaponRoot::m44)
    /* 0x034 */ u8 _34;
    /* 0x035 */ u8 _35 = 10;
    /* 0x036 */ u8 _36 = 0;
    // E3BE78 counts consecutive stationary frames here, saturating at 255.
    /* 0x037 */ u8 _37 = 0;
    /* 0x038 */ u8 _38 = 0;
    /* 0x039 */ u8 _39[0x3c - 0x39];
    /* 0x03c */ u32 _3c;  // flags (RootAi::setChemicalFlags3cMaybe)
    /* 0x040 */ Chemical mChemical;
    /* 0x278 */ sead::Buffer<BodyEntry> _278;
    /* 0x288 */ u32 _288;
    /* 0x28c */ f32 _28c;
    /* 0x290 */ f32 _290;
    /* 0x294 */ f32 _294;
    /* 0x298 */ sead::Vector3f _298;
    /* 0x2a4 */ sead::Vector3f _2a4;
    /* 0x2b0 */ sead::Vector3f _2b0;
    /* 0x2bc */ s32 _2bc;
    /* 0x2c0 */ u32 _2c0;
    // E3B3F4 builds the twenty chemical-event eligibility flags here.
    /* 0x2c4 */ sead::BitFlag32 _2c4;
    /* 0x2c8 */ u8 _2c8[0x2d4 - 0x2c8];
    // E3DB6C starts this at 120.0f; E3C34C decrements it by one.
    /* 0x2d4 */ f32 _2d4;
};
KSYS_CHECK_SIZE_NX150(Unk_71024e6428, 0x2d8);
static_assert(offsetof(Unk_71024e6428, mPlacementXLink) == 0x10);

// Name from the CSV (ActorChemicals::*). Actor::mChemical (+0x6a8). ctor 0x7100e36ebc, vtable
// 0x71024e63f0 (getNodeClassType, D1 0x7100e36f0c, D0 0x7100e37168).
// Holds two arrays of 0x2d8-byte elements (ctor 0x7100e399c0) whose second base (+0x40) is a
// Chemical; the first _58 entries live in _60, the following _80 entries in _78.
// TODO: incomplete.
class ActorChemicals : public sead::hostio::Node {
public:
    ActorChemicals();
    virtual ~ActorChemicals();
    bool sub_7100E37010(bool force);
    void sub_7100E3762C(Unk_71024dd490* holder);
    void init1(phys::InstanceSet* instance, const chm::Root* root, Actor* actor, sead::Heap* heap);
    // Full E3742C initializes the supplied root/body with a heap and ChemicalMgr owner.
    // World record 10C8748 and ChemicalMgr::init_ establish the independent owner input.
    void sub_7100E3742C(chm::IRoot* root, phys::RigidBody* body, world::ChemicalMgr* mgr,
                       sead::Heap* heap);
    // 0x7100e37990: allocates `count` elements into _70 (under mCS) and resets _80.
    void sub_7100E37990(s32 count, sead::Heap* heap);
    // 0x7100e37eb0: binds ActorX6A0's state to each chemical element.
    void init2(Unk_7101265a6c* state);

    // 0x7100e39458: checks the current chemical elements (declaration only).
    bool sub_7100E39458();
    // 0x7100e392fc: false when at least one active chemical element reports a state (the LOD debug
    // helpers call it to decide whether the actor's chemical effects are running).
    bool x_0();

    Chemical* getStuff(int idx);
    // 0x7100e3718c (lane1 s22, placeholder name): the element itself (not its Chemical), ~25 callers.
    Unk_71024e6428* sub_7100E3718C(int idx);
    // 0x7100e37fa8 (lane4 s47): a second out-of-line copy of sub_7100E3718C (byte-identical; ~15 callers: Arrow AI and
    // others).
    Unk_71024e6428* sub_7100E37FA8(int idx);
    // 0x7100e39614 (lane1 s41, placeholder name): Chemical::sub_7100D91098(on) on every chemical.
    void sub_7100E39614(bool on);
    // Full E38588 stores the value at +68 and propagates it to every active Chemical.
    // GolemRoot 4003E4 and independent E37B10 pass existing u32 chemical state fields.
    void sub_7100E38588(u32 value);
    // 0x7100e37788: same as getStuff (a separate copy in the binary; Actor::sub_71011D8A44).
    Chemical* sub_7100E37788(int idx);
    void sub_7100E37CE4();
    // 0x7100e380fc / 0x7100e3816c (placeholder names; two identical copies): the Chemical of entry `idx` of _70
    // (null when out of range).
    Chemical* sub_7100E380FC(int idx);
    Chemical* sub_7100E3816C(int idx);
    // 0x7100e384c4 (placeholder name): whether `body` is one of the rigid bodies (_278) of element `idx` (no lock).
    bool sub_7100E384C4(const phys::RigidBody* body, int idx);
    // 0x7100e381dc (declared only; placeholder name): looks a Chemical up by name; Actor::sub_71011D8A54.
    Chemical* sub_7100E381DC(const sead::SafeString& name);
    // 0x7100e38c54 (unnamed in the CSV; declaration only; 1.7 KB, lane4 s51 placeholder name): attaches (`true`) / detaches the
    // carrier actor (Unk_7100e4e084::sub_7100E50450 / sub_7100E4E084).
    void sub_7100E38C54(Actor* carrier, bool attach);
    // 0x7100e382c4 (declared only; lane4 s30): the index of the chemical called `name` (-1 if none; the
    // wrapper ActorLinkConstDataAccess::sub_7100D137C0 returns it).
    s32 sub_7100E382C4(const sead::SafeString& name);

    /* 0x08 */ sead::CriticalSection mCS;
    /* 0x48 */ bool _48 = false;
    // E37224 stores Root's IRoot base; E38588 reads rigid attribute 13. Non-owning.
    /* 0x50 */ const chm::IRoot* _50 = nullptr;
    /* 0x58 */ sead::Buffer<Unk_71024e6428> _58;
    /* 0x68 */ u32 _68 = 0;
    /* 0x6c */ u32 _6c = 0;
    /* 0x70 */ sead::Buffer<Unk_71024e6428> _70;  // the first _80 entries are used
    /* 0x80 */ s32 _80 = 0;

private:
    // Inlined into getStuff / sub_7100E37788 (they take mCS twice).
    Unk_71024e6428* getElement_(int idx) {
        mCS.lock();
        if (_58.size() + _80 <= 0) {
            mCS.unlock();
            return nullptr;
        }
        Unk_71024e6428* element;
        if (idx < _58.size())
            element = &_58[idx];
        else
            element = &_70[idx - _58.size()];
        mCS.unlock();
        return element;
    }
};

}  // namespace ksys::act
