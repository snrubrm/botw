#include "KingSystem/Physics/Constraint/physConstraint.h"
#include <prim/seadScopedLock.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyRequestMgr.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

// NON_MATCHING: the native selects the body-pointer address before loading it; this branches on the pointer.
RigidBody* getPhysicsMemSysField190Or(const Constraint::Param& param) {
    return param.body_a ? param.body_a : System::instance()->get190();
}

RigidBody* sub_7100F69FAC(const Constraint::Param& param) {
    if (param.mBodyGroup) {
        auto* mgr = System::instance()->getStaticCompoundMgr();
        if (mgr)
            return mgr->getRigidBody(param.mBodyGroup);
        return nullptr;
    }
    return param.body_b;
}

ConstraintUnk18* sub_7100F6ACA8(hkpConstraintData* data, const Constraint::Param& param,
                              sead::Heap* heap) {
    if (!param._19)
        return nullptr;
    ConstraintUnk18::Param breakable_param;
    breakable_param._0 = true;
    breakable_param.mSolverResultLimit = param._1c;
    return ConstraintUnk18::sub_7100F6C5B4(data, breakable_param, heap);
}

Constraint::Constraint(hkpConstraintInstance* instance, RigidBody* body_a, RigidBody* body_b,
                       const u32& value, ConstraintUnk18* breakable)
    : mConstraintInstance(instance), _10(value), _18(breakable), _20(nullptr), _28(nullptr),
      _50(0), _52(0), _98(1.0f), _9c(1.0f), _a0(nullptr) {
    mCurrentBodies[0] = System::instance()->get190();
    mCurrentBodies[1] = nullptr;
    mPendingBodies[0] = body_a;
    mPendingBodies[1] = body_b;
    mConstraintInstance->setUserData(reinterpret_cast<hkUlong>(this));
    if (mConstraintInstance->getPriority() == hkpConstraintInstance::PRIORITY_TOI)
        _50 |= 0x10;
    if (_18)
        _18->_10 = mConstraintInstance;
}

// NON_MATCHING: regalloc (this and &mCS swap x19 / x20); same with a ScopedLock
void Constraint::sub_7100F6A228() {
    mCS.lock();
    if ((_50 & 1) && sub_7100F6A2E0()) {
        if (mPendingBodies[0]) {
            sub_7100F6A300(mCurrentBodies[0], mPendingBodies[0]);
            mPendingBodies[0] = nullptr;
        }
        if (mPendingBodies[1]) {
            sub_7100F6A300(mCurrentBodies[1], mPendingBodies[1]);
            mPendingBodies[1] = nullptr;
        }
    }
    if (_52 & 1)
        sub_7100F6A474(sub_7100F6A2E0());
    if (_52 & 4)
        sub_7100F6A5C8();
    _52 = 0;
    mCS.unlock();
}

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

