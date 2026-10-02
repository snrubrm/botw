#include "Game/AI/Action/actionPlayASForTimelineWithSword.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"

namespace uking::action {

PlayASForTimelineWithSword::PlayASForTimelineWithSword(const InitArg& arg)
    : PlayASForTimeline(arg) {}

void PlayASForTimelineWithSword::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForTimeline::enter_(params);
}

// NON_MATCHING: the original branches and stores true / false separately (two store paths)
void PlayASForTimelineWithSword::leave_() {
    PlayASForTimeline::leave_();
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (!actor)
        return;
    actor->getWeapons()->mWeapons[0]._10 = *mIsHold_d;
}

void PlayASForTimelineWithSword::loadParams_() {
    PlayASForTimeline::loadParams_();
    getDynamicParam(&mIsHold_d, "IsHold");
}

void PlayASForTimelineWithSword::calc_() {
    PlayASForTimeline::calc_();
}

}  // namespace uking::action
