#include "Game/AI/Action/actionRestartStageFromGameOver.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameSaveSystem.h"
#include "Game/gameScene.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

RestartStageFromGameOver::RestartStageFromGameOver(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RestartStageFromGameOver::~RestartStageFromGameOver() = default;

bool RestartStageFromGameOver::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RestartStageFromGameOver::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
    if (auto* save_system = SaveSystem::instance())
        save_system->_1a50 |= 0x40;
    if (auto* gdm = ksys::gdt::Manager::instance())
        gdm->onRestartStageFromGameOverMaybe();
    setIsRestartStageFromGameOver();
    if (sIsRestartStageFromGameOver) {
        if (auto* player_info = ksys::act::PlayerInfo::instance()) {
            player_info->updateLifeAfterGameOver();
            GameScene::sub_71007AEF94();
        }
    }
}

void RestartStageFromGameOver::leave_() {
    ksys::act::ai::Action::leave_();
}

void RestartStageFromGameOver::loadParams_() {}

void RestartStageFromGameOver::calc_() {
    if (!isFinished() && !isFailed() && sub_71007AF558() && ui::sub_7100A96688()) {
        setFinished();
        mFlags.set(Flag::Changeable);
    }
}

}  // namespace uking::action
