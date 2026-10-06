#include "Game/AI/Action/actionPuddle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldWeatherMgr.h"

namespace uking::action {

Puddle::Puddle(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Puddle::~Puddle() = default;

bool Puddle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Puddle::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    const f32 depth = 1.0f - ksys::world::Manager::instance()->getWeatherMgrUnchecked()->_2d0;
    sead::Matrix34f mtx;
    actor->getHomeMtx(&mtx);
    mtx.m[1][3] -= depth;
    actor->setMtx(mtx, false, true);
}

void Puddle::leave_() {
    ksys::act::ai::Action::leave_();
}

void Puddle::loadParams_() {}

void Puddle::calc_() {
    if (auto* body = mActor->getMainBody()) {
        const f32 depth = 1.0f - ksys::world::Manager::instance()->getWeatherMgrUnchecked()->_2d8;
        sead::Matrix34f mtx;
        mActor->getHomeMtx(&mtx);
        mtx.m[1][3] -= depth;
        body->changePositionAndRotation(mtx);
    }
}

}  // namespace uking::action
