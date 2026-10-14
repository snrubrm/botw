#include "Game/Actor/AI/aiHorseRiddenStatusSelector.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

HorseRiddenStatusSelector::HorseRiddenStatusSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRiddenStatusSelector::~HorseRiddenStatusSelector() = default;

bool HorseRiddenStatusSelector::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool HorseRiddenStatusSelector::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool HorseRiddenStatusSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRiddenStatusSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710043EABC(params);
}

void HorseRiddenStatusSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRiddenStatusSelector::loadParams_() {}

void HorseRiddenStatusSelector::sub_710043EABC(ksys::act::ai::InlineParamPack* params) {
    if (auto* info = mActor->getMotorcyclePriorityStuffMaybe()) {
        const uking::act::Unk_7100e8b2b8::Unk8 type(info->_8.load() & 0xff);
        switch (type) {
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

void HorseRiddenStatusSelector::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        return;
    if (child->isChangeable())
        sub_710043EABC(nullptr);
}

}  // namespace uking::ai
