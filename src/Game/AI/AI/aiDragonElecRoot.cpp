#include "Game/AI/AI/aiDragonElecRoot.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::ai {

DragonElecRoot::DragonElecRoot(const InitArg& arg) : DragonRoot(arg) {}

DragonElecRoot::~DragonElecRoot() = default;

bool DragonElecRoot::init_(sead::Heap* heap) {
    return DragonRoot::init_(heap);
}

void DragonElecRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    DragonRoot::enter_(params);
}

void DragonElecRoot::calc_() {
    DragonRoot::calc_();
    if (isCurrentChild("停止"))
        changeChild("帰還");
}

void DragonElecRoot::leave_() {
    DragonRoot::leave_();
}

void DragonElecRoot::loadParams_() {
    DragonRoot::loadParams_();
}

void DragonElecRoot::m42() {
    DragonRoot::m42();
}

void DragonElecRoot::m44(const sead::Vector3f& pos) {
    ksys::act::InstParamPack pack;
    pack->addPosition(pos);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        "DragonThunderBall", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), nullptr, &pack,
        nullptr, 2);
}

}  // namespace uking::ai
