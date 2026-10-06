#include "Game/AI/Action/actionPlayASForTimelineWithSword.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::action {

PlayASForTimelineWithSword::PlayASForTimelineWithSword(const InitArg& arg)
    : PlayASForTimeline(arg) {}

void PlayASForTimelineWithSword::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForTimeline::enter_(params);
}

// NON_MATCHING: the original branches and stores true / false separately (two store paths); written as
// `if (hold) ... = true; else ... = false;` the stores are sunk into one `strb w20` as well.
void PlayASForTimelineWithSword::leave_() {
    PlayASForTimeline::leave_();
    if (auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor))
        actor->getWeapons()->mWeapons[0]._10 = *mIsHold_d;
}

void PlayASForTimelineWithSword::loadParams_() {
    PlayASForTimeline::loadParams_();
    getDynamicParam(&mIsHold_d, "IsHold");
}

void PlayASForTimelineWithSword::calc_() {
    PlayASForTimeline::calc_();
    if (mActor->getASList()->x(83, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        if (auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor))
            actor->getWeapons()->mWeapons[0]._10 = false;
    }
    if (mActor->getASList()->x(84, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        if (auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor))
            actor->getWeapons()->mWeapons[0]._10 = true;
    }
}

}  // namespace uking::action
