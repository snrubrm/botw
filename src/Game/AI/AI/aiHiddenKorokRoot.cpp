#include "Game/AI/AI/aiHiddenKorokRoot.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"

namespace uking::ai {

HiddenKorokRoot::HiddenKorokRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HiddenKorokRoot::~HiddenKorokRoot() {
    if (_78) {
        ksys::phys::CollisionInfo::free(_78);
        _78 = nullptr;
    }
}

// NON_MATCHING: the original clears both layer masks of _78 with one 8-byte store
bool HiddenKorokRoot::init_(sead::Heap* heap) {
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
        npc->_fe8 |= 0x20000000;

    _78 = ksys::phys::CollisionInfo::make(heap, mActor->getName());
    _78->getLayerMask(ksys::phys::ContactLayerType::Entity).makeAllZero();
    _78->getLayerMask(ksys::phys::ContactLayerType::Sensor).makeAllZero();
    _78->enableLayer(ksys::phys::ContactLayer::EntityObject);
    _78->enableLayer(ksys::phys::ContactLayer::EntitySmallObject);
    _78->enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    return true;
}

void HiddenKorokRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HiddenKorokRoot::leave_() {
    if (_82)
        _82 = false;
}

bool HiddenKorokRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() != 0x1800010)
        return false;

    if (auto* schedule = mActor->getSchedule())
        schedule->_122 = false;
    xlinkEventOn(mActor, 26, 0, false);
    callHiddenKorokFoundDemo();
    return true;
}

void HiddenKorokRoot::invokedTalk() {
    if (auto* event_mgr = ksys::evt::Manager::instance()) {
        ksys::evt::Metadata metadata(mActor->getName().cstr(), "Talk", "");
        event_mgr->callEvent(metadata, mActor);
    }
}

void HiddenKorokRoot::invokedExamine() {
    xlinkEventOn(mActor, 26, 0, false);
    callHiddenKorokFoundDemo();
}

void HiddenKorokRoot::callHiddenKorokFoundDemo() {
    if (!_80) {
        _82 = true;
        _80 = true;
    }

    auto* event_mgr = ksys::evt::Manager::instance();
    if (!event_mgr)
        return;

    ksys::evt::Metadata metadata;
    metadata.setEventStartWaitFrame(*mKorokEventStartWaitFrame_m);
    if (mPlacementType_m == "Ground")
        metadata.init("Demo017_0", "HiddenKorok_Ground");
    else if (mPlacementType_m == "Air")
        metadata.init("Demo017_0", "HiddenKorok_Air");
    else
        return;
    event_mgr->callEvent(metadata, mActor);
}

void HiddenKorokRoot::loadParams_() {
    getStaticParam(&mPainTalkHitSpeed_s, "PainTalkHitSpeed");
    getStaticParam(&mPainTalkDistance_s, "PainTalkDistance");
    getMapUnitParam(&mKorokEventStartWaitFrame_m, "KorokEventStartWaitFrame");
    getMapUnitParam(&mIsAppearCheck_m, "IsAppearCheck");
    getMapUnitParam(&mPlacementType_m, "PlacementType");
    getMapUnitParam(&mIsHiddenKorokLiftAppear_m, "IsHiddenKorokLiftAppear");
    getMapUnitParam(&mIsInvisibleKorok_m, "IsInvisibleKorok");
}

}  // namespace uking::ai
