#include "KingSystem/Physics/Constraint/physConstraint.h"
#include <prim/seadScopedLock.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyRequestMgr.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

bool Constraint::sub_7100F6A2E0() const {
    if (mPendingBodies[0])
        return true;
    return mPendingBodies[1] != nullptr;
}

bool Constraint::sub_7100F6ACE8() const {
    return _52 & 1;
}

bool Constraint::sub_7100F6A880() const {
    return _52 & 2;
}

void Constraint::sub_7100F69FF0() {
    auto lock = sead::makeScopedLock(mCS);
    if (_52 & 2) {
        _52 = (_52 & ~3) | 1;
    } else if (!(_52 & 1)) {
        auto lock2 = sead::makeScopedLock(mCS);
        if (_52 == 0)
            System::instance()->getRigidBodyRequestMgr()->pushConstraint(this);
        _52 |= 1;
    }
}

void Constraint::sub_7100F6A074() {
    auto lock = sead::makeScopedLock(mCS);
    if (_52 & 1) {
        _52 = (_52 & ~3) | 2;
    } else if (_50 & 1) {
        auto lock2 = sead::makeScopedLock(mCS);
        if (_52 == 0)
            System::instance()->getRigidBodyRequestMgr()->pushConstraint(this);
        _52 |= 2;
    }
}

void Constraint::sub_7100F6A0FC(f32 a, f32 b) {
    auto lock = sead::makeScopedLock(mCS);
    if (!(_52 & 4)) {
        auto lock2 = sead::makeScopedLock(mCS);
        if (_52 == 0)
            System::instance()->getRigidBodyRequestMgr()->pushConstraint(this);
        _52 |= 4;
    }
    _98 = a;
    _9c = b;
}

void Constraint::sub_7100F6A1D8() {
    auto lock = sead::makeScopedLock(mCS);
    if (_52 & 2)
        sub_7100F6A6F8(true, true);
}

void Constraint::sub_7100F6A21C() {
    sub_7100F6A6F8(true, true);
}

void Constraint::destroy(Constraint* instance) {
    delete instance;
}

// NON_MATCHING: identical instructions, only the shift by 3 (lsl) is scheduled after the &mCurrentBodies add
RigidBody* Constraint::x_0(int idx) const {
    auto* bodies = &mPendingBodies;
    if (!(*bodies)[idx])
        bodies = &mCurrentBodies;
    return (*bodies)[idx];
}

void Constraint::sub_7100F6A69C(BodyIndex idx) {
    auto lock = sead::makeScopedLock(mCS);
    mPendingBodies[idx] = nullptr;
    _52 &= ~8;
}

// inline-only in the original; name is a guess. Sets a body and requests the update (bit 3). The original has
// three copies of it, at 0x7100f6a88c (body index 0), 0x7100f6a92c (index 1) and 0x7100f6a9d4 (index 1, body from
// the StaticCompoundMgr).
inline bool Constraint::setBodyAndRequest_(BodyIndex idx, RigidBody* body) {
    if (_52 & 2)
        return false;
    auto lock = sead::makeScopedLock(mCS);
    mPendingBodies[idx] = body;
    auto lock2 = sead::makeScopedLock(mCS);
    if (_52 == 0)
        System::instance()->getRigidBodyRequestMgr()->pushConstraint(this);
    _52 |= 8;
    return true;
}

bool Constraint::sub_7100F6A88C(RigidBody* body) {
    return setBodyAndRequest_(BodyIndex::_0, body);
}

bool Constraint::sub_7100F6A92C(RigidBody* body) {
    return setBodyAndRequest_(BodyIndex::_1, body);
}

bool Constraint::sub_7100F6A9D4(StaticCompoundRigidBodyGroup* group) {
    if (!group)
        return false;
    auto* mgr = System::instance()->getStaticCompoundMgr();
    if (!mgr)
        return false;
    auto* body = mgr->getRigidBody(group);
    if (!body)
        return false;
    return setBodyAndRequest_(BodyIndex::_1, body);
}

void Constraint::sub_7100F6AC04(bool toi) {
    if (toi != ((_50 >> 4) & 1)) {
        mConstraintInstance->setPriority(toi ? hkpConstraintInstance::PRIORITY_TOI :
                                               hkpConstraintInstance::PRIORITY_PSI);
        if (toi)
            _50 |= 0x10;
        else
            _50 &= ~0x10;
    }
}

bool Constraint::sub_7100F6AC68() const {
    auto* body = x_0(1);
    return !body || body == System::instance()->get190();
}

u64 sub_7100F6AC60(const hkpConstraintInstance* instance) {
    return instance->getUserData();
}

}  // namespace ksys::phys
