#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"
#include <gsys/gsysModel.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Map/mapTypes.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/Constraint/physBAndSCs.h"
#include "KingSystem/Physics/Constraint/physBAndSLimitAngYCs.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::act {

RopeBase::~RopeBase() = default;

// NON_MATCHING: translation temporary loads and stores are scheduled differently.
void RopeBase::preDelete2_(const PreDeleteArg& arg) {
    sub_7100ECED04(arg.do_not_destruct_immediately);
}

void RopeBase::m73() {
    sub_7100ED3498();
    sub_7100ED3CEC();
    _9b0 = _930;
    _9b4 = _938;
    _9b8 = _948;
    mModel->updateWorldMatrix();
    if (!_9f0 && _971) {
        if (!_954 || _96c < 3) {
            _95c = _974;
            _954 = true;
            _958 = false;
            _959 = false;
            _96c = 3;
        }
        _971 = false;
        _974 = -1;
    }
    sub_7100ED4A80();
    sub_7100ED4E50();
    sub_7100ED5010();
}

void RopeBase::m74() {
    Actor::m74();
}

void RopeBase::m76(VFR::ScopedDeltaSetter* setter) {
    if (!_988)
        return;
    const f32 length = _944 * _94c;
    _93c = length * 0.5f;
    _938 = length;
    _940 = 1.0f / length;
    for (s32 i = 0; i <= _930; ++i)
        _860[i]->setScale(_94c);
    for (s32 i = 0; i <= _930 + 1; ++i) {
        auto* constraint = _840[i];
        if (!constraint)
            continue;
        if (auto* limited = sead::DynamicCast<phys::BAndSLimitAngYCs>(constraint)) {
            sead::Matrix34f first = _8f0[i].first;
            sead::Matrix34f second = _8f0[i].second;
            first.m[0][3] *= _94c;
            first.m[1][3] *= _94c;
            first.m[2][3] *= _94c;
            if (i != 0 && i != _930 + 1) {
                second.m[0][3] *= _94c;
                second.m[1][3] *= _94c;
                second.m[2][3] *= _94c;
            }
            limited->sub_7100F6BD8C(first, second);
        } else if (auto* ball = sead::DynamicCast<phys::BAndSCs>(_840[i])) {
            const auto& frames = _8f0[i];
            sead::Vector3f first(frames.first.m[0][3], frames.first.m[1][3], frames.first.m[2][3]);
            sead::Vector3f second(frames.second.m[0][3], frames.second.m[1][3], frames.second.m[2][3]);
            first *= _94c;
            if (i != 0 && i != _930 + 1)
                second *= _94c;
            ball->sub_7100F6B144(first, second);
        }
    }
    sub_7100ECDAB8();
}

void RopeBase::m43(bool on) {
    for (int i = 0; i < _92c; ++i) {
        if (_860[i])
            _860[i]->setFixedAndPreserveImpulse(phys::Fixed(on), phys::MarkLinearVelAsDirty(false));
    }
    for (int i = 0; i < _92c; ++i) {
        if (_880[i])
            _880[i]->setFixedAndPreserveImpulse(phys::Fixed(on), phys::MarkLinearVelAsDirty(false));
    }
}

bool RopeBase::shouldUnload(s32* a1) {
    if (!_95a && !mMapObject)
        return false;
    return shouldUnloadBecauseOfDistance(a1);
}

void RopeBase::updatePositionMaybe() {
    if (auto* body = _860.front()) {
        mMtx = body->getTransform();
        nullsub_4648();
    }
}

int RopeBase::getExtraHeapSize(const ActorHeapInitArgMaybe& arg) {
    map::SRT srt{sead::Vector3f::ones, sead::Vector3f::zero, sead::Vector3f::zero};
    mMapObjIter.getSRT(&srt);
    return sead::Mathf::ceil(srt.scale.y * 16384.0f);
}

// NON_MATCHING: after the _850 store the original reloads the _840 buffer; ours reuses it.
void RopeBase::sub_7100ECD620(s32 idx) {
    if (!_840[idx] || u32(idx) >= u32(_840.size()))
        return;

    if (idx != 0 && idx != _928 - 1) {
        _840[idx]->sub_7100F6A074();
        _850[idx] = _840[idx];
    } else {
        for (s32 i = 0; i < mConstraints.size(); ++i) {
            if (mConstraints.mConstraints[i] == _840[idx] && (_840[idx]->_50 & 1)) {
                _840[idx]->sub_7100F6A074();
                break;
            }
        }
        auto* constraint = _840[idx];
        if ((_8b0 == constraint && (constraint->_50 & 1)) ||
            (_8b8 == constraint && (constraint->_50 & 1))) {
            constraint->sub_7100F6A074();
        }
    }
    _840[idx] = nullptr;
}

