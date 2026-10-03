#include "Game/AI/Action/actionGelEnemySystemHideChase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actGelEnemy.h"

namespace uking::action {

GelEnemySystemHideChase::GelEnemySystemHideChase(const InitArg& arg) : SystemHideChase(arg) {}

GelEnemySystemHideChase::~GelEnemySystemHideChase() = default;

bool GelEnemySystemHideChase::init_(sead::Heap* heap) {
    return SystemHideChase::init_(heap);
}

void GelEnemySystemHideChase::enter_(ksys::act::ai::InlineParamPack* params) {
    SystemHideChase::enter_(params);
    if (auto* gel = sead::DynamicCast<act::GelEnemy>(mActor)) {
        gel->sub_71000269C8();
        gel->_1678 |= 2;
    }
}

void GelEnemySystemHideChase::leave_() {
    if (auto* gel = sead::DynamicCast<act::GelEnemy>(mActor)) {
        gel->sub_7100026A38();
        gel->_1678 &= 0xfd;
    }
    SystemHideChase::leave_();
}

void GelEnemySystemHideChase::loadParams_() {
    SystemHideChase::loadParams_();
}

void GelEnemySystemHideChase::calc_() {
    SystemHideChase::calc_();
    if (auto* gel = sead::DynamicCast<act::GelEnemy>(mActor))
        gel->_14c8._68 = sead::Matrix34f::ident;
}

}  // namespace uking::action
