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

bool RopeBase::shouldUnload() {
    if (!_95a && !mMapObject)
        return false;
    return shouldUnloadBecauseOfDistance();
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

}  // namespace ksys::act