// NON_MATCHING: equivalent initial loop-bound comparisons differ.
void RopeBase::sub_7100ECDE98() {
    for (s32 i = 0; i < _928; ++i) {
        if (_840[i])
            _840[i]->sub_7100F6A074();
    }
    if (_8b0)
        _8b0->sub_7100F6A074();
    if (_8b8)
        _8b8->sub_7100F6A074();
    for (s32 i = 0; i < _92c; ++i) {
        if (_860[i])
            _860[i]->removeFromWorld();
        if (_870[i])
            _870[i]->removeFromWorld();
    }
    for (s32 i = 0; i < _92c; ++i) {
        if (_880[i])
            _880[i]->removeFromWorld();
        if (_890[i])
            _890[i]->removeFromWorld();
    }
}

void RopeBase::onEnterSleep_() {
    Actor::onEnterSleep_();
    if (_928 <= 0)
        return;

    for (s32 i = 0; i < _928; ++i) {
        if (_840[i])
            _840[i]->sub_7100F6A21C();
        if (i == 0 || i == _928 - 1)
            _840[i] = nullptr;
    }
    if (_8b0) {
        _8b0->sub_7100F6A21C();
        phys::Constraint::destroy(_8b0);
        _8b0 = nullptr;
    }
    if (_8b8) {
        _8b8->sub_7100F6A21C();
        phys::Constraint::destroy(_8b8);
        _8b8 = nullptr;
    }
    resetConnectedCalcParent(false);
}

void RopeBase::sub_7100ECDAB8() {
    EndState first;
    EndState last;
    sub_7100ED2C24(_840[0], &first);
    sub_7100ED2C24(_840[_930 + 1], &last);
    sub_7100ED2D4C(&first, &last);
    if (!_95b)
        return;

    for (s32 i = 0; i < _92c; ++i) {
        if (auto* body = _860[i])
            body->setLinearDamping(0.25f);
    }
    for (s32 i = 0; i < _92c; ++i) {
        if (auto* body = _860[i])
            body->setMaxLinearVelocity(15.0f);
    }
    for (s32 i = 0; i < _928; ++i) {
        if (auto* constraint = _840[i])
            constraint->sub_7100F6AC04(false);
    }
}

void RopeBase::sub_7100ECE0CC(phys::ContactLayer layer) {
    for (int i = 0; i < _92c; ++i) {
        if (_860[i])
            _860[i]->enableContactLayer(layer);
    }
}

void RopeBase::sub_7100ECE140() {
    for (int i = 0; i < _92c; ++i) {
        if (_860[i])
            _860[i]->setContactAll();
    }
}

void RopeBase::sub_7100ECE1AC(f32 mass) {
    for (int i = 0; i < _92c; ++i) {
        if (_860[i])
            _860[i]->setMass(mass);
    }
}

void RopeBase::sub_7100ECE228(const sead::Vector3f& inertia) {
    for (int i = 0; i < _92c; ++i) {
        if (_860[i])
            _860[i]->setInertiaLocal(inertia);
    }
}

void RopeBase::sub_7100ECE29C(f32 value) {
    for (int i = 0; i < _92c; ++i) {
        if (_860[i])
            _860[i]->setLinearDamping(value);
    }
}

void RopeBase::sub_7100ECE318(f32 value) {
    for (int i = 0; i < _92c; ++i) {
        if (_860[i])
            _860[i]->setAngularDamping(value);
    }
}

void RopeBase::sub_7100ECE394(f32 value) {
    for (int i = 0; i < _92c; ++i) {
        if (_860[i])
            _860[i]->setGravityFactor(value);
    }
}

// NON_MATCHING: one vector-component negation is scheduled before the final component load.
sead::Vector3f RopeBase::sub_7100ECE61C(f32 length) {
    s32 index = (length - 0.001f) * _940;
    if (index < 0 || index > _930)
        index = length < 0.0f ? 0 : _930;
    const f32 fraction = _940 * (length - index * _938) - 0.5f;
    const sead::Matrix34f mtx = _860[index]->getTransform();
    sead::Vector3f direction(-mtx.m[0][1], -mtx.m[1][1], -mtx.m[2][1]);
    direction.normalize();
    return _860[index]->getPosition() + direction * (fraction * _938);
}

