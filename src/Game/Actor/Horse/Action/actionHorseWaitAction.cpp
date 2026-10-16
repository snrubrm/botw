#include "Game/Actor/Horse/Action/actionHorseWaitAction.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseWaitAction::HorseWaitAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseWaitAction::~HorseWaitAction() = default;

bool HorseWaitAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the native retains the masked finished flag in the early-return path.
bool HorseWaitAction::isFinished() const {
    if (act::sUnk_7102603110 == mActor->getASList()->x_1(0, 0) &&
        !ksys::act::ai::Action::isFinished())
        return isFinishedAS(0, 0);
    return ksys::act::ai::Action::isFinished();
}

// NON_MATCHING: the original keeps the gear byte in a stack temporary (stored and reloaded, as for an enum
// wrapper object) and the courbette gear in another; branch order.
void HorseWaitAction::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* rideable = mActor->m132();
    if (!rideable) {
        setFailed();
        return;
    }

    auto& request = rideable->_18;
    request.sub_7100E787A0();
    const f32 frames = *mSmoothStopFrames_s;
    if (frames <= 0.0f) {
        if (*mIsLight_s)
            request.sub_7100E76E74(act::sUnk_7102603350, false);
        else
            rideable->sub_7100E63224(u32(*mUseGearType_s), 0);
    } else {
        const u8 gear = request._b;
        switch (gear) {
        case 3:
        case 4:
            if (*mSmoothStopFramesGear3_s > 0.0f) {
                rideable->sub_7100E63224(u32(*mUseGearType_s), 3);
                _50 = *mSmoothStopFramesGear3_s;
                _54 = 0;
                _58 = false;
                return;
            }
            rideable->sub_7100E63224(u32(*mUseGearType_s), 2);
            break;
        case 2:
            rideable->sub_7100E63224(u32(*mUseGearType_s), 1);
            break;
        case 1:
        idle:
            if (*mIsLight_s)
                request.sub_7100E76E74(act::sUnk_7102603350, false);
            else
                rideable->sub_7100E63224(u32(*mUseGearType_s), 0);
            break;
        default:
            if (!*mIsCourbetteEnabled_s || (gear == 0 ? request._9 : request._b) < 3)
                goto idle;
            request.sub_7100E76E74(act::sUnk_7102603180, false);
            break;
        }
        _50 = frames;
    }
    _54 = 0;
    _58 = false;
}

void HorseWaitAction::leave_() {
    if (auto* nav = mActor->m45())
        nav->sub_7100F76314();
}

void HorseWaitAction::loadParams_() {
    getStaticParam(&mUseGearType_s, "UseGearType");
    getStaticParam(&mSmoothStopFrames_s, "SmoothStopFrames");
    getStaticParam(&mSmoothStopFramesGear3_s, "SmoothStopFramesGear3");
    getStaticParam(&mMinFramesGear1_s, "MinFramesGear1");
    getStaticParam(&mIsCourbetteEnabled_s, "IsCourbetteEnabled");
    getStaticParam(&mIsLight_s, "IsLight");
}

void HorseWaitAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
