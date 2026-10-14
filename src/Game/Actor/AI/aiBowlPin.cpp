#include "Game/Actor/AI/aiBowlPin.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"

namespace uking::ai {

BowlPin::BowlPin(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BowlPin::~BowlPin() = default;

bool BowlPin::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BowlPin::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("オフ");
}

void BowlPin::calc_() {
    auto* actor = mActor;
    sead::Vector3f up;
    actor->getMtx().getBase(up, 1);
    up.normalize();
    const bool fallen = up.y < sead::Mathf::sin(sead::Mathf::deg2rad(*mDegree_s));
    auto* child = getCurrentChild();

    if ((isCurrentChild("ピンと衝突") || isCurrentChild("雪玉と衝突")) && child->isChangeable())
        changeChild("オフ待機");
    else if (isCurrentChild("オフ待機") && child->isChangeable() && fallen)
        changeChild("オン");
    else if (isCurrentChild("オン待機") && child->isChangeable() && !fallen)
        changeChild("オフ");
    else if (isCurrentChild("オフ") && child->isFinished())
        changeChild("オフ待機");
    else if (isCurrentChild("オン") && child->isFinished())
        changeChild("オン待機");

    if ((_40 & 3) == 3)
        return;
    if (!sub_71007A4178(actor, false))
        return;

    auto* sensed = sub_71007A40D0(actor, 0);
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&sensed->_50, &accessor);
    if (accessor.getName() == "BowlPin" && !(_40 & 2) && child->isChangeable()) {
        _40 |= 2;
        changeChild("ピンと衝突");
    } else if (accessor.getName() == "SnowBowl" && !(_40 & 1) && child->isChangeable()) {
        _40 |= 1;
        changeChild("雪玉と衝突");
    }
}

void BowlPin::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BowlPin::loadParams_() {
    getStaticParam(&mDegree_s, "Degree");
}

}  // namespace uking::ai
