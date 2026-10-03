#include "Game/AI/AI/aiFixableLiftable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace uking::ai {

FixableLiftable::FixableLiftable(const InitArg& arg) : SimpleLiftable(arg) {}

FixableLiftable::~FixableLiftable() = default;

bool FixableLiftable::init_(sead::Heap* heap) {
    return SimpleLiftable::init_(heap);
}

void FixableLiftable::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLiftable::enter_(params);
}

// NON_MATCHING: the original loads the main body twice (once into the saved register, once for the
// null test whose register is reused as the getMotionType argument); the iterator part matches
void FixableLiftable::calc_() {
    SimpleLiftable::calc_();
    auto* actor = mActor;
    auto* body = actor->getMainBody();
    if (!body || !actor->getMapObject())
        return;
    if (!*mIsFixedPlace_m)
        return;
    if (body->getMotionType() == ksys::phys::MotionType::Dynamic)
        return;

    bool touching_dynamic = false;
    if (auto* info = body->getContactPointInfo()) {
        if (info->getNumContactPoints() != 0 && !info->begin().isEnd()) {
            for (auto it = info->begin(), end = info->end(); it != end; ++it) {
                auto* other = (*it)->body_b;
                if (other && other->getMotionType() == ksys::phys::MotionType::Dynamic)
                    touching_dynamic = true;
            }
        }
    }

    const f32 scale = actor->getScale().x;
    if (sub_71007A2604(actor) || (touching_dynamic | (_d8 - scale >= *mCancelFixedScale_s)))
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
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
