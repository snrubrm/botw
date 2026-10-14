#include "Game/Actor/AI/aiLargeCannonRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

LargeCannonRoot::LargeCannonRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

bool LargeCannonRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LargeCannonRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("待機");
    _50 = true;
}

void LargeCannonRoot::calc_() {
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

void LargeCannonRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LargeCannonRoot::loadParams_() {
    getStaticParam(&mSearchMaxDist_s, "SearchMaxDist");
    getStaticParam(&mSearchMinDist_s, "SearchMinDist");
    getStaticParam(&mSearchDistMargin_s, "SearchDistMargin");
}

bool LargeCannonRoot::m35() {
    const f32 dist = sead::Mathf::sqrt(
        ksys::util::sqXZDistance(getPlayerPosition(), mActor->getMtx().getTranslation()));
    f32 max_dist = m41();
    if (isCurrentChild("攻撃"))
        max_dist += *mSearchDistMargin_s;
    const f32 min_dist = *mSearchMinDist_s;
    _51 = (dist <= max_dist) & (min_dist <= dist);
    return _51;
}

void LargeCannonRoot::m36() {
    if (isCurrentChild("攻撃"))
        return;

    _50 = false;
    ksys::act::ai::InlineParamPack params;
    params.addBool(false, "IsLostPlayer", -1);
    params.addVec3(_54, "TargetPos", -1);
    changeChild("攻撃", &params);
}

void LargeCannonRoot::m38() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        m40();
}

bool LargeCannonRoot::m39() {
    return isCurrentChild("攻撃");
}

void LargeCannonRoot::m40() {
    _50 = true;
    changeChild("待機");
}

}  // namespace uking::ai
