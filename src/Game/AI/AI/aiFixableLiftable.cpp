#include "Game/AI/AI/aiFixableLiftable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

FixableLiftable::FixableLiftable(const InitArg& arg) : SimpleLiftable(arg) {}

FixableLiftable::~FixableLiftable() = default;

bool FixableLiftable::init_(sead::Heap* heap) {
    return SimpleLiftable::init_(heap);
}

void FixableLiftable::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLiftable::enter_(params);
}

void FixableLiftable::leave_() {
    SimpleLiftable::leave_();
}

void FixableLiftable::loadParams_() {
    getStaticParam(&mCancelFixedScale_s, "CancelFixedScale");
    getMapUnitParam(&mIsFixedPlace_m, "IsFixedPlace");
}

void FixableLiftable::m34() {
    SimpleLiftable::m34();
    auto* actor = mActor;
    if (actor->getMapObject() != nullptr) {
        if (auto* body = actor->getMainBody()) {
            if (*mIsFixedPlace_m)
                body->changeMotionType(ksys::phys::MotionType::Fixed);
        }
    }
    m38();
}

void FixableLiftable::m38() {
    _d8 = mActor->getScale().x;
}

}  // namespace uking::ai
