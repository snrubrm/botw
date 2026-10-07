#include "Game/AI/Action/actionBattleDungeonBGMAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Sound/sndBgmMgr.h"

namespace uking::action {

BattleDungeonBGMAction::BattleDungeonBGMAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BattleDungeonBGMAction::~BattleDungeonBGMAction() = default;

bool BattleDungeonBGMAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BattleDungeonBGMAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BattleDungeonBGMAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void BattleDungeonBGMAction::loadParams_() {}

void BattleDungeonBGMAction::calc_() {
    const bool active = mActor->checkBasicSig();
    auto* bgm = ksys::snd::sub_7100FFD9D0();
    if (active) {
        if (bgm)
            bgm->sub_7100FFA1E0(true);
    } else {
        if (bgm)
            bgm->sub_7100FFA1E0(false);
    }
}

}  // namespace uking::action
