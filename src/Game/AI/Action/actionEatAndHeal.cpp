#include "Game/AI/Action/actionEatAndHeal.h"
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectCureItem.h"

namespace uking::action {

EatAndHeal::EatAndHeal(const InitArg& arg) : AnimalEatAction(arg) {}

EatAndHeal::~EatAndHeal() = default;

bool EatAndHeal::init_(sead::Heap* heap) {
    return AnimalEatAction::init_(heap);
}

void EatAndHeal::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalEatAction::enter_(params);
}

void EatAndHeal::leave_() {
    AnimalEatAction::leave_();
}

void EatAndHeal::loadParams_() {
    AnimalEatAction::loadParams_();
}

void EatAndHeal::calc_() {
    AnimalEatAction::calc_();
}

// NON_MATCHING: the original keeps the timer index in a register across sub_71002F2E78 and converts it
// in a stack slot above the accessor (as if from an inlined WolfLink helper)
int EatAndHeal::m32() {
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(mTargetActor_d, &accessor))
        return 0;

    const auto* cure_item = accessor.getGParamList()->getCureItem();
    if (!cure_item)
        return 0;

    auto* actor = mActor;
    const s32 hp = cure_item->mHitPointRecover.ref();
    if (auto* life = actor->getLife()) {
        const s32 max_life = actor->getMaxLife();
        *life += hp;
        if (*life > max_life)
            *life = max_life;
        else if (*life < 0)
            *life = 0;
    }

    auto* wolf = sead::DynamicCast<act::WolfLink>(mActor);
    if (!wolf)
        return 0;

    if (wolf->_1698 & 0x400) {
        wolf->_1698 &= ~0x400;
        wolf->_1698 |= 0x800;
        wolf->_1698 |= 0x1000;
        const act::WolfLink::Idx14f8 idx = act::WolfLink::Idx14f8::_17;
        wolf->sub_71002F2E78(idx);
        wolf->_14f8[idx].rate = -1.0f;
    }
    return 1;
}

}  // namespace uking::action
