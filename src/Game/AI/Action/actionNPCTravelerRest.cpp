#include "Game/AI/Action/actionNPCTravelerRest.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::action {

NPCTravelerRest::NPCTravelerRest(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTravelerRest::~NPCTravelerRest() = default;

void NPCTravelerRest::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCTravelerRest::leave_() {
    if (mActor->get1a0())
        return;
    auto* obj = mActor->getMapObject();
    if (obj && obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000))
        return;
    if (testRootAiFlag(ksys::act::ai::RootAiFlag::_5))
        return;
    sub_71005D7518(mActor, true);
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
        npc->_fe8 &= ~0x4000;
    mActor->getASList()->goLimpFromHeadShotMaybe(0x3b, "", true);
}

void NPCTravelerRest::loadParams_() {
    getDynamicParam(&mIsWarpHorse_d, "IsWarpHorse");
}

void NPCTravelerRest::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
}

}  // namespace uking::action
