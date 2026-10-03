#include "Game/AI/AI/aiMiniGolemLifted.h"
#include "Game/AI/aiUnk_7102450410.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

MiniGolemLifted::MiniGolemLifted(const InitArg& arg) : EnemyLifted(arg) {}

MiniGolemLifted::~MiniGolemLifted() = default;

bool MiniGolemLifted::init_(sead::Heap* heap) {
    return EnemyLifted::init_(heap);
}

void MiniGolemLifted::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyLifted::enter_(params);
    if (auto* controller = sead::DynamicCast<Unk_7102450410>(
            *static_cast<Unk_71025afb58**>(mGolemChemicalController_a)))
        controller->_18.setBit(0);
    setDamageCallbackTiming(mActor, 4, &_78);
}

void MiniGolemLifted::calc_() {
    if (isFinished() || isFailed())
        return;

    if (isCurrentChild("落下")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            setFailed();
    } else if (isCurrentChild("所持")) {
        auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
        if (parent && !parent->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40))
            EnemyLifted::calc_();
        else
            changeChild("落下");
    } else {
        EnemyLifted::calc_();
    }
}

void MiniGolemLifted::leave_() {
    sub_71005DA114(mActor, &_78);
    if (auto* controller = sead::DynamicCast<Unk_7102450410>(
            *static_cast<Unk_71025afb58**>(mGolemChemicalController_a)))
        controller->_18.resetBit(0);
    EnemyLifted::leave_();
}

void MiniGolemLifted::m34() {
    changeChild("設置");
}

void MiniGolemLifted::loadParams_() {
    EnemyLifted::loadParams_();
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

}  // namespace uking::ai
