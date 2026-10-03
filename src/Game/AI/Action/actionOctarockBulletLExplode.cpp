#include "Game/AI/Action/actionOctarockBulletLExplode.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>

namespace uking::action {

OctarockBulletLExplode::OctarockBulletLExplode(const InitArg& arg) : Explode(arg) {}

OctarockBulletLExplode::~OctarockBulletLExplode() = default;

bool OctarockBulletLExplode::init_(sead::Heap* heap) {
    return Explode::init_(heap);
}

void OctarockBulletLExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    Explode::enter_(params);
}

void OctarockBulletLExplode::leave_() {
    Explode::leave_();
    if (auto* model = mActor->getModel())
        model->getUnits().unsafeAt(0)->_1e |= 0x20;
}

void OctarockBulletLExplode::loadParams_() {
    Explode::loadParams_();
}

void OctarockBulletLExplode::calc_() {
    Explode::calc_();
}

}  // namespace uking::action
