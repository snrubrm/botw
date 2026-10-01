#include "Game/AI/AI/aiLynelNoticeTerror.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

LynelNoticeTerror::LynelNoticeTerror(const InitArg& arg) : EnemyNoticeTerror(arg) {}

LynelNoticeTerror::~LynelNoticeTerror() = default;

bool LynelNoticeTerror::init_(sead::Heap* heap) {
    return EnemyNoticeTerror::init_(heap);
}

void LynelNoticeTerror::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNoticeTerror::enter_(params);
}

void LynelNoticeTerror::calc_() {
    EnemyNoticeTerror::calc_();
}

void LynelNoticeTerror::leave_() {
    EnemyNoticeTerror::leave_();
}

void LynelNoticeTerror::loadParams_() {
    EnemyNoticeTerror::loadParams_();
}

void LynelNoticeTerror::m36() {
    if (auto* unk = sub_71005D9D68(mActor)) {
        if (!unk->sub_71002DC9E8(_60._0, 2, false))
            unk->sub_71002DC628(_60._0, 2);
    }
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(&_60._0, &acc);
    m35();
}

}  // namespace uking::ai
