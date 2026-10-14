#include "Game/Actor/Action/actionKokkoCreateDrop.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorX6A0.h"
#include "KingSystem/World/worldManager.h"

namespace uking::action {

KokkoCreateDrop::KokkoCreateDrop(const InitArg& arg) : CreateDropBase(arg) {}

KokkoCreateDrop::~KokkoCreateDrop() = default;

bool KokkoCreateDrop::init_(sead::Heap* heap) {
    return CreateDropBase::init_(heap);
}

void KokkoCreateDrop::enter_(ksys::act::ai::InlineParamPack* params) {
    CreateDropBase::enter_(params);
}

void KokkoCreateDrop::leave_() {
    CreateDropBase::leave_();
}

void KokkoCreateDrop::loadParams_() {
    CreateDropBase::loadParams_();
}

void KokkoCreateDrop::calc_() {
    CreateDropBase::calc_();
}

bool KokkoCreateDrop::m32() {
    if (mActor->_6a0->_a.isOn(2 | 4))
        return false;
    return !ksys::world::Manager::instance()->sub_71010F3A94();
}

}  // namespace uking::action
