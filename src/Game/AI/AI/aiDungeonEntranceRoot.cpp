#include "Game/AI/AI/aiDungeonEntranceRoot.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::ai {

DungeonEntranceRoot::DungeonEntranceRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonEntranceRoot::~DungeonEntranceRoot() = default;

bool DungeonEntranceRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonEntranceRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* object = actor->getMapObject()) {
        if (auto* lod = object->findPlacementLODLinkObject(nullptr)) {
            if (lod->getActorData().mFlags.isOnBit(ksys::map::ActorData::Flag::RevivalForUsed) &&
                !lod->checkRevivalFlag(ksys::map::ActorData::Flag::RevivalForUsed))
                actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
        }
    }
    bool check_sig = true;
    if (*mIsCheckClear_s) {
        sead::Vector3f position;
        actor->getMtx().getTranslation(position);
        sead::SafeString name;
        if (!ui::findDungeonNameForPositionImpl(5.0f, &name, &position)) {
            check_sig = false;
        } else if (ksys::gdt::isDungeonCleared(name, false)) {
            changeChild("クリア");
            check_sig = false;
        }
    }
    if (check_sig) {
        if (actor->checkBasicSig())
            changeChild("オープン");
        else
            changeChild("クローズ");
    }
    if (auto* body = actor->findPhysicsBodyByName(sub_71007A250C()->cstr(), "EntitySensorBody"))
        body->addToWorld();
}

void DungeonEntranceRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonEntranceRoot::loadParams_() {
    getStaticParam(&mIsCheckClear_s, "IsCheckClear");
}

// NON_MATCHING: the original loads mActor before the isCurrentChild call (see log: single-use `auto* actor` local)
void DungeonEntranceRoot::calc_() {
    if (isCurrentChild("クローズ") && mActor->checkBasicSig())
        changeChild("オープン");
}

}  // namespace uking::ai
