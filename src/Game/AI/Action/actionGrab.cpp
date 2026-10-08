#include "Game/AI/Action/actionGrab.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

Grab::Grab(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

bool Grab::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void Grab::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    m32();
}

void Grab::leave_() {
    ActionWithPosAngReduce::leave_();
}

void Grab::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mGrabIdx_s, "GrabIdx");
    getStaticParam(&mCheckRadius_s, "CheckRadius");
    getStaticParam(&mCheckSpeed_s, "CheckSpeed");
    getStaticParam(&mAttOffset_s, "AttOffset");
}

void Grab::calc_() {
    ActionWithPosAngReduce::calc_();
    if (m33()) {
        auto* child = mActor->getConnectedCalcChild();
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(child)) {
            if (m34())
                sub_71005DC208(mActor, actor, *mGrabIdx_s);
            else
                mActor->resetConnectedCalcChild(false);
        } else {
            mActor->resetConnectedCalcChild(false);
        }
    }
    if (isFinishedAS(0, 0)) {
        if (!mActor->getConnectedCalcChild()) {
            setFailed();
        } else {
            auto* child = mActor->getConnectedCalcChild();
            if (auto* actor = sead::DynamicCast<ksys::act::Actor>(child))
                sub_71005DC41C(actor);
            setFinished();
        }
    }
}

void Grab::m32() {
    playAS("Grab", false, 0, 0, -1.0f);
}

bool Grab::m33() {
    return mActor->getASList()->x(0x45, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true);
}

}  // namespace uking::action
