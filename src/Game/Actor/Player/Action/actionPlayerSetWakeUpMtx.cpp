#include "Game/Actor/Player/Action/actionPlayerSetWakeUpMtx.h"
#include <math/seadMathNumbers.h>
#include <math/seadQuat.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::action {

PlayerSetWakeUpMtx::PlayerSetWakeUpMtx(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PlayerSetWakeUpMtx::~PlayerSetWakeUpMtx() = default;

bool PlayerSetWakeUpMtx::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: scheduling of the matrix math and of the ray cast start / end copies.
bool PlayerSetWakeUpMtx::oneShot_() {
    auto* evt = ksys::evt::Manager::instance();
    if (!evt)
        return true;
    auto* link = evt->getBaseProcLinkForActorOrActiveLink(nullptr);
    if (!link)
        return true;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    if (!accessor.hasProc())
        return true;

    sead::Matrix34f mtx = accessor.getActorMtx();
    sead::Vector3f pos = mtx * sead::Vector3f(-1.45f, 0.0f, 0.0f);
    mtx.setTranslation(pos);
    sead::Quatf rotation;
    rotation.setAxisRadian(sead::Vector3f::ey, -sead::numbers::pi / 2);
    sead::Matrix34f rotation_mtx;
    rotation_mtx.fromQuat(rotation);
    mtx = mtx * rotation_mtx;

    sead::Vector3f ground = pos;
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    const sead::Vector3f start{pos.x, pos.y + 0.2f, pos.z};
    const sead::Vector3f end = ground;
    query.setStartAndEnd(start, end);
    ksys::act::sub_7100EEACE8(&query);
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        query.getHitPosition(&ground);
    mtx.setTranslation(ground);
    mActor->setMtx(mtx, false, true);
    return true;
}

void PlayerSetWakeUpMtx::loadParams_() {}

}  // namespace uking::action
