#include "Game/AI/Action/actionGelEnemyAppear.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actGelEnemy.h"

namespace uking::action {

GelEnemyAppear::GelEnemyAppear(const InitArg& arg) : Appear(arg) {}

GelEnemyAppear::~GelEnemyAppear() = default;

bool GelEnemyAppear::init_(sead::Heap* heap) {
    return Appear::init_(heap);
}

// NON_MATCHING: the original loads the _1678 flag byte before the _1620.z store (our load follows it)
void GelEnemyAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    Appear::enter_(params);
    if (auto* gel = sead::DynamicCast<act::GelEnemy>(mActor)) {
        gel->sub_71000269C8();
        gel->_1620.z = 1.0f;
        gel->_1678 &= 0xfd;
    }
}

void GelEnemyAppear::leave_() {
    if (auto* gel = sead::DynamicCast<act::GelEnemy>(mActor))
        gel->sub_7100026A38();
    Appear::leave_();
}

void GelEnemyAppear::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
}

void GelEnemyAppear::calc_() {
    Appear::calc_();
}

}  // namespace uking::action
