#pragma once

#include <cmath>
#include <heap/seadHeap.h>
#include <math/seadMathCalcCommon.h>
#include <thread/seadThread.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Chemical/chmChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physUserTag.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Chemical;
class Unk_71024dd1c8;
class Unk_71024dd490;
// lane1 s95: 0x7100e40448 (placeholder name, declared only): the centre of a rigid body (sphere / box
// translate, capsule / cylinder midpoint, otherwise the centre of mass).
void sub_7100E40448(sead::Vector3f* out, phys::RigidBody* body);
}  // namespace ksys::act

namespace ksys::phys {
class RigidBody;
}

// vtable 0x71024dd1a8 (ctor 0x7100d8cbb4; CSV name ElementName): the request an element factory fills
// and passes to Element::emitWrap. The holder ctor 0x7100d8cff0 reads the fields.
class ElementName {
public:
    // 0x7100d8cbb4 (next to CameraUtil); its TU also emits the vtable and D1 0x7100d8e244.
    ElementName();
    // 0x7100d8e244 (out of line in CameraUtil.cpp; it keeps the vtable store).
    virtual ~ElementName();

    /* 0x08 */ sead::SafeString mName = "unknown";
    /* 0x18 */ u32 _18 = 0;
    /* 0x20 */ ksys::act::Chemical* _20 = nullptr;
    /* 0x28 */ u64 _28 = 0;
    /* 0x30 */ u64 _30 = 0;
};
KSYS_CHECK_SIZE_NX150(ElementName, 0x38);

// vtable 0x7102517b28 (35 slots; 29 and 33 are pure): base of the world elements (fire, wind, water, ...).
// Functions at 0x7101265698 .. 0x7101265a68 (next to CameraS1). It owns the heap it lives in.
class Element {
    SEAD_RTTI_BASE(Element)
public:
    Element(const ElementName& name, sead::Heap* heap) : mHeap(heap) {}

    virtual void m2() {}
    virtual void m3(f32 delta_frame) {}
    virtual void m4(const sead::Matrix34f& mtx) {}
    virtual void m5(sead::Matrix34f* mtx) const {}
    virtual const sead::Vector3f& m6() const;
    virtual f32 m7() { return 0.0f; }
    virtual void m8() {}
    virtual bool m9() { return false; }
    virtual bool m10() { return true; }
    virtual void m11() {}
    virtual void m12() {}
    virtual f32 m13(f32* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical);
    virtual f32 m14(sead::Vector3f* out, const sead::Vector3f& pos);
    virtual f32 m15(sead::Vector3f* out);
    virtual f32 m16() {
        if (mHolder && mHolder->_80)
            return mHolder->_80->sub_7100D912AC();
        return 1.0f;
    }
    virtual f32 m17(ksys::act::Chemical* chemical);
    virtual bool m18() { return false; }
    virtual f32 m19(ksys::act::Chemical* chemical) { return 1.0f; }
    virtual f32 m20(ksys::act::Chemical* chemical) { return 1.0f; }
    virtual f32 m21(ksys::act::Chemical* chemical) { return 1.0f; }
    virtual f32 m22() { return 1.0f; }
    virtual f32 m23() { return 1.0f; }
    virtual f32 m24() { return 1.0f; }
    virtual s32 m25();
    virtual s32 m26() { return 1; }
    virtual ~Element() { mHeap->destroy(); }
    virtual bool m29(const ElementName& name, sead::Heap* heap) = 0;
    virtual void m30() {}
    virtual bool m31() { return false; }
    virtual void m32() {}
    // lane1 s91: ElementWater and Unk_71025187d0 pass `fixed` to RigidBody::setFixed.
    virtual void m33(bool a, bool fixed) = 0;
    virtual void m34() {}

    // 0x7101265698: creates the chemical holder for `name`, links it to this element and
    // registers it with `holder_mgr`.
    void emitWrap(const ElementName& name, ksys::act::Unk_71024dd490* holder_mgr);

    // inline-only in the original; name is a guess (emitWrap and Unk_71024dd1c8::sub_7100D8CF1C).
    void setHolderMaybe(ksys::act::Unk_71024dd1c8* holder) {
        if (mHolder)
            return;
        mHolder = holder;
        holder->sub_7100D8CF1C(this);
        m34();
    }

    // inline-only in the original; name is a guess (emitWrap and both Unk_7102518688 destructors).
    void unlinkHolderMaybe() {
        if (auto* holder = mHolder) {
            mHolder = nullptr;
            holder->sub_7100D8CF70();
        }
    }

    /* 0x08 */ sead::Heap* mHeap;
    /* 0x10 */ ksys::act::Unk_71024dd1c8* mHolder = nullptr;
    /* 0x18 */ u16 mFlags = 0;
};
KSYS_CHECK_SIZE_NX150(Element, 0x20);

class Unk_7102518688;

// vtable 0x7102518620: the user tag of the element's rigid body.
class Unk_7102518620 : public ksys::phys::UserTag {
    SEAD_RTTI_OVERRIDE(Unk_7102518620, ksys::phys::UserTag)
public:
    ~Unk_7102518620() override = default;

