#include "Game/AI/AI/aiGyroActivateTerminal.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

GyroActivateTerminal::GyroActivateTerminal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GyroActivateTerminal::~GyroActivateTerminal() = default;

bool GyroActivateTerminal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GyroActivateTerminal::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _38.x();
    ksys::act::enableAttClient(actor, "BootPStop");
    _78 = false;
    changeChild("待機");
    _78 = false;
}

// NON_MATCHING: in the disable path the original computes `&_38` right after loading the actor
// (kept in a register across the sender reset); the enable path matches
void GyroActivateTerminal::calc_() {
    getCurrentChild();
    if (isCurrentChild("待機")) {
        if (!_38._30)
            return;
        auto* actor = mActor;
        _38.x();
        ksys::act::disableAttClient(actor, "BootPStop");
        _78 = false;
        changeChild("起動");
    } else {
        if (!isCurrentChild("起動"))
            return;
        const bool was_pressed = _78;
        bool pressed;
        {
            ksys::act::acc::PlayerBase player;
            player.getPlayerFromPlayerInfo();
            pressed = player.x_10();
        }
        if (!was_pressed) {
            if (pressed)
                _78 = true;
            return;
        }
        if (pressed)
            return;
        auto* actor = mActor;
        _38.x();
        ksys::act::enableAttClient(actor, "BootPStop");
        _78 = false;
        changeChild("待機");
    }
}

void GyroActivateTerminal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GyroActivateTerminal::loadParams_() {}

bool GyroActivateTerminal::handleMessage_(const ksys::Message& message) {
    if (isCurrentChild("待機") && _38.m2(message))
        return true;
    return false;
}

}  // namespace uking::ai
