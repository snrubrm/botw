#include "Game/AI/AI/aiGiantSleepReaction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

GiantSleepReaction::GiantSleepReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GiantSleepReaction::~GiantSleepReaction() = default;

bool GiantSleepReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GiantSleepReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = false;
    changeChild("睡眠");
}

void GiantSleepReaction::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!_38 && isCurrentChild("音反応"))
            changeChild("睡眠");
        else
            setFinished();
    } else {
        child->isChangeable();
    }

    if (!isCurrentChild("睡眠"))
        return;
    if (_38) {
        setFinished();
        return;
    }

    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return;
    auto* sensor = awareness->_260[1];
    if (!sensor || !sensor->_8.isBufferReady() || sensor->_8.size() < 1)
        return;
    if (ksys::act::sub_7100D78E30(&sensor->_8, 0)->_a0 != 0)
        changeChild("音反応");
}

void GiantSleepReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantSleepReaction::loadParams_() {}

bool GiantSleepReaction::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000015)
        _38 = false;
    else if (message->getType() == 0x3000016)
        _38 = true;
    return false;
}

}  // namespace uking::ai
