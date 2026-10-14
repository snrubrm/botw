#include "Game/Actor/Action/actionHorseReturnToSafePos.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "Game/Actor/actHorse.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/Timer.h"

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
    if (auto* options = mActor->getHorseOptionsMaybe()) {
        options->_18.sub_7100E770C4(false);
        options->sub_7100E8BD80();
        options->Unk_7100e8b2b8::_8 &= ~0x200u;
    }
    if (auto* horse = sead::DynamicCast<act::Horse>(mActor))
        horse->_11a8.resetBit(act::Horse::Flag(act::Horse::Flag::_3));
}

void HorseReturnToSafePos::loadParams_() {
    getStaticParam(&mStartFadeOutFrame_s, "StartFadeOutFrame");
    getStaticParam(&mHiddenFrames_s, "HiddenFrames");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: operand order of the orr in `_11a8.setBit(3)` (bits | mask in the original).
// Fades the horse out once the AS reaches StartFadeOutFrame (negative: counted back from the end), keeps it hidden
// for HiddenFrames after the warp message (_40 = 0) and finishes when it is shown again.
void HorseReturnToSafePos::calc_() {
    auto* rideable = mActor->getHorseOptionsMaybe();
    auto* horse = sead::DynamicCast<act::Horse>(mActor);
    if (!horse) {
        setFailed();
    } else {
        const f32 prev = _40;
        if (prev < 0.0f) {
            bool start;
            if (mASName_s.isEmpty()) {
                start = true;
            } else if (_44) {
                start = false;
            } else {
                const f32 fade_out_frame = *mStartFadeOutFrame_s;
                const f32 frame = mActor->getASList()->x_5(
                    0, 0, &ksys::as::ASList::Unk2::sub_71011632F8);
                if (fade_out_frame >= 0.0f) {
                    start = frame >= *mStartFadeOutFrame_s || mActor->getASList()->x_4(0, 0);
                } else {
                    const f32 end = mActor->getASList()->x_5(
                        0, 0, &ksys::as::ASList::Unk2::sub_710116323C);
                    start = frame >= end + *mStartFadeOutFrame_s;
                }
            }
            if (start)
                horse->sub_7100E6B4A8();
        } else {
            if (prev == 0.0f) {
                rideable->_18.sub_7100E770C4(false);
                horse->_11a8.setBit(act::Horse::Flag(act::Horse::Flag::_3));
            }
            ksys::Timer::update(&_40, 1.0f);
            const f32 hidden_frames = *mHiddenFrames_s;
            if (prev < hidden_frames && hidden_frames <= _40) {
                horse->sub_7100E6BA08();
                horse->_11a8.resetBit(act::Horse::Flag(act::Horse::Flag::_3));
                horse->sub_7100E6B764();
                rideable->sub_7100E8BD80();
                rideable->Unk_7100e8b2b8::_8 &= ~0x200u;
                setFinished();
            }
        }
    }
    if (rideable) {
        if (auto* controller = mActor->getCharacterController())
            act::sub_7100E7F698(rideable, mActor->getASList(), controller);
    }
    _44 = false;
}

bool HorseReturnToSafePos::handleMessage_(const ksys::Message* message) {
    if (message->getType() != 0x3000010)
        return false;
    _40 = 0;
    return true;
}

}  // namespace uking::action
