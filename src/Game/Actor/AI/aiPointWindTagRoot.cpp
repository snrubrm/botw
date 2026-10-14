#include "Game/Actor/AI/aiPointWindTagRoot.h"
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/World/worldManager.h"

namespace uking::ai {

PointWindTagRoot::PointWindTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PointWindTagRoot::~PointWindTagRoot() = default;

bool PointWindTagRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PointWindTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* area = sead::DynamicCast<ksys::act::Area>(mActor))
        area->m107();
}

// NON_MATCHING: the original reads the list head before locking and locks the CollisionInfo mutex inline
// (ours calls CollisionInfoBase::lock()); frame 0x10 larger
// Blows wind in the tag's direction (the opposite one while the basic signal is on) while the player touches
// the area; resets the manual wind otherwise.
void PointWindTagRoot::calc_() {
    auto* area = sead::DynamicCast<ksys::act::AreaActor>(mActor);
    const bool reverse = mActor->checkBasicSig();
    bool blowing = false;
    if (area) {
        ksys::act::acc::AreaActor accessor(area);
        auto* info = accessor.getField848();
        area->m107();
        if (info && info->getCollidingBodies().size() != 0) {
            info->lock();
            for (auto& bodies : info->getCollidingBodies()) {
                auto* body = bodies.bodies[1];
                if (!body)
                    continue;
                auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(body->getUserTag());
                if (!tag)
                    continue;
                ksys::act::ActorLinkConstDataAccess other;
                tag->acquireActor(&other);
                if (!ksys::act::isPlayerProfile(other))
                    continue;
                s32 direction = *mDirection_m;
                if (reverse)
                    direction = direction + 4 > 7 ? direction - 4 : direction + 4;
                ksys::world::Manager::instance()->changeWind(direction, true, *mWindSpeed_m);
                blowing = true;
            }
            info->unlock();
        }
    }
    if (!blowing)
        ksys::world::Manager::instance()->resetManualWind();
}

void PointWindTagRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PointWindTagRoot::loadParams_() {
    getMapUnitParam(&mDirection_m, "Direction");
    getMapUnitParam(&mWindSpeed_m, "WindSpeed");
    getMapUnitParam(&mShape_m, "Shape");
}

}  // namespace uking::ai
