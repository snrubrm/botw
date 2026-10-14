#include "Game/Actor/AI/aiSwarmStopTimerEscape.h"
#include "Game/Actor/aiUnk_710072A80C.h"
#include "Game/Actor/aiUnk_710072A944.h"
#include "Game/Actor/actSwarm.h"
#include "Game/gameStasisMgr.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/aiRootAi.h"

namespace uking::ai {

SwarmStopTimerEscape::SwarmStopTimerEscape(const InitArg& arg) : SwarmEscapeDie(arg) {}

SwarmStopTimerEscape::~SwarmStopTimerEscape() = default;

bool SwarmStopTimerEscape::init_(sead::Heap* heap) {
    return SwarmEscapeDie::init_(heap);
}

void SwarmStopTimerEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    SwarmEscapeDie::enter_(params);
    sub_710072A80C(mActor, &_80, nullptr);
}

void SwarmStopTimerEscape::calc_() {
    SwarmEscapeDie::calc_();
    if (!_80.isAllocatedOrFailed())
        return;

    if (_80.isProcReady())
        sub_71005B31CC();
    else if (_80.hasProcCreationFailed())
        _80.deleteProcIfFailed();
}

void SwarmStopTimerEscape::leave_() {
    if (_80.isAllocatedOrFailed())
        _80.deleteProc();
    SwarmEscapeDie::leave_();
}

void SwarmStopTimerEscape::loadParams_() {
    SwarmEscapeDie::loadParams_();
    getStaticParam(&mStopActorName_s, "StopActorName");
}

// NON_MATCHING: the key SafeString temporary is stored with two str instead of one stp (as in sub_7100731000,
// reversed)
// Places the stop actor at the swarm unit nearest to the swarm's centre (or at the actor) and enables
// its stop timer.
void SwarmStopTimerEscape::sub_71005B31CC() {
    auto* actor = sead::DynamicCast<ksys::act::Actor>(_80.releaseAndWakeProc());
    if (!actor)
        return;

    if (auto* swarm = sead::DynamicCast<act::Swarm>(mActor)) {
        sead::Vector3f pos = sead::Vector3f::zero;
        sead::Matrix33f rot = sead::Matrix33f::ident;
        for (s32 i = 0; i < swarm->_14c8.size(); ++i) {
            if (auto* unit = swarm->_14c8[i])
                pos += unit->_8.getTranslation();
        }
        pos *= 1.0f / static_cast<f32>(swarm->_14c8.size());
        if (auto* unit = sub_710072A6DC(swarm, pos)) {
            unit->m10();
            unit->_8.getTranslation(pos);
            rot = sead::Matrix33f(unit->_8);
        }
        actor->sub_71011C7020(&pos, &rot, nullptr);
    } else {
        actor->setMatrix(mActor->getMtx(), nullptr);
    }

    if (auto* root = actor->getRootAi())
        root->getAiTreeParams().setAITreeVariable("EnableStopTimerOnSleep", ksys::AIDefParamType::Bool, true);

    if (auto* sender = ksys::act::ActorSystem::instance()->getStasisMessageSender())
        sender->sendMessage(actor, ksys::MessageType(0x3000003), false);
}

}  // namespace uking::ai
