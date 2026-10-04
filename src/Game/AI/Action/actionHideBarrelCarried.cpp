#include "Game/AI/Action/actionHideBarrelCarried.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/Shape/Cylinder/physCylinderRigidBody.h"

namespace uking::action {

HideBarrelCarried::HideBarrelCarried(const InitArg& arg) : Carried(arg) {}

HideBarrelCarried::~HideBarrelCarried() = default;

bool HideBarrelCarried::init_(sead::Heap* heap) {
    return Carried::init_(heap);
}

// NON_MATCHING: the original selects a pointer to the lower vertex's y component (csel of &a.y / &b.y); clang
// selects the vertex and offsets by 4 afterwards
void HideBarrelCarried::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = sead::DynamicCast<ksys::phys::CylinderRigidBody>(mActor->getMainBody())) {
        body->getVertices(&_170, &_17c);
        sead::Vector3f a = _170;
        sead::Vector3f b = _17c;
        f32& y = a.y < b.y ? a.y : b.y;
        y = *mCutLength_s + y;
        body->setVertices(a, b);
    }
    Carried::enter_(params);
}

void HideBarrelCarried::leave_() {
    if (auto* body = sead::DynamicCast<ksys::phys::CylinderRigidBody>(mActor->getMainBody()))
        body->setVertices(_170, _17c);
    Carried::leave_();
}

void HideBarrelCarried::loadParams_() {
    Carried::loadParams_();
    getStaticParam(&mCutLength_s, "CutLength");
}

void HideBarrelCarried::calc_() {
    Carried::calc_();
}

}  // namespace uking::action
