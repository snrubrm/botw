#include "Game/Actor/Action/actionToCDungeon.h"
#include <prim/seadSafeString.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Scene/gameScene.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

ToCDungeon::ToCDungeon(const InitArg& arg) : ChangeSceneBase(arg) {}

ToCDungeon::~ToCDungeon() = default;

bool ToCDungeon::init_(sead::Heap* heap) {
    return ChangeSceneBase::init_(heap);
}

void ToCDungeon::enter_(ksys::act::ai::InlineParamPack* params) {
    ChangeSceneBase::enter_(params);
    if (isFinished() || isFailed())
        return;

    const auto* manager = ksys::evt::Manager::instance();
    if (manager->_1d2f4_bytes[0] & 0x20) {
        setFinished();
        return;
    }

    sead::SafeString dungeon_name;
    sead::Vector3f pos;
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        player.getActorMtx().getTranslation(pos);
        if (ui::findDungeonNameForPositionImpl(100.0f, &dungeon_name, &pos)) {
            sead::FixedSafeString<32> map;
            sead::FixedSafeString<32> pos_name("Entrance_1");
            map.format("CDungeon/%s", dungeon_name.cstr());
            initWarpEventFlow(map, pos_name);
            changeSceneImpl(map, pos_name, _48, 0);
            return;
        }
    }
    setFailed();
}

void ToCDungeon::leave_() {
    ChangeSceneBase::leave_();
}

void ToCDungeon::loadParams_() {
    ChangeSceneBase::loadParams_();
}

void ToCDungeon::calc_() {
    ChangeSceneBase::calc_();
}

}  // namespace uking::action
