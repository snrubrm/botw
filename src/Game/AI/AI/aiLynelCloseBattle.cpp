#include "Game/AI/AI/aiLynelCloseBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

LynelCloseBattle::LynelCloseBattle(const InitArg& arg) : EnemyBattle(arg) {}

LynelCloseBattle::~LynelCloseBattle() = default;

bool LynelCloseBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void LynelCloseBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
    *mLynelAIFlags_a |= 0x800;
}

void LynelCloseBattle::m34(ksys::act::ai::InlineParamPack* params) {
    if ((*mLynelAIFlags_a & 0x800) &&
        !(*mBackAngleAction_s == 2 && sub_710048FA58() && !sub_7100381E7C())) {
        EnemyBattle::m34(params);
        return;
    }
    sub_7100381ED4();
    m38();
}

void LynelCloseBattle::calc_() {
    EnemyBattle::calc_();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable())
        return;
    if (*mBackAngleAction_s == 0 || !isCurrentChild("戦闘準備") || !sub_710048FA58())
        return;

    switch (*mBackAngleAction_s) {
    case 1:
        setFailed();
        break;
    case 2:
        m38();
        break;
    default:
        break;
    }
}

void LynelCloseBattle::leave_() {
    EnemyBattle::leave_();
}

void LynelCloseBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mBackAngleAction_s, "BackAngleAction");
    getStaticParam(&mBackAngle_s, "BackAngle");
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
}

bool LynelCloseBattle::isFinished() const {
    return ActionBase::isFinished() ||
           (isCurrentChild("戦闘攻撃") && getCurrentChild()->isFinished() &&
            (*mBackAngleAction_s != 1 || !sub_710048FA58()));
}

// Whether the target is within BackAngle (radians) of directly behind the actor,
// measured in the plane perpendicular to the actor's up direction.
bool LynelCloseBattle::sub_710048FA58() const {
    if (*mBackAngle_s > 0.0f) {
        const sead::Vector3f& target_pos = sub_71005D9330(mActor);
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        const sead::Vector3f up = getUpDir(mActor);

        sead::Vector3f to_target = target_pos;
        to_target -= pos;
        ksys::util::sub_71011EFA00(&to_target, to_target, up);
        to_target.normalize();

        sead::Vector3f front;
        mActor->getMtx().getBase(front, 2);
        ksys::util::sub_71011EFA00(&front, front, up);
        front.normalize();

        const f32 angle = sead::Mathf::pi() - *mBackAngle_s;
        return !(front.dot(to_target) >= sead::Mathf::cos(angle));
    }
    return false;
}

bool LynelCloseBattle::isFailed() const {
    if (ActionBase::isFailed() || getCurrentChild()->isFailed())
        return true;
    if (*mBackAngleAction_s == 1 && isCurrentChild("戦闘攻撃") && getCurrentChild()->isFinished())
        return sub_710048FA58();
    return false;
}

}  // namespace uking::ai
