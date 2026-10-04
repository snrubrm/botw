#include "Game/AI/Action/actionPlayerMagnetSubject.h"
#include "Game/gameSceneSubsysMisc.h"

namespace uking::action {

PlayerMagnetSubject::PlayerMagnetSubject(const InitArg& arg) : PlayerAction(arg) {}

void PlayerMagnetSubject::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerMagnetSubject::leave_() {
    PlayerAction::leave_();
}

void PlayerMagnetSubject::loadParams_() {
    getStaticParam(&mDRCEnergy_s, "DRCEnergy");
}

void PlayerMagnetSubject::calc_() {
    PlayerAction::calc_();
}

bool PlayerMagnetSubject::isChangeable() const {
    return false;
}

bool PlayerMagnetSubject::isFailed() const {
    if (auto* scene = GameSceneSubsys5::instance()) {
        if (scene->sub_7100905B34())
            return true;
    }
    return false;
}

}  // namespace uking::action
