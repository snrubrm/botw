#include "Game/AI/Action/actionKokkoCreateDrop.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorX6A0.h"
#include "KingSystem/World/worldManager.h"

namespace uking::action {

KokkoCreateDrop::KokkoCreateDrop(const InitArg& arg) : KokkoCreateDropBase(arg) {}

KokkoCreateDrop::~KokkoCreateDrop() = default;

bool KokkoCreateDrop::init_(sead::Heap* heap) {
    return KokkoCreateDropBase::init_(heap);
}

void KokkoCreateDrop::enter_(ksys::act::ai::InlineParamPack* params) {
    KokkoCreateDropBase::enter_(params);
}

void KokkoCreateDrop::leave_() {
    KokkoCreateDropBase::leave_();
}

void KokkoCreateDrop::loadParams_() {
    KokkoCreateDropBase::loadParams_();
}

void KokkoCreateDrop::calc_() {
    KokkoCreateDropBase::calc_();
}

bool KokkoCreateDrop::m32() {
    if (mActor->_6a0->_a.isOn(2 | 4))
        return false;
    return !ksys::world::Manager::instance()->sub_71010F3A94();
}

}  // namespace uking::action
