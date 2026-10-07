#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include <prim/seadScopedLock.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

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
    virtual bool m15() const { return false; }
    virtual bool m16() const { return false; }
    virtual bool m17() const { return false; }
    virtual bool m18() const { return false; }
    virtual bool m19() const { return false; }
    virtual bool m20() const { return false; }
    virtual bool m21() const { return false; }
    virtual bool m22() const { return true; }
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

// Placeholder name (vtable 0x71024e6428, 37 slots; ctor 0x7100e399c0; size 0x2d8): an element of
// ActorChemicals' arrays and the owner of its Chemical (Chemical::_18).
// TODO: incomplete (virtual functions not declared).
class Unk_71024e6428 : public Unk_71024e6560 {
    SEAD_RTTI_OVERRIDE(Unk_71024e6428, Unk_71024e6560)
public:
    Unk_71024e6428();
    ~Unk_71024e6428() override;

    /* 0x008 */ u8 _8[0x30 - 0x8];
    /* 0x030 */ u32 _30;  // flags (bit 9 set by ChemicalWeaponRoot::m44)
    /* 0x034 */ u8 _34[0x3c - 0x34];
    /* 0x03c */ u32 _3c;  // flags (RootAi::setChemicalFlags3cMaybe)
    /* 0x040 */ Chemical mChemical;
    /* 0x278 */ u8 _278[0x2d8 - 0x278];
};
KSYS_CHECK_SIZE_NX150(Unk_71024e6428, 0x2d8);

// Name from the CSV (ActorChemicals::*). Actor::mChemical (+0x6a8). ctor 0x7100e36ebc, vtable
// 0x71024e63f0 (getNodeClassType, D1 0x7100e36f0c, D0 0x7100e37168).
// Holds two arrays of 0x2d8-byte elements (ctor 0x7100e399c0) whose second base (+0x40) is a
// Chemical; the first _58 entries live in _60, the following _80 entries in _78.
// TODO: incomplete.
class ActorChemicals : public sead::hostio::Node {
public:
    ActorChemicals();
    virtual ~ActorChemicals();

    // 0x7100e39458: checks the current chemical elements (declaration only).
    bool sub_7100E39458();

    Chemical* getStuff(int idx);
    // 0x7100e3718c (lane1 s22, placeholder name): the element itself (not its Chemical), ~25 callers.
    Unk_71024e6428* sub_7100E3718C(int idx);
    // 0x7100e37fa8 (lane4 s47): a second out-of-line copy of sub_7100E3718C (byte-identical; ~15 callers: Arrow AI and
    // others).
    Unk_71024e6428* sub_7100E37FA8(int idx);
    // 0x7100e39614 (lane1 s41, placeholder name): Chemical::sub_7100D91098(on) on every chemical.
    void sub_7100E39614(bool on);
    // 0x7100e37788: same as getStuff (a separate copy in the binary; Actor::sub_71011D8A44).
    Chemical* sub_7100E37788(int idx);
    // 0x7100e381dc (declared only; placeholder name): looks a Chemical up by name; Actor::sub_71011D8A54.
    Chemical* sub_7100E381DC(const sead::SafeString& name);
    // 0x7100e382c4 (declared only; lane4 s30): the index of the chemical called `name` (-1 if none; the
    // wrapper ActorConstDataAccess::sub_7100D137C0 returns it).
    s32 sub_7100E382C4(const sead::SafeString& name);

    /* 0x08 */ sead::CriticalSection mCS;
    /* 0x48 */ bool _48 = false;
    /* 0x50 */ void* _50 = nullptr;
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