f32 RopeBase::sub_7100ECE76C() const {
    return _938 * (_930 + 1);
}

// NON_MATCHING: the two selects in the search loop are scheduled the other way round (fcsel before csel).
f32 RopeBase::sub_7100ECE410(const sead::Vector3f& pos) const {
    f32 min_dist = 100000.0f;
    s32 min_index = 0;
    for (s32 i = 0; i <= _930; ++i) {
        const f32 dist = (_860[i]->getPosition() - pos).length();
        if (dist < min_dist) {
            min_dist = dist;
            min_index = i;
        }
    }

    sead::Vector3f diff = pos - _860[min_index]->getPosition();
    const sead::Matrix34f mtx = _860[min_index]->getTransform();
    sead::Vector3f axis(mtx.m[0][1], mtx.m[1][1], mtx.m[2][1]);
    diff.normalize();
    axis.normalize();
    return min_index * _938 + _93c * (1.0f - diff.dot(axis));
}

s32 RopeBase::sub_7100ED68B4(const sead::Vector3f& pos) const {
    const f32 value = sub_7100ECE410(pos);
    s32 index = (value - 0.001f) * _940;
    if (index < 0 || index > _930)
        return value < 0.0f ? 0 : _930;
    return index;
}

// NON_MATCHING: our build does not pass `this` to sub_7100ED6910 (which does not use it).
void RopeBase::sub_7100ED2C24(phys::Constraint* constraint, EndState* state) {
    if (!constraint || !state)
        return;

    state->_0 = _950;
    state->_4 = false;
    state->_5 = false;
    if (!(constraint->_50 & 1) && !constraint->sub_7100F6ACE8())
        return;

    auto* body = constraint->x_0(1);
    if (constraint->sub_7100F6AC68()) {
        if (body)
            return;
    } else if (body->getMotionType() == phys::MotionType::Dynamic) {
        state->_0 = body->getMass() * 0.8f;
        state->_5 = true;
        ActorLinkConstDataAccess accessor;
        if (sub_7100ED6910(&accessor, constraint)) {
            if (!_956 && accessor.hasTag(0xff2ecb67)) {
                state->_6 = true;
                if (accessor.sub_7100D10E6C(30))
                    state->_7 = true;
            }
            if (accessor.sub_7100D13BB8())
                state->_8 = true;
        }
    }
    state->_4 = true;
}

bool RopeBase::sub_7100ED6910(ActorLinkConstDataAccess* accessor,
                              const phys::Constraint* constraint) const {
    if (constraint && !constraint->sub_7100F6AC68()) {
        if (auto* body = constraint->x_0(1)) {
            if (auto* tag = sead::DynamicCast<PhysicsUserTag>(body->getUserTag())) {
                tag->acquireActor(accessor);
                return accessor->hasProc();
            }
        }
    }
    accessor->acquire(nullptr);
    return false;
}

phys::RigidBody* RopeBase::sub_7100ED6878(s32 index) const {
    if (index < 0 || _930 < index)
        return nullptr;
    return _860[index];
}

}  // namespace ksys::act

namespace ksys::act::acc {

// inline-only in the original; name is a guess (same helper as in acc::Weapon / acc::Armor).
static BaseProc* getProcIfActor(BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        return proc;
    return nullptr;
}

inline ksys::act::RopeBase* RopeBase::getRopeBase() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    return sead::DynamicCast<ksys::act::RopeBase>(actor);
}

bool RopeBase::sub_7100ED8344() const {
    auto* rope = getRopeBase();
    return rope ? rope->_956 != 0 : false;
}

// NON_MATCHING: register allocation only (the original keeps the product in s3)
sead::Vector3f RopeBase::sub_7100ED8440(f32 ratio) const {
    if (auto* rope = getRopeBase()) {
        const f32 length = rope->_938 * f32(rope->_930 + 1);
        return rope->sub_7100ECE61C(length * sead::Mathf::clamp(ratio, 0.0f, 1.0f));
    }
    return sead::Vector3f::zero;
}

void RopeBase::requestCutOffHungPoint(int on) const {
    debugLog(1, "requestCutOff(HungPoint)");
    debugLog(2, "requestCutOff(HungPoint)");
    if (auto* rope = getRopeBase()) {
        rope->_971 = true;
        rope->_974 = on ? rope->_930 + 1 : 0;
    }
}

}  // namespace ksys::act::acc
