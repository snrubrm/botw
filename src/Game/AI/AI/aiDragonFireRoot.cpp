#include "Game/AI/AI/aiDragonFireRoot.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::ai {

DragonFireRoot::DragonFireRoot(const InitArg& arg) : DragonRoot(arg) {}

DragonFireRoot::~DragonFireRoot() = default;

bool DragonFireRoot::init_(sead::Heap* heap) {
    return DragonRoot::init_(heap);
}

void DragonFireRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    DragonRoot::enter_(params);
}

void DragonFireRoot::leave_() {
    DragonRoot::leave_();
}

void DragonFireRoot::loadParams_() {
    DragonRoot::loadParams_();
}

void DragonFireRoot::calc_() {
    DragonRoot::calc_();
    if (isCurrentChild("停止"))
        changeChild("帰還");
    sub_7100367FE4();
}

void DragonFireRoot::m42() {
    DragonRoot::m42();
}

void DragonFireRoot::m44(const sead::Vector3f& pos) {
    ksys::act::InstParamPack pack;
    pack->addPosition(pos);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        "DragonFlameBall", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), nullptr, &pack,
        nullptr, 2);
}

}  // namespace uking::ai
