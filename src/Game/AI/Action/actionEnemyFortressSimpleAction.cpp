#include "Game/AI/Action/actionEnemyFortressSimpleAction.h"
#include "Game/AI/aiUnk_71025b1808.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

EnemyFortressSimpleAction::EnemyFortressSimpleAction(const InitArg& arg) : ForkTimer(arg) {}

EnemyFortressSimpleAction::~EnemyFortressSimpleAction() = default;

bool EnemyFortressSimpleAction::init_(sead::Heap* heap) {
    return ForkTimer::init_(heap);
}

void EnemyFortressSimpleAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTimer::enter_(params);
    _48.x(mActor);
}

void EnemyFortressSimpleAction::leave_() {
    if (!isActorDeletedOrDeleting()) {
        auto* unit = sead::DynamicCast<Unk_71025b1808>(
            *static_cast<Unk_71025afb58**>(mRegistedActorUnit_a));
        if (unit) {
            for (auto& entry : unit->_8.mEntries) {
                if (entry.link.hasProcInCalcState())
                    _78.sub_710070DCC0(&entry.link, true);
            }
        }
    }
    ForkTimer::leave_();
}

void EnemyFortressSimpleAction::loadParams_() {
    ForkTimer::loadParams_();
    getStaticParam(&mNoRequestTime_s, "NoRequestTime");
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

void EnemyFortressSimpleAction::calc_() {
    ForkTimer::calc_();
    auto* unit =
        sead::DynamicCast<Unk_71025b1808>(*static_cast<Unk_71025afb58**>(mRegistedActorUnit_a));
    if (!unit) {
        setFailed();
        return;
    }
    if (_30 > f32(*mNoRequestTime_s)) {
        for (auto& entry : unit->_8.mEntries) {
            if (entry.link.hasProcInCalcState())
                _48.sub_710070DCC0(&entry.link, true);
        }
    }
}

}  // namespace uking::action
