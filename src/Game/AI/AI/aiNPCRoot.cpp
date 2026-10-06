#include "Game/AI/AI/aiNPCRoot.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Utils/Thread/Message.h"

// Declaration only; the original source namespace of this actor cleanup helper is unknown.
void sub_71007132E4(ksys::act::Actor* actor);

namespace uking::ai {

NPCRoot::NPCRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCRoot::~NPCRoot() = default;

bool NPCRoot::init_(sead::Heap* heap) {
    _68 = sead::DynamicCast<act::NPC>(mActor);
    return true;
}

void NPCRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCRoot::onPreDelete() {
    sub_71007132E4(mActor);
}

void NPCRoot::loadParams_() {
    getStaticParam(&mReleaseInterest2Time_s, "ReleaseInterest2Time");
    getStaticParam(&mPlayerHitVelocity_s, "PlayerHitVelocity");
    getStaticParam(&mStaggerUpperASName_s, "StaggerUpperASName");
    getStaticParam(&mStaggerUpperRunASName_s, "StaggerUpperRunASName");
}

// NON_MATCHING: scheduling (the original loads the name's first character and cNullChar before mActor)
void NPCRoot::m34() {
    const sead::SafeString name = mActor->getASList()->sub_710115ECF4(59, 1);
    mActor->getASList()->x_2(66, 35, name.isEmpty() && _201, false);
    changeChild("Timeline");
    _201 = false;
    mActor->getASList()->x_2(66, 35, false, false);
}

bool NPCRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() != ksys::MessageType(0x08000034))
        return false;
    if (_68) {
        if (isCurrentChild("Timeline") || isCurrentChild("Rest")) {
            sead::FixedSafeString<64> name;
            mActor->getRootAi()->getCurrentName(&name, nullptr);
            _68->_a70.copy(name);
        }
        setRootAiFlag(ksys::act::ai::RootAiFlag::_5);
    }
    changeChild("EventStartWait", nullptr);
    return true;
}

// 0x71004dc204
bool NPCRoot::sub_71004DC204() {
    ksys::act::acc::PlayerBase accessor;
    ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &accessor);
    sead::FixedSafeString<32> series;
    accessor.getArmorSeriesType(&series);
    return series == "Black" || series == "Stalfos" || series == "PhantomGanon";
}

}  // namespace uking::ai
