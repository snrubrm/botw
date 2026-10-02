#include "Game/AI/Action/actionForkForceIgniteCarriedActor.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkForceIgniteCarriedActor::ForkForceIgniteCarriedActor(const InitArg& arg) : Fork(arg) {}

ForkForceIgniteCarriedActor::~ForkForceIgniteCarriedActor() = default;

bool ForkForceIgniteCarriedActor::init_(sead::Heap* heap) {
    if (!Fork::init_(heap))
        return false;
    return _38.init(heap);
}

void ForkForceIgniteCarriedActor::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    _38.enter(params);
}

void ForkForceIgniteCarriedActor::leave_() {
    _38.leave();
    Fork::leave_();
}

void ForkForceIgniteCarriedActor::loadParams_() {
    Fork::loadParams_();
    _38.loadParams();
    getStaticParam(&mIsCheckAfterChildState_s, "IsCheckAfterChildState");
}

void ForkForceIgniteCarriedActor::calc_() {
    if (isFinished() || isFailed()) {
        if (*mIsCheckAfterChildState_s && !mActor->getConnectedCalcChild())
            setFailed();
        return;
    }

    if (_38.isFinished()) {
        setEndState();
        return;
    }
    if (_38.isFailed()) {
        setFailed();
        return;
    }

    Fork::calc_();
    _38.calc();
    _38.sub_71002A7A38();
}

}  // namespace uking::action
