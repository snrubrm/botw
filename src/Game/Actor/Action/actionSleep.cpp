#include "Game/Actor/Action/actionSleep.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actUnk_7102376d50.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

Sleep::Sleep(const InitArg& arg) : StopBase(arg) {}

Sleep::~Sleep() = default;

bool Sleep::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void Sleep::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
    m32();
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.set(0x100);
}

void Sleep::leave_() {
    StopBase::leave_();
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.reset(0x100);
}

void Sleep::loadParams_() {
    StopBase::loadParams_();
}

void Sleep::calc_() {
    StopBase::calc_();
    if (mActor->getASList()->x(70, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        uking::act::Unk_7102376d50 info;
        info.mFlags.set(1);
        playerOrEnemyDropWeapon(mActor, &sead::Vector3f::zero, 0, false, false, &info, false);
        playerOrEnemyDropWeapon(mActor, &sead::Vector3f::zero, 1, false, false, &info, false);
    }
}

void Sleep::m32() {
    playAS("Sleep", true, 0, 0, -1.0f);
}

}  // namespace uking::action
