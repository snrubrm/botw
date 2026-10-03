#include "Game/AI/AI/aiGanonWeaponAttackOnFloor.h"
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GanonWeaponAttackOnFloor::GanonWeaponAttackOnFloor(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonWeaponAttackOnFloor::~GanonWeaponAttackOnFloor() = default;

bool GanonWeaponAttackOnFloor::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonWeaponAttackOnFloor::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71003F1E0C();
}

void GanonWeaponAttackOnFloor::calc_() {
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "MoveDstPos");

    if (!isCurrentChild("接近"))
        return;

    if (getCurrentChild()->isFinished()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("攻撃", &pack);
    } else if (getCurrentChild()->isFailed()) {
        setFailed();
    } else if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor)) {
        ksys::Timer::update(&_50, -1.0f);
        if (boss->sub_71002C6210(90.0f)) {
            if (boss->_1544 > 2 || _50 < 0) {
                boss->_1544 = 0;
                setFailed();
            }
        }
    }
}

void GanonWeaponAttackOnFloor::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonWeaponAttackOnFloor::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool GanonWeaponAttackOnFloor::isFinished() const {
    if (isCurrentChild("攻撃")) {
        auto* child = getCurrentChild();
        if (child->isFinished())
            return true;
        if (child->isFailed())
            return true;
    }
    return false;
}

void GanonWeaponAttackOnFloor::sub_71003F1E0C() {
    _50 = 120.0f;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(*mTargetPos_d, "MoveDstPos", -1);

    const auto& mtx = mActor->getMtx();
    const f32 dx = mtx(0, 3) - mTargetPos_d->x;
    const f32 dz = mtx(2, 3) - mTargetPos_d->z;
    pack.addBool(dx * dx + dz * dz <= *mCloseDist_s * *mCloseDist_s, "IsMoveSide", -1);
    pack.addBool(!testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0), "IsChangeable", -1);
    changeChild("接近", &pack);
}

}  // namespace uking::ai
