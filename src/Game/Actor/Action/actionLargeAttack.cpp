#include "Game/Actor/Action/actionLargeAttack.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/aiUnk_710073fa90.h"

namespace uking::action {

// NON_MATCHING: store scheduling (the damage callback member's zero stores are ordered differently)
LargeAttack::LargeAttack(const InitArg& arg) : ActionEx(arg) {}

LargeAttack::~LargeAttack() = default;

void LargeAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710073FA90(&_8c, mActor);
    _b0 = 0;
    playAS("LargeAttack", false, 0, 0, -1.0f);
    setDamageCallbackTiming(mActor, 4, &_58);
}

void LargeAttack::leave_() {
    sub_71005D79AC(mActor, *mParams.mWeaponIdx_s, act::Unk_71002edaec(1));
    ksys::act::disableAttClient(mActor, "Counter");
    sub_71005DA114(mActor, &_58);
}

void LargeAttack::loadParams_() {
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mAttackRatio_s, "AttackRatio");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mParams.mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mParams.mJustAvoidAngle_s, "JustAvoidAngle");
}

// NON_MATCHING: stack slots of the direction / up temporaries and the operand order of the second up length.
void LargeAttack::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    sub_710073FA94(&_8c, mActor);
    const f32 reach = sub_71007322E8(mActor, *mParams.mWeaponIdx_s);
    sub_71005DAB2C(mActor, reach + *mParams.mJustAvoidSideDist_s,
                   reach + *mParams.mJustAvoidBackDist_s, *mParams.mJustAvoidAngle_s, 0);
    switch (_b0) {
    case 0: {
        _80 *= 0.5f;
        _80.updateStats();
        sub_710073FA94(&_8c, mActor);
        sead::Vector3f dir = *mParams.mTargetPos_d;
        dir -= mActor->getMtx().getTranslation();
        const sead::Vector3f up = getUpDir(controller->get70());
        ksys::util::sub_71011EFA00(&dir, dir, getUpDir(up));
        dir.normalize();
        sub_710074006C(&_8c, dir, up, true, 0.16f, *mParams.mRotSpd_s, *mParams.mRotSpd_s * 0.1f);
        sub_7100740E04(_8c, controller);
        ksys::as::ASList::Unk4 query;
        if (sub_71005DD66C(mActor, &query, 0, 0)) {
            sub_71005D7ADC(mActor, *mParams.mWeaponIdx_s, 2, &query.name, nullptr, 1, 1, 0, 1,
                           *mParams.mAttackRatio_s, 1.0f);
            _b0 = 1;
        }
        break;
    }
    case 1:
        _80 *= 0.5f;
        _80.updateStats();
        sub_7100738660(controller, 0.5f);
        if (sub_71005DD74C(mActor, nullptr, 0, 0))
            sub_71005D79AC(mActor, *mParams.mWeaponIdx_s, act::Unk_71002edaec(1));
        break;
    }
    sub_710072C1B4(controller, mActor->getMtx().getBase(2));
    controller->sub_7100F5E7F0(_80.value * 30.0f);
    if (isFinishedAS(0, 0))
        setFinished();
}

bool LargeAttack::isChangeable() const {
    return false;
}

}  // namespace uking::action
