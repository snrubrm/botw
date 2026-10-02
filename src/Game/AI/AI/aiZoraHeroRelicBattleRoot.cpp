#include "Game/AI/AI/aiZoraHeroRelicBattleRoot.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

ZoraHeroRelicBattleRoot::ZoraHeroRelicBattleRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ZoraHeroRelicBattleRoot::~ZoraHeroRelicBattleRoot() = default;

bool ZoraHeroRelicBattleRoot::init_(sead::Heap* heap) {
    _48._8.sub_7100743814(mActor);
    return true;
}

void ZoraHeroRelicBattleRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ZoraHeroRelicBattleRoot::leave_() {
    auto* actor = mActor;
    if (auto* awareness = actor->getAwareness())
        awareness->disable();

    auto** unit = static_cast<Unk_71025afb58**>(mZoraHeroShowMsgUnit_a);
    if (unit && *unit == &_48)
        *unit = nullptr;

    if (auto* body = actor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), "HeadSensor"))
        body->removeFromWorld();
}

bool ZoraHeroRelicBattleRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType() == 0x180001a && isCurrentChild("騎乗待ち")) {
        _41 = true;
        _48._8.sub_7100744200(3, false);
        return true;
    }
    return false;
}

void ZoraHeroRelicBattleRoot::loadParams_() {
    getAITreeVariable(&mZoraHeroShowMsgUnit_a, "ZoraHeroShowMsgUnit");
}

}  // namespace uking::ai
