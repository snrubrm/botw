#include "Game/AI/AI/aiLastAttackerSpecialActionSelect.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_710001A69C.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

LastAttackerSpecialActionSelect::LastAttackerSpecialActionSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

LastAttackerSpecialActionSelect::~LastAttackerSpecialActionSelect() = default;

bool LastAttackerSpecialActionSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastAttackerSpecialActionSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto* link = &enemy->_e08._0;
        if (sub_7100739930(mActor, link)) {
            changeChild("特殊相手", params);
            return;
        }
        if (*mIsAngerActorSpecial_s) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(link, &accessor);
            if (sub_710001A69C(&accessor, 0x40))
                changeChild("特殊相手", params);
            else
                changeChild("通常相手", params);
            return;
        }
    }
    changeChild("通常相手", params);
}

void LastAttackerSpecialActionSelect::calc_() {}

bool LastAttackerSpecialActionSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool LastAttackerSpecialActionSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

void LastAttackerSpecialActionSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastAttackerSpecialActionSelect::loadParams_() {
    getStaticParam(&mIsAngerActorSpecial_s, "IsAngerActorSpecial");
}

}  // namespace uking::ai
