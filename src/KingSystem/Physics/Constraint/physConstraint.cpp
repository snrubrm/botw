#include "KingSystem/Physics/Constraint/physConstraint.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyRequestMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

bool Constraint::sub_7100F6ACE8() const {
    return _52 & 1;
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

// NON_MATCHING (m): identical instructions, only the index/base registers are swapped
// (original keeps the index in x9 and the base in x8). Hoisting &_30 into its own local
// reproduces the exact order but that local only steers scheduling (borderline, not applied).
RigidBody* Constraint::x_0(int idx) {
    s64 i = (u32)idx < 2 ? idx : 0;
    RigidBody** bodies = &_40;
    if (bodies[i] == nullptr)
        bodies = &_30;
    return bodies[i];
}

}  // namespace ksys::phys
