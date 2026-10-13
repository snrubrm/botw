#include "Game/AI/Action/actionEventFadeOut.h"
#include "Game/UI/uiScreens.h"
#include "Game/gameScene.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

EventFadeOut::EventFadeOut(const InitArg& arg) : EventFade(arg) {}

EventFadeOut::~EventFadeOut() = default;

bool EventFadeOut::init_(sead::Heap* heap) {
    return EventFade::init_(heap);
}

void EventFadeOut::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_710011A710()) {
        setFinished();
        mFlags.set(Flag::Changeable);
    } else {
        EventFade::enter_(params);
        auto* screen = sub_7100119888();
        if (!screen->isOpened() && !screen->isOpening())
            screen->open(1);
    }
}

void EventFadeOut::leave_() {
    if (sub_710011A710())
        return;
    EventFade::leave_();
}

void EventFadeOut::loadParams_() {
    EventFade::loadParams_();
}

void EventFadeOut::calc_() {
    if (isFinished() || isFailed())
        return;
    EventFade::calc_();
    auto* screen = sub_7100119888();
    if (screen->isOpened()) {
        setFinished();
        mFlags.set(Flag::Changeable);
    } else if (!screen->isOpening()) {
        if (getSceneStatus() != 4) {
            sead::FixedSafeString<128> flow;
            sead::FixedSafeString<128> entry;
            getActiveEventFlowPath_0(mActor, &flow, &entry);
            sead::FixedSafeString<128> path;
            getActiveEventFlowPath(mActor, &path);
        }
        setFailed();
        mFlags.set(Flag::Changeable);
    }
}

}  // namespace uking::action
