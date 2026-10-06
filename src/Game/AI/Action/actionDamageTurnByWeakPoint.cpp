#include "Game/AI/Action/actionDamageTurnByWeakPoint.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

DamageTurnByWeakPoint::DamageTurnByWeakPoint(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DamageTurnByWeakPoint::~DamageTurnByWeakPoint() = default;

bool DamageTurnByWeakPoint::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DamageTurnByWeakPoint::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e08._10.getTranslation(_48);
    playAS(mASName_s.cstr(), false, 0, 0, -1.f);
    sub_710073FA90(&_54, mActor);
}

void DamageTurnByWeakPoint::leave_() {
    ksys::act::ai::Action::leave_();
}

void DamageTurnByWeakPoint::loadParams_() {
    getStaticParam(&mTurnSpeed_s, "TurnSpeed");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: the original loads the actor's translation before it copies _48 to the stack (load order only)
void DamageTurnByWeakPoint::sub_71000E6400() {
    sead::Vector3f dir = _48;
    dir -= mActor->getMtx().getTranslation();
    dir.normalize();
    sub_710073FA94(&_54, mActor);
    sub_71007407F0(&_54, dir, sead::Vector3f::ey, true, *mTurnSpeed_s);
    sub_7100740F1C(_54, mActor);
}

void DamageTurnByWeakPoint::calc_() {
    if (sub_71005DD798(mActor, 41, nullptr, 0, 0))
        sub_71000E6400();
    else
        sub_7100738AA8(mActor, *mAngReduceRatio_s);
    auto* actor = mActor;
    sub_7100738488(actor, *mPosReduceRatio_s, getGravity(actor) * (1.0f / 900.0f));
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
