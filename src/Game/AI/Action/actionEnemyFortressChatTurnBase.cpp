#include "Game/AI/Action/actionEnemyFortressChatTurnBase.h"
#include "Game/AI/aiUnk_71025b1808.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

namespace uking::action {

EnemyFortressChatTurnBase::EnemyFortressChatTurnBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EnemyFortressChatTurnBase::~EnemyFortressChatTurnBase() = default;

bool EnemyFortressChatTurnBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EnemyFortressChatTurnBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = 0;
    _3c = 0;
    _40 = 0;
    const int* try_num = mTryNum_s;
    for (auto& count : _44)
        count = *try_num;
}

void EnemyFortressChatTurnBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void EnemyFortressChatTurnBase::loadParams_() {
    getStaticParam(&mTryNum_s, "TryNum");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

// NON_MATCHING: the original addresses the entry with `smaddl x20, w25, w26, x23` (32-bit counter), ours
// sign-extends it (`sxtw` + `madd`); the `_44[i]` decrement test is `subs; b.lt` as in Talk::calc_.
void EnemyFortressChatTurnBase::calc_() {
    auto* unit =
        sead::DynamicCast<Unk_71025b1808>(*static_cast<Unk_71025afb58**>(mRegistedActorUnit_a));
    if (!unit) {
        setFailed();
        return;
    }

    bool all_done = true;
    bool any_acked = false;
    int i = 0;
    for (auto& entry : unit->_8.mEntries) {
        const u32 bit = 1u << i;
        if (_40 & bit) {
        } else if (_3c & bit) {
            any_acked = true;
        } else if (!entry.link.hasProcInCalcState()) {
            _44[i] = 0;
        } else if (entry.link == *mTargetActor_d) {
            _44[i] = 0;
        } else {
            const s32 remaining = _44[i] - 1;
            if (remaining >= 0) {
                if (!(_38 & bit)) {
                    _44[i] = remaining;
                    m32(&entry.link);
                }
                all_done = false;
            }
        }
        ++i;
    }

    if (!all_done)
        return;
    if (any_acked)
        setFinished();
    else
        setFailed();
}

void EnemyFortressChatTurnBase::m32(ksys::act::BaseProcLink* link) {}

bool EnemyFortressChatTurnBase::m33(const ksys::MessageAck* ack) {
    return false;
}

bool EnemyFortressChatTurnBase::handleAck_(const ksys::MessageAck* ack) {
    auto* unit =
        sead::DynamicCast<Unk_71025b1808>(*static_cast<Unk_71025afb58**>(mRegistedActorUnit_a));
    if (!unit)
        return true;

    if (!m33(ack))
        return false;

    int i = 0;
    for (auto& entry : unit->_8.mEntries) {
        {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&entry.link, &accessor);
            const auto* id = accessor.getMessageTransceiverId();
            const auto& dest = ack->getDestination();
            if (id->queue_id == dest.queue_id && id->id == dest.id) {
                _3c |= 1u << i;
                return true;
            }
        }
        ++i;
    }
    return false;
}

bool EnemyFortressChatTurnBase::handleMessage_(const ksys::Message* message) {
    return false;
}

}  // namespace uking::action
