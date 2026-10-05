#include "Game/AI/Action/actionSetOpenState.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::action {

SetOpenState::SetOpenState(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetOpenState::~SetOpenState() = default;

bool SetOpenState::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetOpenState::loadParams_() {
    getAITreeVariable(&mIsOpenTreasureBox_a, "IsOpenTreasureBox");
}

bool SetOpenState::oneShot_() {
    auto* actor = mActor;
    if (!actor || !ksys::act::hasTag(actor, ksys::act::tags::TreasureBox))
        return false;
    auto* object = actor->getMapObject();
    actor->emitBasicSigOn();
    actor->setRevivalFlagForUsed(true);
    if (object) {
        object->setRevivalFlagValueIf(ksys::map::ActorData::Flag::RevivalEnable, true);
        ui::uiManagerUpdateIsDungeon();
    }
    *mIsOpenTreasureBox_a = true;
    return true;
}

}  // namespace uking::action
