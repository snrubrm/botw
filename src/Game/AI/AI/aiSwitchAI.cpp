#include "Game/AI/AI/aiSwitchAI.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SwitchAI::SwitchAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwitchAI::~SwitchAI() = default;

bool SwitchAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwitchAI::enter_(ksys::act::ai::InlineParamPack* params) {
    if (m34())
        m41();
    else
        m40();
}

void SwitchAI::calc_() {
    getCurrentChild();
    if (m35())
        m43();
    else if (m36())
        m42();
    else if (m38())
        m40();
    else if (m37())
        m41();
    else
        m39();
}

void SwitchAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwitchAI::loadParams_() {}

bool SwitchAI::m34() {
    return mActor->checkLinkBasicSig();
}

void SwitchAI::m40() {
    changeChild("オフ待機");
}

void SwitchAI::m41() {
    changeChild("オン待機");
}

void SwitchAI::m42() {
    changeChild("オフ");
}

void SwitchAI::m43() {
    changeChild("オン");
}

}  // namespace uking::ai
