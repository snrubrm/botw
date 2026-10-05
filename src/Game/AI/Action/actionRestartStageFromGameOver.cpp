#include "Game/AI/Action/actionRestartStageFromGameOver.h"
#include "Game/UI/uiUtils.h"

// 0x71007af558: source namespace unknown; only the bool interface is established.
bool sub_71007AF558();

namespace uking::action {

RestartStageFromGameOver::RestartStageFromGameOver(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RestartStageFromGameOver::~RestartStageFromGameOver() = default;

bool RestartStageFromGameOver::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RestartStageFromGameOver::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RestartStageFromGameOver::leave_() {
    ksys::act::ai::Action::leave_();
}

void RestartStageFromGameOver::loadParams_() {}

void RestartStageFromGameOver::calc_() {
    if (!isFinished() && !isFailed() && sub_71007AF558() && ui::sub_7100A96688()) {
        setFinished();
        mFlags.set(Flag::Changeable);
    }
}

}  // namespace uking::action
