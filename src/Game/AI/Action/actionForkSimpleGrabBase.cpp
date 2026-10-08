#include "Game/AI/Action/actionForkSimpleGrabBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkSimpleGrabBase::ForkSimpleGrabBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSimpleGrabBase::~ForkSimpleGrabBase() = default;

bool ForkSimpleGrabBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSimpleGrabBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _30 = false;
}

void ForkSimpleGrabBase::leave_() {
    if (!_30)
        mActor->resetConnectedCalcChild(true);
}

void ForkSimpleGrabBase::loadParams_() {
    getStaticParam(&mGrabIdx_s, "GrabIdx");
    getStaticParam(&mIsNoGrabSuccess_s, "IsNoGrabSuccess");
}

void ForkSimpleGrabBase::calc_() {
    if (mActor->getASList()->x(0x45, nullptr, 0, 0,
                               &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        _30 = true;
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild())) {
            if (m32() & 1)
                sub_71005DC208(mActor, actor, *mGrabIdx_s);
            else
                mActor->resetConnectedCalcChild(true);
        } else {
            mActor->resetConnectedCalcChild(true);
        }
    }
    if (isFinishedAS(0, 0)) {
        if (mActor->getConnectedCalcChild()) {
            if (auto* actor =
                    sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild()))
                sub_71005DC41C(actor);
            setFinished();
        } else {
            if (*mIsNoGrabSuccess_s)
                setFinished();
            else
                setFailed();
        }
    }
}

int ForkSimpleGrabBase::m32() {
    return 0;
}

}  // namespace uking::action
