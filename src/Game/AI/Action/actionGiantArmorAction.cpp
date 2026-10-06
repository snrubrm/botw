#include "Game/AI/Action/actionGiantArmorAction.h"

namespace uking::action {

GiantArmorAction::GiantArmorAction(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

GiantArmorAction::~GiantArmorAction() = default;

bool GiantArmorAction::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void GiantArmorAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    _68 = 0;
    if (mStartAS_s.isEmpty())
        playAS(mLoopAS_s.cstr(), false, 0, 0, -1.0f);
    else
        playAS(mStartAS_s.cstr(), false, 0, 0, -1.0f);
}

void GiantArmorAction::leave_() {
    ActionWithPosAngReduce::leave_();
}

void GiantArmorAction::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mUseRestart_s, "UseRestart");
    getStaticParam(&mStartAS_s, "StartAS");
    getStaticParam(&mLoopAS_s, "LoopAS");
    getStaticParam(&mEndAS_s, "EndAS");
}

void GiantArmorAction::calc_() {
    ActionWithPosAngReduce::calc_();
    switch (_68) {
    case 0:
        if (mStartAS_s.isEmpty()) {
            _68 = 1;
        } else if (isFinishedAS(0, 0)) {
            _68 = 1;
            playAS(mLoopAS_s.cstr(), false, 0, 0, -1.0f);
        }
        break;
    case 1:
        if (!m32() || isFinishedAS(0, 0)) {
            _68 = 2;
            playAS(mEndAS_s.cstr(), false, 0, 0, -1.0f);
        }
        break;
    case 2:
        if (*mUseRestart_s && m32()) {
            _68 = 0;
            if (!mStartAS_s.isEmpty())
                playAS(mStartAS_s.cstr(), false, 0, 0, -1.0f);
            else
                playAS(mLoopAS_s.cstr(), false, 0, 0, -1.0f);
        } else if (isFinishedAS(0, 0)) {
            setFinished();
        }
        break;
    default:
        setFailed();
        break;
    }
}

}  // namespace uking::action
