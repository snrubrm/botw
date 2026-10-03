#include "Game/AI/AI/aiDoorRoot.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

DoorRoot::DoorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DoorRoot::~DoorRoot() = default;

bool DoorRoot::init_(sead::Heap* heap) {
    *mIsOpenDoor_a = false;
    *mIsOpenToInside_a = false;
    return true;
}

void DoorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* awareness = mActor->getAwareness())
        awareness->enable();
    auto* actor = mActor;
    if (*mIsOpenDoor_a) {
        _e8 = ksys::Timer(*mCloseWaitFrame_s, *mCloseWaitFrame_s);
        actor->getPhysics()->sub_7100FC012C(nullptr);
    } else {
        actor->getPhysics()->sub_7100FC01B0();
        ksys::act::enableAttClient(actor, "Open");
    }
    changeChild("Wait");
}

void DoorRoot::leave_() {
    if (auto* awareness = mActor->getAwareness())
        awareness->disable();
}

void DoorRoot::loadParams_() {
    getStaticParam(&mCloseWaitFrame_s, "CloseWaitFrame");
    getStaticParam(&mIsCheckBack_s, "IsCheckBack");
    getStaticParam(&mOpen_L_AS_s, "Open_L_AS");
    getStaticParam(&mOpen_R_AS_s, "Open_R_AS");
    getStaticParam(&mClose_L_AS_s, "Close_L_AS");
    getStaticParam(&mClose_R_AS_s, "Close_R_AS");
    getMapUnitParam(&mNpcCanOpenFlag_m, "NpcCanOpenFlag");
    getAITreeVariable(&mIsOpenDoor_a, "IsOpenDoor");
    getAITreeVariable(&mIsOpenToInside_a, "IsOpenToInside");
}

bool DoorRoot::handleMessage_(const ksys::Message* message) {
    if (_a8._30)
        return false;
    if (isCurrentChild("Wait") && !*mIsOpenDoor_a)
        return _a8.m2(*message);
    return false;
}

}  // namespace uking::ai
