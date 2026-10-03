#include "Game/AI/Action/actionHorseReturnToSafePos.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseReturnToSafePos::HorseReturnToSafePos(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseReturnToSafePos::~HorseReturnToSafePos() = default;

bool HorseReturnToSafePos::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseReturnToSafePos::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mASName_s.isEmpty()) {
        if (auto* rideable = mActor->getHorseOptionsMaybe()) {
            rideable->_18.sub_7100E76E74(mASName_s, false);
            rideable->sub_7100E8BE10();
            rideable->Unk_7100e8b2b8::_8 = 0x200;
        }
    }
    _40 = -1.0f;
    _44 = true;
}

void HorseReturnToSafePos::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseReturnToSafePos::loadParams_() {
    getStaticParam(&mStartFadeOutFrame_s, "StartFadeOutFrame");
    getStaticParam(&mHiddenFrames_s, "HiddenFrames");
    getStaticParam(&mASName_s, "ASName");
}

void HorseReturnToSafePos::calc_() {
    ksys::act::ai::Action::calc_();
}

bool HorseReturnToSafePos::handleMessage_(const ksys::Message& message) {
    if (message.getType() != 0x3000010)
        return false;
    _40 = 0;
    return true;
}

}  // namespace uking::action
