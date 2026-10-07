#include "Game/AI/AI/aiSeqTimeredTwoAction.h"

namespace uking::ai {

SeqTimeredTwoAction::SeqTimeredTwoAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool SeqTimeredTwoAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqTimeredTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = m34() > 0;
    const f32 first_time = m34();
    _50 = ksys::Timer(first_time, first_time);
    const f32 all_time = m36();
    _5c = ksys::Timer(all_time, all_time);
    changeChild("先行動", params);
}

void SeqTimeredTwoAction::calc_() {
    _50.update();
    _5c.update();

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed()) {
        if (!child->isChangeable())
            return;
        if (m36() >= 1 && _5c.value <= sead::Mathf::epsilon()) {
            setFinished();
            return;
        }
        if (!_68 || !(_50.value <= sead::Mathf::epsilon()))
            return;
    }

    if (isCurrentChild("先行動")) {
        _68 = m35() > 0;
        const f32 second_time = m35();
        _50.value = second_time;
        _50.previous_value = second_time;
        changeChild("後行動");
    } else {
        setFinished();
    }
}

void SeqTimeredTwoAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqTimeredTwoAction::loadParams_() {
    getStaticParam(&mFirstActionTime_s, "FirstActionTime");
    getStaticParam(&mSecondActionTime_s, "SecondActionTime");
    getStaticParam(&mAllActionTime_s, "AllActionTime");
}

}  // namespace uking::ai
