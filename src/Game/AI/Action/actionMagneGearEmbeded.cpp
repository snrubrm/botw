#include "Game/AI/Action/actionMagneGearEmbeded.h"
#include "Game/AI/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

MagneGearEmbeded::MagneGearEmbeded(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MagneGearEmbeded::~MagneGearEmbeded() {
    if (_20) {
        ksys::phys::Constraint::destroy(_20);
        _20 = nullptr;
    }
    if (_28) {
        ksys::phys::Constraint::destroy(_28);
        _28 = nullptr;
    }
    if (_30) {
        ksys::phys::Constraint::destroy(_30);
        _30 = nullptr;
    }
    if (_38) {
        ksys::phys::Constraint::destroy(_38);
        _38 = nullptr;
    }
    if (_40) {
        ksys::phys::Constraint::destroy(_40);
        _40 = nullptr;
    }
    if (_48) {
        operator delete(_48);
        _48 = nullptr;
    }
}

bool MagneGearEmbeded::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MagneGearEmbeded::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MagneGearEmbeded::leave_() {
    mActor->emitBasicSigOff();
    if (_20)
        _20->sub_7100F6A074();
    if (_28)
        _28->sub_7100F6A074();
    if (_30)
        _30->sub_7100F6A074();
    if (_38)
        _38->sub_7100F6A074();
    if (_40)
        _40->sub_7100F6A074();
    if (_48)
        xlink::fade(*_48, -1);
}

void MagneGearEmbeded::loadParams_() {}

void MagneGearEmbeded::calc_() {
    mFlags.set(Flag::Changeable);
    if (auto* body = mActor->getMainBody()) {
        sead::Vector3f angular_velocity;
        body->getAngularVelocity(&angular_velocity);
        const f32 speed = angular_velocity.length();
        if (_48) {
            if (speed > 0.0f) {
                if (!_48->isActive())
                    ksys::eft::sub_710105DDB8(mActor, "Roll", _48);
            } else {
                xlink::fade(*_48, -1);
            }
        }
    }
}

}  // namespace uking::action
