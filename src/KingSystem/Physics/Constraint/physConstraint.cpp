#include "KingSystem/Physics/Constraint/physConstraint.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyRequestMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

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

}  // namespace ksys::phys
