#include "Game/AI/AI/aiBeeBattle.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

BeeBattle::BeeBattle(const InitArg& arg) : EnemyBattle(arg) {}

BeeBattle::~BeeBattle() = default;

bool BeeBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void BeeBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void BeeBattle::calc_() {
    EnemyBattle::calc_();
}

void BeeBattle::leave_() {
    EnemyBattle::leave_();
}

void BeeBattle::loadParams_() {
    EnemyBattle::loadParams_();
}

void BeeBattle::m36(sead::Vector3f* pos) {
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(&m35(), &acc);
    *pos = acc.getField44C_Vec3();
}

}  // namespace uking::ai
