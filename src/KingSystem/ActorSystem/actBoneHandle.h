#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace gsys {
class Model;
}

namespace ksys::act {

// Name from the CSV (BoneHandleBase::ctor 0x7100d3ba50). vtable 0x71023571d8 (inline virtuals; the
// D1 copy 0x7100012274 sits in the Enemy TU). A node of the list of bone handles an actor applies
// to its model every frame (Actor::_4d8; Actor::boneHandleStuff adds a handle,
// Actor::sub_71011DA868 removes it, Actor::job_common_calcAI_andMore calls sub_7100D3BA6C).
class BoneHandleBase {
public:
    BoneHandleBase();
    // NON_MATCHING (D2 0x7100012274): the original keeps the vtable store of this empty dtor.
    virtual ~BoneHandleBase() {}

    // Called every frame with the actor's model.
    virtual void m2(gsys::Model* model) = 0;
    // Called when the handle is added to a list (`sorted` = the attach argument).
    virtual bool m3(gsys::Model* model, bool sorted) { return true; }
    // The bone the handle applies to (sorted lists are ordered by it).
    virtual const gsys::BoneAccessKey* m4() { return nullptr; }

    // 0x7100d3baac: adds this handle to the list `head` (if not added yet and m3 succeeds).
    bool sub_7100D3BAAC(BoneHandleBase** head, gsys::Model* model, bool sorted);
    // 0x7100d3bbd4: removes this handle from the list `head`.
    bool sub_7100D3BBD4(BoneHandleBase** head);
    // 0x7100d3ba6c: calls m2(model) on every handle of the list starting at `head`.
    static void sub_7100D3BA6C(BoneHandleBase* head, gsys::Model* model);

    /* 0x08 */ bool _8;  // in a list
    /* 0x09 */ bool _9;  // `sorted` attach argument
    /* 0x10 */ BoneHandleBase* _10;  // previous
    /* 0x18 */ BoneHandleBase* _18;  // next
};
KSYS_CHECK_SIZE_NX150(BoneHandleBase, 0x20);

// Name from the CSV (BoneHandle::ctor 0x7100d3b3f0, BoneHandle::setName). vtable 0x71024dadc0.
// Applies a transform (_68, scale _98) to one bone (_20 / _30) of the actor's model. Embedded in
// Enemy (+0xf68, +0x1010), GelEnemy and ~30 AI/action classes.
// TODO: incomplete.
class BoneHandle : public BoneHandleBase {
public:
    BoneHandle();
    ~BoneHandle() override;

    void m2(gsys::Model* model) override;
    bool m3(gsys::Model* model, bool sorted) override;
    const gsys::BoneAccessKey* m4() override { return &_30.getKey(); }

    void setName(const sead::SafeString& name);

    /* 0x20 */ sead::SafeString _20 = sead::SafeString::cEmptyString;  // bone name
    /* 0x30 */ gsys::BoneAccessKeyEx _30;
    /* 0x68 */ sead::Matrix34f _68 = sead::Matrix34f::ident;
    /* 0x98 */ sead::Vector3f _98 = sead::Vector3f::ones;
};
KSYS_CHECK_SIZE_NX150(BoneHandle, 0xa8);

}  // namespace ksys::act
