#include "Game/AI/Action/actionBombExplode.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BombExplode::BombExplode(const InitArg& arg) : ActionEx(arg) {}

BombExplode::~BombExplode() = default;

void BombExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void BombExplode::leave_() {
    mActor->setFlag(ksys::act::Actor::ActorFlag::_20, false);
    if (_48) {
        sub_71007A2D34(_48);
        _48 = nullptr;
    }
}

void BombExplode::loadParams_() {}

void BombExplode::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
