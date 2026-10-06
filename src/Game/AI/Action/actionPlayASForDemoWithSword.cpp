#include "Game/AI/Action/actionPlayASForDemoWithSword.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::action {

PlayASForDemoWithSword::PlayASForDemoWithSword(const InitArg& arg) : PlayASForDemo(arg) {}

void PlayASForDemoWithSword::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForDemo::enter_(params);
}

void PlayASForDemoWithSword::leave_() {
    PlayASForDemo::leave_();
    if (auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor)) {
        if (*mIsHold_d) {
            actor->getWeapons()->mWeapons[0]._10 = true;
            if (actor->getWeapons()->mWeapons[1].link.hasProc())
                actor->getWeapons()->mWeapons[1]._10 = true;
        } else {
            actor->getWeapons()->mWeapons[0]._10 = false;
            if (actor->getWeapons()->mWeapons[1].link.hasProc())
                actor->getWeapons()->mWeapons[1]._10 = false;
        }
    }
}

void PlayASForDemoWithSword::loadParams_() {
    PlayASForDemo::loadParams_();
    getDynamicParam(&mIsHold_d, "IsHold");
}

void PlayASForDemoWithSword::calc_() {
    PlayASForDemo::calc_();
    if (mActor->getASList()->x(83, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        if (auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor)) {
            actor->getWeapons()->mWeapons[0]._10 = false;
            if (actor->getWeapons()->mWeapons[1].link.hasProc())
                actor->getWeapons()->mWeapons[1]._10 = false;
        }
    }
    if (mActor->getASList()->x(84, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        if (auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor)) {
            actor->getWeapons()->mWeapons[0]._10 = true;
            if (actor->getWeapons()->mWeapons[1].link.hasProc())
                actor->getWeapons()->mWeapons[1]._10 = true;
        }
    }
}

}  // namespace uking::action
