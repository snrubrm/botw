#include "Game/AI/Action/actionShootingStarBrightTower.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldShootingStarMgr.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

ShootingStarBrightTower::ShootingStarBrightTower(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShootingStarBrightTower::~ShootingStarBrightTower() = default;

bool ShootingStarBrightTower::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShootingStarBrightTower::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    mActor->getXLink()->_cc.reset(0x80000);
    _6c = sead::Matrix34f::ident;
    sead::Vector3f pos = mActor->getMtx().getTranslation();
    if (auto* world = ksys::world::Manager::instance()) {
        if (auto* star = world->getShootingStarMgr())
            star->tryGetStarPosition(&pos);
    }
    const sead::Vector3f& dir = *mHitGroundAngle_d;
    _6c.setTranslation(pos);
    const f32 length = dir.length();
    if (length > 0)
        _9c.setScale(dir, 1.0f / length);
    xlinkSearchAndEmit(mActor, "BrightTower", 2, &_30);
    _30.sub_7101241A44(_6c);
    _60 = pos;
    _a8 = 50.0f;
}

void ShootingStarBrightTower::leave_() {
    _30.fadeXLink();
}

void ShootingStarBrightTower::loadParams_() {
    getStaticParam(&mDisappearDistance_s, "DisappearDistance");
    getDynamicParam(&mHitGroundAngle_d, "HitGroundAngle");
}

void ShootingStarBrightTower::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
