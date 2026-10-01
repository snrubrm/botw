#include "Game/AI/AI/aiRemainElectricCannonRootBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

RemainElectricCannonRootBase::RemainElectricCannonRootBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

bool RemainElectricCannonRootBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainElectricCannonRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("待機");
    _50 = true;
}

void RemainElectricCannonRootBase::calc_() {
    auto* child = getCurrentChild();
    if (!child)
        return;

    auto* life = mActor->getLife();
    if (life && *life == 0) {
        changeChild("死亡");
        return;
    }

    if (m34())
        return;

    if (child->isChangeable()) {
        if (m35())
            m36();
        else
            m37();
    } else if (m39()) {
        m38();
    }

    child->setDynamicParam(_50, "IsLostPlayer");
    child->setDynamicParam(_54, "TargetPos");
}

void RemainElectricCannonRootBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainElectricCannonRootBase::loadParams_() {
    getStaticParam(&mSearchMaxDist_s, "SearchMaxDist");
    getStaticParam(&mSearchMinDist_s, "SearchMinDist");
    getStaticParam(&mSearchDistMargin_s, "SearchDistMargin");
}

void RemainElectricCannonRootBase::m36() {
    if (isCurrentChild("攻撃"))
        return;

    _50 = false;
    ksys::act::ai::InlineParamPack params;
    params.addBool(false, "IsLostPlayer", -1);
    params.addVec3(_54, "TargetPos", -1);
    changeChild("攻撃", &params);
}

void RemainElectricCannonRootBase::m38() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        m40();
}

bool RemainElectricCannonRootBase::m39() {
    return isCurrentChild("攻撃");
}

void RemainElectricCannonRootBase::m40() {
    _50 = true;
    changeChild("待機");
}

}  // namespace uking::ai
