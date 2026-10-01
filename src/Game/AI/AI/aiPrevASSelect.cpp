#include "Game/AI/AI/aiPrevASSelect.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PrevASSelect::PrevASSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PrevASSelect::~PrevASSelect() = default;

bool PrevASSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PrevASSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->getASList()->x_1(0, 0) == mASName_s)
        changeChild("該当", params);
    else
        changeChild("非該当", params);
}

void PrevASSelect::calc_() {}

void PrevASSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PrevASSelect::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::ai
