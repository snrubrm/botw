#include "Game/AI/AI/aiDrawnSwordBowSelect.h"

namespace uking::ai {

DrawnSwordBowSelect::DrawnSwordBowSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DrawnSwordBowSelect::~DrawnSwordBowSelect() = default;

bool DrawnSwordBowSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DrawnSwordBowSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DrawnSwordBowSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DrawnSwordBowSelect::loadParams_() {
    getStaticParam(&mCloseWeaponIdx_s, "CloseWeaponIdx");
    getStaticParam(&mBowWeaponIdx_s, "BowWeaponIdx");
}

bool DrawnSwordBowSelect::isFinished() const {
    return mFlags.isOn(Flag::Finished) || (getCurrentChild()->isFinished() && !sub_7100373648());
}

bool DrawnSwordBowSelect::isFailed() const {
    return mFlags.isOn(Flag::Failed) || (getCurrentChild()->isFailed() && !sub_7100373648());
}

}  // namespace uking::ai