    void onMaxPositionExceeded(ksys::phys::RigidBody* body) override;
    void onBodyShapeChanged(ksys::phys::RigidBody* body) override;

    /* 0x08 */ Unk_7102518688* mElement = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_7102518620, 0x10);

// vtable 0x7102518688 (39 slots): an element with a rigid body (functions 0x710127c378 .. 0x710127d1bc).
class Unk_7102518688 : public Element {
    SEAD_RTTI_OVERRIDE(Unk_7102518688, Element)
public:
    Unk_7102518688(const ElementName& name, sead::Heap* heap, bool flag8);
    ~Unk_7102518688() override;

    // 0x710127d134: updates mPosition to the rigid body centre (zero without a body).
    void m2() override;
    void m3(f32 delta_frame) override;
    void m4(const sead::Matrix34f& mtx) override;
    void m5(sead::Matrix34f* mtx) const override;
    const sead::Vector3f& m6() const override { return mPosition; }
    f32 m7() override;
    void m8() override;
    bool m9() override;
    bool m10() override;
    void m11() override;
    void m12() override;
    // Declared only (lane1 s90): m13 0x710127c7a4, m14 0x710127c920, m15 0x710127cab4, m19 0x710127cda8,
    // m21 0x710127ceb0 (unnamed helpers 0x7100e40814 / e412d0 / e40b7c / e40d94).
    f32 m13(f32* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical) override;
    f32 m14(sead::Vector3f* out, const sead::Vector3f& pos) override;
    f32 m15(sead::Vector3f* out) override;
    f32 m16() override;
    f32 m19(ksys::act::Chemical* chemical) override;
    f32 m21(ksys::act::Chemical* chemical) override;
    f32 m20(ksys::act::Chemical* chemical) override { return 1.0f; }
    f32 m22() override;
    f32 m23() override;
    f32 m24() override { return mRadius; }
    s32 m26() override { return 1; }
    void m30() override;
    bool m31() override;
    void m32() override;
    void m34() override;
    // lane1 s91: ElementSpark::m35 uses the frame delta passed through m3.
    virtual void m35(f32 delta_frame) {}
    virtual void m36() {}
    virtual bool m37() { return true; }
    virtual void m38() {}

    // 0x710127cfcc
    void x();
    // 0x710127c4d0: takes the rigid body, sets its contact layer / info and user tag, and adds it to the world.
    void setRigidBody(ksys::phys::RigidBody* body, bool add_to_world);
    // inline-only in the original; name is a guess (0x710127c318 and setRigidBody repeat it):
    // the radius of a sphere with the rigid body's volume.
    void updateRadius() {
        if (mRigidBody)
            mRadius = std::pow(mRigidBody->getVolume() * 3.0f / (4.0f * sead::Mathf::pi()), 1.0f / 3.0f);
        else
            mRadius = 1.0f;
    }

    // inline-only in the original; name is a guess (m31, m32 and setRigidBody repeat it; the same
    // sequence is act::Chemical::notifyWatch_'s body).
    void notifyChemicalMaybe() {
        if (ksys::chm::Chemical::instance()->_84 & 1) {
            sead::ThreadMgr::instance()->getCurrentThread();
            if (static_cast<const void*>(ksys::chm::Chemical::instance()) != this)
                ksys::chm::Chemical::instance()->_85 = 100;
        }
    }

    /* 0x20 */ ksys::phys::RigidBody* mRigidBody = nullptr;
    /* 0x28 */ Unk_7102518620 mTag;
    /* 0x38 */ sead::Vector3f mPosition = {0, 0, 0};
    /* 0x44 */ f32 mRadius = 1.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_7102518688, 0x48);

namespace ksys::world {
struct Unk_ChemicalMgrM2Arg;
}

// vtable 0x71025187d0: an element with a second rigid body; created by ksys::world::sub_71010CBF7C
// (ChemicalMgr::m2) in a 0x2000-byte "ElementHolder" heap. Functions 0x710127d1d4 .. 0x710127e230.
class Unk_71025187d0 : public Unk_7102518688 {
    SEAD_RTTI_OVERRIDE(Unk_71025187d0, Unk_7102518688)
public:
    // 0x710127d1d4
    Unk_71025187d0(const ksys::world::Unk_ChemicalMgrM2Arg& arg, sead::Heap* heap);
    ~Unk_71025187d0() override;
    bool m29(const ElementName& name, sead::Heap* heap) override;
    void m33(bool a, bool fixed) override;
    void m35(f32 delta_frame) override;
    void m36() override;

    // 0x710127db28 (declared only; 820 bytes).
    void sub_710127DB28();

    /* 0x48 */ ksys::phys::RigidBody* _48 = nullptr;
    /* 0x50 */ ksys::phys::RigidBody* _50 = nullptr;
    /* 0x58 */ void* _58;
    /* 0x60 */ void* _60;
};
KSYS_CHECK_SIZE_NX150(Unk_71025187d0, 0x68);
