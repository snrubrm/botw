#include "Game/AI/Action/actionPlayerMagnetSubject.h"
#include "Game/gameSceneSubsysMisc.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerMagnetSubject::PlayerMagnetSubject(const InitArg& arg) : PlayerAction(arg) {}

void PlayerMagnetSubject::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x400000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x20);
    sub_71007FEE10();
    static_cast<ksys::act::Player*>(mActor)->x_23("ItemMagneCatchStart", false, -1.0f);
    f32 energy = 0.0f;
    if (auto* scene = GameSceneSubsys5::instance())
        energy = scene->sub_7100905D18();
    static_cast<ksys::act::Player*>(mActor)->_20f4 = energy;
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    static_cast<ksys::act::Player*>(mActor)->_17f1 = false;
    static_cast<ksys::act::Player*>(mActor)->_17f2 = false;
    static_cast<ksys::act::Player*>(mActor)->_1800 = 0.0f;
    static_cast<ksys::act::Player*>(mActor)->_1804 = 0.0f;
    static_cast<ksys::act::Player*>(mActor)->_1808 = 0.0f;
    static_cast<ksys::act::Player*>(mActor)->_180c = 0.0f;
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
