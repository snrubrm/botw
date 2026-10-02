#include "KingSystem/ActorSystem/Awareness/actAITerror.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereShape.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace ksys::act {

// The AITerror methods form their own TU (0x7100d78564-0x7100d789e4): the Unk_71024dca28
// functions in the awareness entry TU call sub_7100D78970 / sub_7100D78814 without inlining them,
// and sub_7100D786EC calls Unk_71024dca28::sub_7100D78444 (32 bytes) out of line.

bool AITerror::sub_7100D78564(sead::Heap* heap) {
    phys::SphereParam param;
    param.name = "ExtendEmitterSensor";
    param.motion_type = phys::MotionType::Keyframed;
    param.contact_layer = phys::ContactLayer::SensorTerror;
    param.radius = 1.0f;
    if (auto* actor = _10._8) {
        if (auto* physics = actor->getPhysics())
            _8 = physics->sub_7100FC0300(&param, heap);
    }
    if (!_8)
        return false;
    _8->setUserTag(&_10);
    return true;
}

bool AITerror::sub_7100D786D8() {
    if (!_8)
        return true;
    return _8->removeFromWorldAndResetLinks();
}

void AITerror::sub_7100D786EC() {
    if (_80)
        _80->sub_7100D78444(this);
    if (_8) {
        _8->x_10();
        if (auto* actor = _10._8) {
            if (auto* physics = actor->getPhysics()) {
                physics->sub_7100FC0600(_8);
                _8 = nullptr;
            }
        }
    }
}

void AITerror::x(const int& idx, u32 flags, f32 value) {
    _10._10.setBit(idx);
    if (idx == 2) {
        _10._18.sub_7100D77518(2, value);
        _10._18._3c |= flags;
    } else {
        _10._18.sub_7100D77518(idx, value);
        _10._18._38.set(u8(flags));
    }
    _10._18._40 = -1;
}

void AITerror::setRadius(f32 radius) {
    if (radius > 0 && _8) {
        _8->setRadius(radius);
        _10._18._4c = radius;
    }
}

f32 AITerror::sub_7100D78800() const {
    if (!_8)
        return -1.0f;
    return _8->getRadius();
}

bool AITerror::sub_7100D78814(Unk_71024dca28* owner, AITerror* prev) {
    if (!_8)
        return false;
    if (_80)
        return false;

    if (!_8->isAddedToWorld()) {
        auto* actor = _10._8;
        sead::Matrix34f mtx = actor->getMtx();
        sead::Vector3f pos;
        if (_b0.isOnBit(0) && actor->x_18(&pos)) {
            sead::Vector3f offset;
            offset.setRotated(mtx, _88);
            pos += offset;
            pos += _94;
            mtx.setTranslation(pos);
        }
        _8->setTransform(mtx, phys::PropagateToLinkedMotions{true});
        _8->addToWorld();
    }

    if (prev) {
        prev->_a8 = this;
        _a0 = prev;
    }
    _80 = owner;
    return true;
}

bool AITerror::sub_7100D78960() const {
    return _80 != nullptr;
}

// NON_MATCHING: addressing (the original keeps the address of _a0 in a register for the prev
// accesses and the final clear)
void AITerror::sub_7100D78970() {
    if (!_8)
        return;
    if (_80) {
        if (_a0)
            _a0->_a8 = _a8;
        if (_a8)
            _a8->_a0 = _a0;
        _80 = nullptr;
        _a0 = nullptr;
        _a8 = nullptr;
    }
    if (_8->isAddedToWorld())
        _8->removeFromWorld();
}

}  // namespace ksys::act
