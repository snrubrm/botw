#include "Game/AI/AI/aiGanonBattleRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

GanonBattleRoot::GanonBattleRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBattleRoot::~GanonBattleRoot() = default;

bool GanonBattleRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBattleRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sead::DynamicCast<act::LastBoss>(mActor)) {
        auto* actor = mActor;
        if (actor) {
            auto* target = sub_71005D9050(actor);
            if (target && target->hasProc() && ksys::act::isPlayerProfile(target))
                sub_71005D9330(actor);
            else
                getPlayerPosition();
        }
    }
    sub_71003E3644();
    _38 = false;
}

void GanonBattleRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBattleRoot::loadParams_() {}

}  // namespace uking::ai
