#include "Game/AI/AI/aiHorseDamageTypeSelect.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

HorseDamageTypeSelect::HorseDamageTypeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseDamageTypeSelect::~HorseDamageTypeSelect() = default;

bool HorseDamageTypeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseDamageTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->getDamageMgr()->getField54() == 0) {
        changeChild("継続ダメージ");
        auto* child = getCurrentChild();
        if (!child->isFinished() && !child->isFailed())
            return;
    }
    changeChild("その他");
}

void HorseDamageTypeSelect::calc_() {
    if (getCurrentChild()->isFinished())
        setFinished();
    else if (getCurrentChild()->isFailed())
        setFailed();
}

void HorseDamageTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseDamageTypeSelect::loadParams_() {}

bool HorseDamageTypeSelect::isFinished() const {
    auto* child = getCurrentChild();
    if (ActionBase::isFinished())
        return true;
    return child && child->isFinished();
}

bool HorseDamageTypeSelect::isFailed() const {
    auto* child = getCurrentChild();
    if (ActionBase::isFailed())
        return true;
    return child && child->isFailed();
}

}  // namespace uking::ai
