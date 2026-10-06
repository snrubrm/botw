#include "Game/AI/Action/actionWarpOwnedHorse.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

WarpOwnedHorse::WarpOwnedHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpOwnedHorse::~WarpOwnedHorse() = default;

void WarpOwnedHorse::loadParams_() {}

// NON_MATCHING: same code; the original keeps a separate accessor-destructor block on the success path and the return value in
// w20 (ours merges the destructor tails)
bool WarpOwnedHorse::oneShot_() {
    auto* object = mActor->getMapObject();
    if (!object)
        return false;
    auto* link_data = object->getLinkData();
    if (!link_data)
        return false;
    auto* anchor = link_data->sub_7100D4EFA4("HorsePlacmentAnchor");
    if (!anchor)
        return false;
    auto* manager = HorseMgr::instance();
    if (!manager)
        return false;

    auto* link = &manager->mOwnedHorse;
    ksys::act::ActorConstDataAccess accessor;
    if (link->hasProc()) {
        if (ksys::act::acquireActor(link, &accessor)) {
            const sead::Vector3f rotation = anchor->getRotate();
            const sead::Vector3f translation = anchor->getTranslate();
            _1c.makeSRT(sead::Vector3f::ones, rotation, translation);
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800015), &_1c, true);
            return true;
        }
    }
    return false;
}

}  // namespace uking::action
