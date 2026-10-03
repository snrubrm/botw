#include "Game/AI/AI/aiTargetClimbSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

TargetClimbSelect::TargetClimbSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetClimbSelect::~TargetClimbSelect() = default;

bool TargetClimbSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetClimbSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    bool flag = false;
    auto* link = sub_71005D9050(mActor);
    if (link && ksys::act::isPlayerProfile(link)) {
        ksys::act::acc::PlayerBase player;
        ksys::act::acquireActor(&ksys::act::PlayerInfo::instance()->getPlayerLink(), &player);
        flag = player.m186();
    }
    if (flag)
        changeChild("対象よじ登り", params);
    else
        changeChild("対象通常", params);
}

void TargetClimbSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable())
        return;

    if (isCurrentChild("対象通常")) {
        auto* link = sub_71005D9050(mActor);
        if (!link || !ksys::act::isPlayerProfile(link))
            return;

        bool flag;
        {
            ksys::act::acc::PlayerBase player;
            ksys::act::acquireActor(&ksys::act::PlayerInfo::instance()->getPlayerLink(), &player);
            flag = player.m186();
        }
        if (flag)
            changeChild("対象よじ登り");
    } else if (isCurrentChild("対象よじ登り")) {
        bool flag = false;
        auto* link = sub_71005D9050(mActor);
        if (link && ksys::act::isPlayerProfile(link)) {
            ksys::act::acc::PlayerBase player;
            ksys::act::acquireActor(&ksys::act::PlayerInfo::instance()->getPlayerLink(), &player);
            flag = player.m186();
        }
        if (!flag)
            changeChild("対象通常");
    }
}

void TargetClimbSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetClimbSelect::loadParams_() {}

bool TargetClimbSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool TargetClimbSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

}  // namespace uking::ai
