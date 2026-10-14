#include "Game/Actor/Action/actionEventPickOutFromPorch.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_7101e7c5d0.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

// Existing CSV utility name; source namespace is unknown.
bool aiActionEventPickOutFromPorch(ksys::act::BaseProcHandle* handle);

namespace uking::action {

EventPickOutFromPorch::EventPickOutFromPorch(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPickOutFromPorch::~EventPickOutFromPorch() = default;

bool EventPickOutFromPorch::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: scheduling of the two GOT float loads around the item value load.
// Creates the actor of the last item added to the inventory (taken back out of the pouch).
void EventPickOutFromPorch::enter_(ksys::act::ai::InlineParamPack* params) {
    const auto* item = ui::PauseMenuDataMgr::instance()->getLastAddedItem();
    if (!item->isInInventory()) {
        setFailed();
        return;
    }

    act::WeaponModifierInfo modifier(*item);
    sead::FixedSafeString<64> name;
    if (item->getType() == ui::PouchItemType::Arrow)
        name = item->getName();
    else
        ksys::act::getSameGroupActorName(&name, item->getName());

    if (*mIsUseCarryBox_d &&
        sub_710073CD5C(name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap()))
        setFinished();

    if (isFinished() || isFailed())
        return;
    createActorPickOutFromPorch(name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
                                item->getValue(), &modifier, &_30, sUnk_7101e7d6ec, sUnk_7101e7d6f0);
}

void EventPickOutFromPorch::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventPickOutFromPorch::loadParams_() {
    getStaticParam(&mPickOutItemType_s, "PickOutItemType");
    getDynamicParam(&mIsUseCarryBox_d, "IsUseCarryBox");
}

void EventPickOutFromPorch::calc_() {
    if (isFinished() || isFailed())
        return;
    if (_30.hasProcCreationFailed()) {
        setFailed();
        _30.deleteProcIfFailed();
    } else if (_30.isProcReady()) {
        if (aiActionEventPickOutFromPorch(&_30))
            setFinished();
        else
            setFailed();
    }
}

}  // namespace uking::action
