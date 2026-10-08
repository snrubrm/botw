#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Map/mapTypes.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::act {

RopeBase::~RopeBase() = default;

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

int RopeBase::getExtraHeapSize() {
    map::SRT srt{sead::Vector3f::ones, sead::Vector3f::zero, sead::Vector3f::zero};
    mMapObjIter.getSRT(&srt);
    return sead::Mathf::ceil(srt.scale.y * 16384.0f);
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