// NON_MATCHING: request-manager argument loads and the shared return block are reordered.
void Constraint::sub_7100F6A6F8(bool activate, bool replace_body) {
    _52 &= ~8;
    mPendingBodies[1] = nullptr;
    if ((_50 & 1) && mConstraintInstance->getOwner()) {
        System::instance()->lockWorld(ContactLayerType::Entity);
        _a8.lock();
        if (activate) {
            if (mCurrentBodies[0])
                mCurrentBodies[0]->getHkBody()->activate();
            if (mCurrentBodies[1])
                mCurrentBodies[1]->getHkBody()->activate();
        }
        System::instance()->getRigidBodyRequestMgr()->removeConstraintFromWorld(mConstraintInstance);
        if (_20)
            System::instance()->sub_7101216AB0(_20);
        _50 = (_50 & ~9) | 8;
        _a8.unlock();
        System::instance()->unlockWorld(ContactLayerType::Entity);
    } else if (replace_body && mCurrentBodies[1] != System::instance()->get190()) {
        const bool added = _50 & 1;
        if (added)
            System::instance()->lockWorld(ContactLayerType::Entity);
        _a8.lock();
        if (mCurrentBodies[1])
            sub_7100F6A300(mCurrentBodies[1], System::instance()->get190());
        _a8.unlock();
        if (added)
            System::instance()->unlockWorld(ContactLayerType::Entity);
    }
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

// NON_MATCHING: the original loads mConstraintInstance before the RigidBodyRequestMgr for both calls
bool Constraint::sub_7100F6A300(RigidBody* old_body, RigidBody* body) {
    bool result = false;
    if (old_body != body && body) {
        if (System::instance()->get190() || body->isAddedToWorld()) {
            _50 |= 0x20;
            const bool added = _50 & 1;
            hkpEntity* old_entity = old_body ? old_body->getHkBody() : nullptr;
            hkpEntity* entity = body->getHkBody();
            if (added) {
                System::instance()->getRigidBodyRequestMgr()->removeConstraintFromWorld(mConstraintInstance);
                if (_20)
                    System::instance()->sub_7101216AB0(_20);
                _50 = (_50 & ~9) | 8;
            }
            if (mCurrentBodies[0] == old_body)
                mCurrentBodies[0] = body;
            else if (mCurrentBodies[1] == old_body)
                mCurrentBodies[1] = body;
            mConstraintInstance->replaceEntity(old_entity, entity);
            if (added) {
                System::instance()->getRigidBodyRequestMgr()->addConstraintToWorld(mConstraintInstance);
                if (_20)
                    System::instance()->sub_7101216AA8(_20);
                _50 = (_50 & ~9) | 1;
            }
            body->setFlag800000();
            result = true;
        }
    }
    _50 &= ~0x20;
    return result;
}

// NON_MATCHING: the original loads mCurrentBodies[1] separately on each branch; same request-mgr load order
// as sub_7100F6A300
bool Constraint::sub_7100F6A474(bool apply_pending) {
    RigidBody* body_a = mCurrentBodies[0];
    RigidBody* body_b = mCurrentBodies[1];
    if (apply_pending) {
        if (mPendingBodies[0])
            body_a = mPendingBodies[0];
        if (mPendingBodies[1])
            body_b = mPendingBodies[1];
    }

    if (body_b == System::instance()->get190())
        return false;
    if (body_a->isSensor())
        return false;
    if (body_b && body_b->isSensor())
        return false;
    if (!body_a->isAddedToWorld())
        return false;
    if (body_b && !body_b->isAddedToWorld())
        return false;
    if (_50 & 1)
        return false;

    auto lock = sead::makeScopedLock(_a8);
    if (apply_pending) {
        if (mPendingBodies[0]) {
            sub_7100F6A300(mCurrentBodies[0], body_a);
            mPendingBodies[0] = nullptr;
        }
        if (mPendingBodies[1]) {
            sub_7100F6A300(mCurrentBodies[1], body_b);
            mPendingBodies[1] = nullptr;
        }
    }
    if (_a0)
        _a0->m0(this, false);
    System::instance()->getRigidBodyRequestMgr()->addConstraintToWorld(mConstraintInstance);
    if (_20)
        System::instance()->sub_7101216AA8(_20);
    _50 = (_50 & ~9) | 1;
    return true;
}

void Constraint::sub_7100F6A5C8() {
    if (!mConstraintInstance->getOwner())
        return;
    RigidBody* body_a = mCurrentBodies[0];
    if (!body_a)
        return;
    RigidBody* body_b = mCurrentBodies[1];
    if (!body_b)
        return;

    hkpRigidBody* hk_body_a = body_a->getHkBody();
    hkpRigidBody* hk_body_b = body_b->getHkBody();
    const f32 mass_a = hk_body_a->getMotion()->getMass();
    const f32 mass_b = hk_body_b->getMotion()->getMass();
    f32 inv_a = 1.0f;
    f32 inv_b = 1.0f;
    if (hk_body_a->getMotion()->getMass() >= hk_body_b->getMotion()->getMass())
        inv_b = (mass_b * _98) / (mass_a * _9c);
    else
        inv_a = (mass_a * _9c) / (mass_b * _98);
    hkVector4 inv_mass_a;
    hkVector4 inv_mass_b;
    inv_mass_a.setAll(inv_a);
    inv_mass_b.setAll(inv_b);
    mConstraintInstance->setVirtualMassInverse(inv_mass_a, inv_mass_b);
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

bool Constraint::sub_7100F6AAA4(RigidBody* a, RigidBody* b) {
    const bool success_a = setBodyAndRequest_(BodyIndex::_0, a);
    const bool success_b = setBodyAndRequest_(BodyIndex::_1, b);
    return success_a && success_b;
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

u32 sub_7100F6ACF4(bool breakable) {
    if (breakable)
        return sub_7100F6C5AC() + 0x98;
    return 0x98;
}

}  // namespace ksys::phys
