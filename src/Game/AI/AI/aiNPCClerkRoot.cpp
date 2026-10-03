#include "Game/AI/AI/aiNPCClerkRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::ai {

NPCClerkRoot::NPCClerkRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCClerkRoot::~NPCClerkRoot() = default;

bool NPCClerkRoot::init_(sead::Heap* heap) {
    if (!NPCRoot::init_(heap))
        return false;
    _240.initWithName(mActor, mActor->getName(), "ClerkAsk");
    return true;
}

// NON_MATCHING: the original loads mActor for the first argument of sub_7100EE2850 AFTER the hasTag call (ours
// loads it before and keeps it in x20); a `const bool` local for the hasTag result would match
void NPCClerkRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
    {
        ksys::act::ActorConstDataAccess accessor;
        _238 = ksys::act::sub_7100EE2850(
            mActor, &accessor, ksys::act::hasTag(mActor, ksys::act::tags::GroupingDisplayItem),
            nullptr, nullptr);
    }
    mActor->resetConnectedCalcChild(false);
    _239 = false;
    if (_240.mEventFlow)
        return;
    if (auto* object = mActor->getMapObject()) {
        if (auto* link_data = object->getLinkData()) {
            auto& links = link_data->mLinksToSelf.links;
            for (s32 i = 0; i < links.size(); ++i) {
                if (links[i].type == ksys::map::MapLinkDefType::ForSale) {
                    _240.loadEvent();
                    break;
                }
            }
        }
    }
}

// NON_MATCHING: same as enter_ (load of mActor for the first argument vs the hasTag call)
void NPCClerkRoot::calc_() {
    NPCRoot::calc_();
    ksys::act::ActorConstDataAccess accessor;
    _238 = ksys::act::sub_7100EE2850(
        mActor, &accessor, ksys::act::hasTag(mActor, ksys::act::tags::GroupingDisplayItem), nullptr,
        nullptr);
}

void NPCClerkRoot::leave_() {
    NPCRoot::leave_();
}

void NPCClerkRoot::onPreDelete() {
    NPCRoot::onPreDelete();
    if (_240.mEventFlow)
        _240.unloadEvent();
}

void NPCClerkRoot::loadParams_() {
    NPCRoot::loadParams_();
}

}  // namespace uking::ai
