#include "Game/AI/Action/actionNPCDeliverHorse.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::action {

NPCDeliverHorse::NPCDeliverHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCDeliverHorse::~NPCDeliverHorse() = default;

// NON_MATCHING: stack layout only: the original keeps the two SafeString temporaries ("Horse_SelectedIndex" and
// "HorsePlacmentAnchor") in separate slots (frame 0x50), ours merges them (frame 0x40); the copy of the anchor
// translation then also loads x before z
bool NPCDeliverHorse::oneShot_() {
    s32 index = 0;
    const bool success =
        ksys::gdt::Manager::instance()->getParamBypassPerm().get().getS32(&index, "Horse_SelectedIndex");
    if (!success || index < 0)
        return false;
    auto* object = mActor->getMapObject();
    if (!object)
        return false;
    auto* link_data = object->getLinkData();
    if (!link_data)
        return false;
    auto* anchor = link_data->sub_7100D4EFA4("HorsePlacmentAnchor");
    if (!anchor)
        return false;
    const sead::Vector3f translation = anchor->getTranslate();
    HorseMgr::instance()->sub_7100E85CAC(ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
                                         index, translation, mActor, false);
    return true;
}

}  // namespace uking::action
