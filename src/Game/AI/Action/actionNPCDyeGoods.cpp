#include "Game/AI/Action/actionNPCDyeGoods.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/gameSceneSubsys12.h"

namespace uking::action {

NPCDyeGoods::NPCDyeGoods(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCDyeGoods::~NPCDyeGoods() = default;

bool NPCDyeGoods::oneShot_() {
    if (auto* manager = ui::PauseMenuDataMgr::instance())
        manager->dyeGoodsStuff();
    if (auto* scene = GameSceneSubsys12::instance())
        scene->sub_7100664484(0, nullptr);
    return true;
}

}  // namespace uking::action
