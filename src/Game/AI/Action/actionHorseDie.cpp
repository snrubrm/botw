#include "Game/AI/Action/actionHorseDie.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

HorseDie::HorseDie(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseDie::~HorseDie() = default;

bool HorseDie::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseDie::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseDie::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseDie::loadParams_() {
    getStaticParam(&mDyingFrames_s, "DyingFrames");
    getStaticParam(&mCheckIfStable_s, "CheckIfStable");
    getStaticParam(&mASName_s, "ASName");
}

void HorseDie::calc_() {
    ksys::act::ai::Action::calc_();
}

bool HorseDie::handleMessage_(const ksys::Message& message) {
    if (message.getType() != ksys::MessageType(0x380001c))
        return false;
    auto* info = mActor->m135();
    if (info) {
        if (info->_0)
            mActor->deleteEx(ksys::act::Actor::DeleteType::_4, ksys::act::BaseProc::DeleteReason::_0);
        else
            mActor->deleteAndEmit(0);
    } else {
        mActor->deleteEx(ksys::act::Actor::DeleteType::_4, ksys::act::BaseProc::DeleteReason::_0);
    }
    return true;
}

}  // namespace uking::action
