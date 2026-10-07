#include "Game/AI/Action/actionSandwormTackleMove.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

Unk_71024512c0::~Unk_71024512c0() = default;
void* Unk_71024512c0::m2() { return &_18; }

Unk_SandwormTackleTarget::Unk_SandwormTackleTarget(uking::act::Enemy* actor)
    : mActor(actor), _8(actor) {}

// NON_MATCHING: The owner and key argument-address calculations are scheduled differently.
Unk_SandwormTackleTarget::~Unk_SandwormTackleTarget() {
    mActor->_1128.sub_7100D3CFEC(_48);
}

// NON_MATCHING: The parts-member address calculation is scheduled differently.
bool Unk_SandwormTackleTarget::sub_710073E5E0(const ksys::MessageAck* ack) {
    if (!_8.sub_710070E070(*ack))
        return false;
    if (!_8._14) {
        _58 = 3;
        _38.reset();
    } else {
        _58 = 2;
        mActor->_1128.sub_7100D3D1E0(_48, _38);
        ksys::act::ActorConstDataAccess actor;
        ksys::act::acquireActor(&_38, &actor);
        actor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
    return true;
}

bool Unk_SandwormTackleTarget::sub_710073E45C(sead::Heap* heap, const sead::SafeString& name) {
    if (!name.isEmpty())
        _48 = name;
    return mActor->_1128.sub_7100D3CED8(_48, heap);
}

void Unk_SandwormTackleTarget::sub_710073E580(ksys::act::BaseProcLink* link) {
    if (link->hasProcInCalcState()) {
        _8.sub_710070DCC0(link, true);
        _38 = *link;
        _58 = 1;
    } else {
        _58 = 3;
    }
}

}  // namespace uking::action
