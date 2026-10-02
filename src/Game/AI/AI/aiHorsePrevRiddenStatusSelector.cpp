#include "Game/AI/AI/aiHorsePrevRiddenStatusSelector.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

HorsePrevRiddenStatusSelector::HorsePrevRiddenStatusSelector(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

HorsePrevRiddenStatusSelector::~HorsePrevRiddenStatusSelector() = default;

bool HorsePrevRiddenStatusSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorsePrevRiddenStatusSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710043C1D4(params);
}

void HorsePrevRiddenStatusSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorsePrevRiddenStatusSelector::loadParams_() {}

void HorsePrevRiddenStatusSelector::sub_710043C1D4(ksys::act::ai::InlineParamPack* params) {
    if (auto* rideable = mActor->getHorseOptionsMaybe()) {
        const uking::act::Unk_7100e8b2b8::Unk8 status = rideable->Unk_7100e8b2b8::_c.load();
        switch (status) {
        case uking::act::Unk_7100e8b2b8::Unk8::_1:
            if (!isCurrentChild("プレイヤー騎乗"))
                changeChild("プレイヤー騎乗", params);
            return;
        case uking::act::Unk_7100e8b2b8::Unk8::_2:
            if (!isCurrentChild("敵騎乗"))
                changeChild("敵騎乗", params);
            return;
        case uking::act::Unk_7100e8b2b8::Unk8::_3:
            if (!isCurrentChild("NPC騎乗"))
                changeChild("NPC騎乗", params);
            return;
        default:
            break;
        }
    }
    if (!isCurrentChild("騎乗無し"))
        changeChild("騎乗無し", params);
}

void HorsePrevRiddenStatusSelector::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        return;
    if (child->isChangeable())
        sub_710043C1D4(nullptr);
}

}  // namespace uking::ai
