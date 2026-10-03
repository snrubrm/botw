#include "Game/AI/AI/aiAttackGrave.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::ai {

AttackGrave::AttackGrave(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AttackGrave::~AttackGrave() = default;

bool AttackGrave::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AttackGrave::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    if (auto* xlink = mActor->getXLink())
        xlink->_cc.reset(0x80000);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(getPlayerPosition(), "TargetPos", -1);
    pack.addActor(ksys::act::PlayerInfo::getSomeProcLink(), "TargetActor", -1);
    changeChild("先行動", &pack);
}

void AttackGrave::calc_() {
    bool is_pre_or_mid = isCurrentChild("中行動");
    if (!is_pre_or_mid)
        is_pre_or_mid = isCurrentChild("先行動");
    if (is_pre_or_mid && _70._30) {
        mActor->killWithDropsAndEffects(0);
        return;
    }

    if (isCurrentChild("後行動")) {
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("先行動")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(getPlayerPosition(), "TargetPos", -1);
            if (getCurrentChild()->isFailed())
                changeChild("後行動", &pack);
            else
                changeChild("中行動", &pack);
        } else if (isCurrentChild("中行動")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(getPlayerPosition(), "TargetPos", -1);
            changeChild("後行動", &pack);
        } else {
            setFinished();
        }
    }

    if (isCurrentChild("先行動")) {
        ksys::act::ai::InlineParamPack unused_pack;
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        if (!player.m194()) {
            sead::Vector3f pos;
            player.getActorMtx().getTranslation(pos);
            getCurrentChild()->setDynamicParam(pos, "TargetPos");
        }
        if (_38._30) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(getPlayerPosition(), "TargetPos", -1);
            changeChild("中行動", &pack);
        }
    }
}

bool AttackGrave::handleMessage_(const ksys::Message& message) {
    if (_38.m2(message))
        return true;
    if (_70.m2(message)) {
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
        return true;
    }
    return false;
}

void AttackGrave::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AttackGrave::loadParams_() {}

}  // namespace uking::ai
