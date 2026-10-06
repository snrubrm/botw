#include "Game/AI/Action/actionTurnToActor.h"
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

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

// NON_MATCHING: register allocation only (the last `add x8, x8, #0x2c` uses x11 here).
// `Actor::_7d0` points to an object starting with the actor's Matrix34f (type not known yet).
sead::Matrix34f TurnToActor::m33() {
    sead::Matrix34f result;
    if (const auto* mtx = static_cast<const sead::Matrix34f*>(mActor->get7d0())) {
        sead::Matrix34f trans;
        trans.makeT(mtx->getTranslation());
        const f32 yaw = sead::Mathf::atan2(mtx->m[0][2], mtx->m[2][2]);
        sead::Matrix34f rot;
        rot.makeR(sead::Vector3f(0, yaw, 0));
        result.setMul(trans, rot);
    } else {
        result.makeZero();
    }
    return result;
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
