#include "Game/AI/AI/aiPartsNoticeSelect.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

PartsNoticeSelect::PartsNoticeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
PartsNoticeSelect::~PartsNoticeSelect() {
    ;
}

bool PartsNoticeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PartsNoticeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71004F4C38())
        changeChild("パーツ気づき", params);
    else
        changeChild("パーツ通常", params);
}

void PartsNoticeSelect::calc_() {
    if (!getCurrentChild()->isChangeable())
        return;

    const bool is_on = isCurrentChild("パーツ気づき");
    const bool should_be_on = sub_71004F4C38();
    if (is_on) {
        if (!should_be_on)
            changeChild("パーツ通常");
    } else if (should_be_on) {
        changeChild("パーツ気づき");
    }
}

void PartsNoticeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

bool PartsNoticeSelect::sub_71004F4C38() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&enemy->getActorPartsActor(mPartsName_s), &accessor);
    return accessor.isStateCalc() && accessor.sub_7100D10E6C(25);
}

void PartsNoticeSelect::loadParams_() {
    getStaticParam(&mPartsName_s, "PartsName");
}

}  // namespace uking::ai
