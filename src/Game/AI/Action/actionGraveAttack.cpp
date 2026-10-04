#include "Game/AI/Action/actionGraveAttack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

GraveAttack::GraveAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GraveAttack::~GraveAttack() = default;

bool GraveAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GraveAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->setScale({1.0f, 1.0f / *mTime_s, 1.0f});
    _38 = *mTime_s;
    getActorAttackSensor(mActor)->activateAttackSensor(0x2000, 0x400c, *mAttackPower_m, 1000, 0.0f,
                                                       9999, 1, 5, false, 1, -1);
    sub_71007A2C30(mActor, "AtkBody", nullptr);
    sub_71007A302C(mActor, "AtkBody", nullptr);
    _3c = 0;
}

void GraveAttack::leave_() {
    sub_71007A3270(mActor, "AtkBody", nullptr);
    sub_71007A2D7C(mActor, "AtkBody");
}

void GraveAttack::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mKeepTime_s, "KeepTime");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
}

void GraveAttack::calc_() {
    switch (_3c) {
    case 0: {
        ksys::Timer::update(&_38, -1.0f);
        mActor->setScale({1.0f, (*mTime_s - _38) / *mTime_s, 1.0f});
        if (_38 <= 0.0f) {
            mActor->setScale(sead::Vector3f::ones);
            _38 = *mKeepTime_s;
            _3c = 1;
        }
        break;
    }
    case 1:
        ksys::Timer::update(&_38, -1.0f);
        if (_38 <= 0.0f) {
            setFinished();
            _3c = 2;
        }
        break;
    }
}

}  // namespace uking::action
