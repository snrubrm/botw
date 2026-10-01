#include "Game/AI/AI/aiDrawnSwordBowSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

DrawnSwordBowSelect::DrawnSwordBowSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DrawnSwordBowSelect::~DrawnSwordBowSelect() = default;

bool DrawnSwordBowSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DrawnSwordBowSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    const int close_idx = *mCloseWeaponIdx_s;
    if (sub_71005D83E8(mActor, close_idx) && sub_71005DB904(mActor, close_idx)) {
        changeChild("抜刀", params);
        return;
    }
    const int bow_idx = *mBowWeaponIdx_s;
    if (sub_71005D83E8(mActor, bow_idx) && sub_71005DB904(mActor, bow_idx))
        changeChild("抜弓", params);
    else
        changeChild("素手", params);
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

// NON_MATCHING: the child vtable load is not hoisted above the isFinished/isFailed branches
void DrawnSwordBowSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFailed()) {
            setFailed();
            return;
        }

        // 0: sword, 1: bow, 2: no weapon
        int state;
        const int close_idx = *mCloseWeaponIdx_s;
        if (sub_71005D83E8(mActor, close_idx) && sub_71005DB904(mActor, close_idx)) {
            state = 0;
        } else {
            const int bow_idx = *mBowWeaponIdx_s;
            if (sub_71005D83E8(mActor, bow_idx) && sub_71005DB904(mActor, bow_idx))
                state = 1;
            else
                state = 2;
        }
        int current;
        if (isCurrentChild("抜刀"))
            current = 0;
        else if (isCurrentChild("抜弓"))
            current = 1;
        else
            current = 2;

        if (state == current) {
            setFinished();
            return;
        }
        switch (state) {
        case 0:
            changeChild("抜刀");
            break;
        case 1:
            changeChild("抜弓");
            break;
        case 2:
            changeChild("素手");
            break;
        default:
            setFailed();
            break;
        }
    } else if (child->isChangeable()) {
        int state;
        const int close_idx = *mCloseWeaponIdx_s;
        if (sub_71005D83E8(mActor, close_idx) && sub_71005DB904(mActor, close_idx)) {
            state = 0;
        } else {
            const int bow_idx = *mBowWeaponIdx_s;
            if (sub_71005D83E8(mActor, bow_idx) && sub_71005DB904(mActor, bow_idx))
                state = 1;
            else
                state = 2;
        }
        int current;
        if (isCurrentChild("抜刀"))
            current = 0;
        else if (isCurrentChild("抜弓"))
            current = 1;
        else
            current = 2;

        if (state == current)
            return;
        switch (state) {
        case 0:
            changeChild("抜刀");
            break;
        case 1:
            changeChild("抜弓");
            break;
        case 2:
            changeChild("素手");
            break;
        }
    }
}

bool DrawnSwordBowSelect::sub_7100373648() const {
    bool ok;
    if (isCurrentChild("抜刀")) {
        const int idx = *mCloseWeaponIdx_s;
        ok = sub_71005D83E8(mActor, idx) && sub_71005DB904(mActor, idx);
    } else if (isCurrentChild("抜弓")) {
        const int idx = *mBowWeaponIdx_s;
        ok = sub_71005D83E8(mActor, idx) && sub_71005DB904(mActor, idx);
    } else {
        const int close_idx = *mCloseWeaponIdx_s;
        if (sub_71005D83E8(mActor, close_idx) && sub_71005DB904(mActor, close_idx)) {
            ok = false;
        } else {
            const int bow_idx = *mBowWeaponIdx_s;
            ok = !(sub_71005D83E8(mActor, bow_idx) && sub_71005DB904(mActor, bow_idx));
        }
    }
    return !ok;
}

}  // namespace uking::ai
