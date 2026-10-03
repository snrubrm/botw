#include "Game/AI/AI/aiGanonBeastStairState.h"
#include "Game/AI/aiUnk_710070284C.h"

namespace uking::ai {

GanonBeastStairState::GanonBeastStairState(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBeastStairState::~GanonBeastStairState() = default;

bool GanonBeastStairState::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBeastStairState::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = sub_710070284C(mActor);
    switch (_38) {
    case 0:
        changeChild("段階１", params);
        break;
    case 1:
        changeChild("段階２", params);
        break;
    case 2:
        changeChild("段階３", params);
        break;
    case 3:
        changeChild("段階４", params);
        break;
    default:
        changeChild("段階１", params);
        break;
    }
}

void GanonBeastStairState::calc_() {
    const int stage = sub_710070284C(mActor);
    if (stage != _38) {
        _38 = stage;
        switch (stage) {
        case 0:
            if (!isCurrentChild("段階１"))
                changeChild("段階１");
            break;
        case 1:
            if (!isCurrentChild("段階２"))
                changeChild("段階２");
            break;
        case 2:
            if (!isCurrentChild("段階３"))
                changeChild("段階３");
            break;
        case 3:
            if (!isCurrentChild("段階４"))
                changeChild("段階４");
            break;
        default:
            if (!isCurrentChild("段階１"))
                changeChild("段階１");
            break;
        }
    }
    _38 = sub_710070284C(mActor);
}

void GanonBeastStairState::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBeastStairState::loadParams_() {}

}  // namespace uking::ai
