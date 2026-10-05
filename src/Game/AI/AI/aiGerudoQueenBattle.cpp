#include "Game/AI/AI/aiGerudoQueenBattle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_71024ef620.h"

namespace uking::ai {

GerudoQueenBattle::GerudoQueenBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GerudoQueenBattle::~GerudoQueenBattle() = default;

bool GerudoQueenBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GerudoQueenBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GerudoQueenBattle::leave_() {
    mActor->emitBasicSigOff();
    _40.fade();
    _80->sub_7100EBB518();
    mActor->resetConnectedCalcChild(false);
}

void GerudoQueenBattle::loadParams_() {
    getStaticParam(&mRetireFrame_s, "RetireFrame");
}

}  // namespace uking::ai
