#include "Game/AI/Behavior/behaviorSetStaticSystemGroupHandler.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace uking::behavior {

SetStaticSystemGroupHandler::SetStaticSystemGroupHandler(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetStaticSystemGroupHandler::~SetStaticSystemGroupHandler() = default;

bool SetStaticSystemGroupHandler::m6(sead::Heap* heap) {
    return true;
}

void SetStaticSystemGroupHandler::m7() {}

void SetStaticSystemGroupHandler::loadParams() {
    getStaticParam(&mType_s, "Type");
    getStaticParam(&mOnLeaveReset_s, "OnLeaveReset");
}

void SetStaticSystemGroupHandler::m8() {
    if (*mType_s != 1)
        return;
    auto* handler = ksys::phys::System::instance()->sub_7101216894(
        ksys::phys::ContactLayerType::Entity, 2);
    if (handler) {
        if (auto* physics = mActor->getPhysics())
            physics->sub_7100FBDFA4(handler);
    }
}

void SetStaticSystemGroupHandler::m9() {
    if (!*mOnLeaveReset_s)
        return;
    auto* physics = mActor->getPhysics();
    if (!physics)
        return;
    physics->sub_7100FBDFA4(physics->get178(0));
    physics->sub_7100FBDFA4(physics->get178(1));
}

}  // namespace uking::behavior
