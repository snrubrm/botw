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
