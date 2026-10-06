#include "Game/AI/Action/actionDungeonEntranceASPlay.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DungeonEntranceASPlay::DungeonEntranceASPlay(const InitArg& arg) : NullASPlay(arg) {}

DungeonEntranceASPlay::~DungeonEntranceASPlay() = default;

bool DungeonEntranceASPlay::init_(sead::Heap* heap) {
    return NullASPlay::init_(heap);
}

void DungeonEntranceASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    sead::Vector3f position;
    actor->getMtx().getTranslation(position);
    sead::SafeString name;
    if (mSetDgnName_s.isEmpty()) {
        if (ui::findDungeonNameForPositionImpl(5.0f, &name, &position))
            actor->getASList()->goLimpFromHeadShotMaybe(0x40, name, 0);
    } else {
        actor->getASList()->goLimpFromHeadShotMaybe(0x40, mSetDgnName_s, 0);
    }
    NullASPlay::enter_(params);
}

void DungeonEntranceASPlay::leave_() {
    NullASPlay::leave_();
}

void DungeonEntranceASPlay::loadParams_() {
    NullASPlay::loadParams_();
    getStaticParam(&mSetDgnName_s, "SetDgnName");
}

void DungeonEntranceASPlay::calc_() {
    NullASPlay::calc_();
}

}  // namespace uking::action
