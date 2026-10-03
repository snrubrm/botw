#include "Game/AI/Action/actionTurnToActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

TurnToActor::TurnToActor(const InitArg& arg) : TurnToActorBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
TurnToActor::~TurnToActor() {
    ;
}

bool TurnToActor::init_(sead::Heap* heap) {
    return TurnToActorBase::init_(heap);
}

void TurnToActor::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnToActorBase::enter_(params);
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115BC28(m38(), -1.0f);
}

void TurnToActor::leave_() {
    TurnToActorBase::leave_();
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115C11C();
}

f32 TurnToActor::m34() {
    if (auto* as_list = mActor->getASList())
        return as_list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_71011632F8);
    return 0.0f;
}

const sead::SafeString& TurnToActor::m38() {
    auto* as_list = mActor->getASList();
    if (!as_list)
        return sead::SafeString::cEmptyString;
    const sead::SafeString* name;
    if (!mDemoASName_d.isEmpty())
        name = &mDemoASName_d;
    else if (!mASName_d.isEmpty())
        name = &mASName_d;
    else
        return sead::SafeString::cEmptyString;
    as_list->sub_710115AA68(*name);
    return *name;
}

void TurnToActor::loadParams_() {
    TurnToActorBase::loadParams_();
    getDynamicParam(&mASSlot_d, "ASSlot");
    getDynamicParam(&mSequenceBank_d, "SequenceBank");
    getDynamicParam(&mIsIgnoreSame_d, "IsIgnoreSame");
    getDynamicParam(&mIsChangeable_d, "IsChangeable");
    getDynamicParam(&mASName_d, "ASName");
    getDynamicParam(&mDemoASName_d, "DemoASName");
}

void TurnToActor::calc_() {
    TurnToActorBase::calc_();
}

}  // namespace uking::action
