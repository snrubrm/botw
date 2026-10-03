#include "KingSystem/Event/evtActionContext.h"

namespace ksys::evt {

// 0x7100da546c
void ActionContext::setStatus2() {
    mStatus = 2;
}

// 0x7100da5478
void ActionContext::setStatus1() {
    mStatus = 1;
}

// 0x7100da5484
void ActionContext::setStatus1_0() {
    mStatus = 1;
}

// 0x7100da56b8
void ActionContext::reset() {
    mStatus = 0;
    _af4 = 0;
}

// 0x7100da5678
void ActionContext::x_0() {
    _a50 = 0;
}

// 0x7100da5708
void ActionContext::statusStuff_2() {
    const s32 status = mStatus;
    mStatus = status == 3 ? 7 : (status == 4 ? 8 : 0);
}

// 0x7100da5680
void ActionContext::x_1() {
    switch (mStatus) {
    case 1:
        mStatus = 3;
        break;
    case 2:
        mStatus = 4;
        break;
    default:
        mStatus = 0;
        _af4 = 0;
        break;
    }
}

// 0x7100da5490
bool ActionContext::statusStuff() {
    switch (mStatus) {
    case 2:
        mStatus = 1;
        return true;
    case 4:
        mStatus = 3;
        return true;
    case 6:
    case 8:
        return true;
    default:
        return false;
    }
}

// 0x7100da54e0
bool ActionContext::statusStuff_0() {
    switch (mStatus) {
    case 2:
        mStatus = 1;
        return true;
    case 4:
        mStatus = 3;
        return true;
    case 6:
    case 8:
        mStatus = 0;
        return true;
    default:
        return false;
    }
}

// 0x7100da56c4
void ActionContext::statusStuff_1() {
    switch (mStatus) {
    case 0:
    case 5:
        break;
    case 3:
        mStatus = 5;
        break;
    case 4:
        mStatus = 6;
        break;
    default:
        mStatus = 0;
        _af4 = 0;
        break;
    }
}

}  // namespace ksys::evt
