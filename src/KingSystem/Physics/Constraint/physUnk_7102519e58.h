#pragma once

#include <container/seadTList.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class Constraint;
class RigidBody;
}

// Placeholder name: constraint owner, vtable 0x7102519e58 (seven slots).
// Native registration converts this to its TListNode base at +8.
class Unk_7102519e58 : public sead::TListNode<Unk_7102519e58*> {
    SEAD_RTTI_BASE(Unk_7102519e58)
public:
    Unk_7102519e58();
    virtual ~Unk_7102519e58();
    virtual void m4(const sead::Matrix34f& matrix) = 0;
    virtual void m5() {}
    virtual bool m6() = 0;
    void sub_71012AD478(const sead::Matrix34f& matrix);

    ksys::phys::Constraint* mConstraint = nullptr;
    ksys::phys::RigidBody* mBodyA = nullptr;
    ksys::phys::RigidBody* mBodyB = nullptr;
    s32 mLinkIndex = -1;
    bool _44 = true;
};
KSYS_CHECK_SIZE_NX150(Unk_7102519e58, 0x48);

// Placeholder name: constraint transform owner, vtable 0x71024f7180.
class Unk_71024f7180 : public Unk_7102519e58 {
    SEAD_RTTI_OVERRIDE(Unk_71024f7180, Unk_7102519e58)
public:
    Unk_71024f7180();
    ~Unk_71024f7180() override;
    void m4(const sead::Matrix34f& matrix) override;
    void m5() override;
    bool m6() override;

    sead::Vector3f _48 = sead::Vector3f::ez;
    sead::Vector3f _54 = sead::Vector3f::ey;
    sead::Vector3f _60 = sead::Vector3f::ey;
    sead::Matrix34f mTransform = sead::Matrix34f::ident;
    bool _9c = true;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f7180, 0xa0);
