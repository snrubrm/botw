#include "Game/Actor/Behavior/behaviorElevatorBaseEmitPassingSe.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::behavior {

// 0x71024358f0 (placeholder name): nothing in this file writes it; the original loads it without the GOT.
KSYS_VISIBILITY_HIDDEN bool sUnk_71024358F0 = true;

ElevatorBaseEmitPassingSe::ElevatorBaseEmitPassingSe(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

ElevatorBaseEmitPassingSe::~ElevatorBaseEmitPassingSe() = default;

bool ElevatorBaseEmitPassingSe::init_(sead::Heap* heap) {
    return true;
}

// NON_MATCHING: the original keeps hasProc in a second callee-saved register across the accessor destructor
// and selects the result afterwards, and it groups the four matrix loads by base pointer; the logic is the same.
void ElevatorBaseEmitPassingSe::enter() {
    bool close = false;
    if (auto* link = ksys::act::ActorSystem::instance()->getPlayerLink()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        link->getActorViaAccessor(&accessor);
        const sead::Matrix34f& player_mtx = accessor.getActorMtx();
        const sead::Matrix34f& actor_mtx = mActor->getMtx();
        const f32 dx = player_mtx(0, 3) - actor_mtx(0, 3);
        const f32 dz = player_mtx(2, 3) - actor_mtx(2, 3);
        const bool has_proc = accessor.hasProc();
        close = has_proc ? std::sqrt(dx * dx + dz * dz) < 278.18753f : false;
    }
    _28 = close;
}

// NON_MATCHING: same register selection and load grouping as enter().
void ElevatorBaseEmitPassingSe::calc() {
    bool close = false;
    if (auto* link = ksys::act::ActorSystem::instance()->getPlayerLink()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        link->getActorViaAccessor(&accessor);
        const sead::Matrix34f& player_mtx = accessor.getActorMtx();
        const sead::Matrix34f& actor_mtx = mActor->getMtx();
        const f32 dx = player_mtx(0, 3) - actor_mtx(0, 3);
        const f32 dz = player_mtx(2, 3) - actor_mtx(2, 3);
        const bool has_proc = accessor.hasProc();
        close = has_proc ? std::sqrt(dx * dx + dz * dz) < 278.18753f : false;
    }
    if (_28 != close) {
        if (!sUnk_71024358F0 || ksys::evt::Manager::instance()->hasActiveEvent())
            xlinkSearchAndEmit(mActor, "Demo_EntranceLight_Border", 1, nullptr);
        _28 = close;
    }
}

void ElevatorBaseEmitPassingSe::leave() {}

void ElevatorBaseEmitPassingSe::loadParams() {}

}  // namespace uking::behavior
