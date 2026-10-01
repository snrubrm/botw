#include "Game/AI/Action/actionSetTreasureBoxOpenAndClose.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SetTreasureBoxOpenAndClose::SetTreasureBoxOpenAndClose(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetTreasureBoxOpenAndClose::~SetTreasureBoxOpenAndClose() = default;

bool SetTreasureBoxOpenAndClose::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetTreasureBoxOpenAndClose::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 set_open = *mIsSetOpen_d;
    const bool is_open = *mIsOpenTreasureBox_a;
    if (set_open != 0) {
        if (is_open) {
            mActor->emitBasicSigOff();
            *mIsOpenTreasureBox_a = false;
            playAS("Close", true, 0, 0, -1.0f);
        } else {
            setFinished();
        }
    } else {
        if (!is_open) {
            *mIsOpenTreasureBox_a = true;
            playAS("Open", true, 0, 0, -1.0f);
        } else {
            setFinished();
        }
    }
    mFlags.set(Flag::Changeable);
}

void SetTreasureBoxOpenAndClose::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetTreasureBoxOpenAndClose::loadParams_() {
    getDynamicParam(&mIsSetOpen_d, "IsSetOpen");
    getAITreeVariable(&mIsOpenTreasureBox_a, "IsOpenTreasureBox");
}

void SetTreasureBoxOpenAndClose::calc_() {
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
