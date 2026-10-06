#include "Game/AI/Action/actionWolfLinkAmiiboWarp.h"
#include "Game/gameWolfLinkMgr.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

namespace uking::action {

WolfLinkAmiiboWarp::WolfLinkAmiiboWarp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WolfLinkAmiiboWarp::~WolfLinkAmiiboWarp() = default;

bool WolfLinkAmiiboWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: same code; the original computes `&manager->_68` before the spin lock and uses other registers
void WolfLinkAmiiboWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* manager = WolfLinkMgr::instance();
    manager->_54.set(*mTargetPos_d);
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_28._18.mLock);
        _28._18._0 = 3;
    }
    _28.sub_710070DBB0(manager->_68, true);
}

void WolfLinkAmiiboWarp::leave_() {
    ksys::act::ai::Action::leave_();
}

void WolfLinkAmiiboWarp::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void WolfLinkAmiiboWarp::calc_() {
    ksys::act::ai::Action::calc_();
}

bool WolfLinkAmiiboWarp::handleAck_(const ksys::MessageAck* ack) {
    if (ack->getType() == 0x80000a8) {
        setFinished();
        return true;
    }
    return false;
}

}  // namespace uking::action
