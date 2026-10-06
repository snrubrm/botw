#include "Game/AI/Action/actionAnmDrivenHoverTurn.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

AnmDrivenHoverTurn::AnmDrivenHoverTurn(const InitArg& arg) : AnmDrivenHoverBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
AnmDrivenHoverTurn::~AnmDrivenHoverTurn() {
    ;
}

bool AnmDrivenHoverTurn::init_(sead::Heap* heap) {
    return AnmDrivenHoverBase::init_(heap);
}

void AnmDrivenHoverTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    AnmDrivenHoverBase::enter_(params);
    sub_710073FA90(&_78, mActor);
    _9c = mActor->getAngVelocity().y;
}

void AnmDrivenHoverTurn::leave_() {
    AnmDrivenHoverBase::leave_();
}

void AnmDrivenHoverTurn::loadParams_() {
    AnmDrivenHoverBase::loadParams_();
    getStaticParam(&mParams.mRotSpeed_s, "RotSpeed");
    getStaticParam(&mParams.mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mParams.mRotAccRatio_s, "RotAccRatio");
    getStaticParam(&mParams.mFinRotate_s, "FinRotate");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void AnmDrivenHoverTurn::calc_() {
    AnmDrivenHoverBase::calc_();

    auto* actor = mActor;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    const sead::Vector3f up = getUpDir(actor);

    sead::Vector3f to_target = *mParams.mTargetPos_d;
    to_target -= pos;
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();

    ksys::VFR::chase(&_9c, *mParams.mRotSpeed_s, *mParams.mRotSpeed_s * *mParams.mRotAccRatio_s);
    sub_710073FA94(&_78, mActor);
    sub_710074006C(&_78, to_target, up, true, *mParams.mBaseRotRatio_s, _9c, 0.0f);
    sub_7100740F1C(_78, mActor);

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, up);
    front.normalize();
    if (to_target.dot(front) >= sead::Mathf::cos(*mParams.mFinRotate_s))
        setFinished();
}

}  // namespace uking::action
