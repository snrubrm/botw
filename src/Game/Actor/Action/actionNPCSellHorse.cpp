#include "Game/Actor/Action/actionNPCSellHorse.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::action {

NPCSellHorse::NPCSellHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCSellHorse::~NPCSellHorse() = default;

// Registers the first linked horse that the player does not own yet under the name in Horse_NewName.
bool NPCSellHorse::oneShot_() {
    auto* map_object = mActor->getMapObject();
    if (!map_object)
        return false;
    auto* link_data = map_object->getLinkData();
    if (!link_data || link_data->mObjects.size() == 0)
        return false;

    for (auto it = link_data->mObjects.begin(); it != link_data->mObjects.end(); ++it) {
        auto* object = *it;
        if (!object)
            continue;
        auto* actor = object->tryGetActor(false);
        if (!actor)
            continue;
        if (actor->getProfile() != "Horse")
            continue;
        if (!sead::IsDerivedFrom<act::HorseBase>(actor))
            continue;
        if (HorseMgr::instance()->sub_7100E84AB8(actor))
            continue;
        const char* new_name;
        if (!ksys::gdt::Manager::instance()->getParamBypassPerm().get().getStr64(&new_name, "Horse_NewName"))
            break;
        if (HorseMgr::instance()->sub_7100E84A04(actor, new_name, false))
            return true;
    }
    return false;
}

}  // namespace uking::action
