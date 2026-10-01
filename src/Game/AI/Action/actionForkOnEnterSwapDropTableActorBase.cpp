#include "Game/AI/Action/actionForkOnEnterSwapDropTableActorBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

ForkOnEnterSwapDropTableActorBase::ForkOnEnterSwapDropTableActorBase(const InitArg& arg)
    : Fork(arg) {}

ForkOnEnterSwapDropTableActorBase::~ForkOnEnterSwapDropTableActorBase() {
    if (_38.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_38, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool ForkOnEnterSwapDropTableActorBase::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkOnEnterSwapDropTableActorBase::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkOnEnterSwapDropTableActorBase::leave_() {
    Fork::leave_();
    _38.reset();
}

void ForkOnEnterSwapDropTableActorBase::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mOnGroundPos_s, "OnGroundPos");
}

void ForkOnEnterSwapDropTableActorBase::calc_() {
    Fork::calc_();
}

bool ForkOnEnterSwapDropTableActorBase::m32(sead::BufferedSafeString* name) {
    return false;
}

}  // namespace uking::action
