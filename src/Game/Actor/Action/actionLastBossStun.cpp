#include "Game/Actor/Action/actionLastBossStun.h"
#include "Game/Actor/actLastBoss.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"
#include <limits>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

LastBossStun::LastBossStun(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossStun::~LastBossStun() = default;

bool LastBossStun::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: scheduling around the flag updates and an inverted csel for the down time.
void LastBossStun::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* boss = sead::DynamicCast<act::LastBoss>(mActor);
    if (!boss) {
        setFailed();
        return;
    }

    if (boss->_14f8._30.isOnBit(10)) {
        boss->_14f8._30.resetBit(10);
        xlinkSearchAndEmit(mActor, "BlownWithPile", 1, nullptr);
    }

    if (!mActor->getCharacterController())
        return;

    _39 = false;
    _3a = false;
    sub_710073FA90(&_60, mActor);
    if (boss->_14e8.isOnBit(2))
        boss->_14e8.resetBit(2);
    boss->_14e8.resetBit(18);
    boss->_14e8.setBit(3);
    const u32 stun_type = boss->_14e4;
    boss->_14f8._30.resetBit(0);
    boss->_14f8._30.setBit(4);

    f32 time;
    if (stun_type == 1) {
        time = *mStunTime_s;
        _38 = true;
        playAS("Damage_Big_Up", false, 0, 0, -1.0f);
    } else {
        _38 = false;
        if (auto* life = mActor->getLife(); life && *life == 0) {
            setFinished();
            return;
        }
        const f32* const* base_time = &mStunTime_s;
        playAS("Down_Start", false, 0, 0, -1.0f);
        _48 = sead::Vector3f::ey;
        if (!boss->_14f8._30.isOnBit(9))
            base_time = &mShockWaveDownTime_s;
        time = **base_time;
        _3a = true;
    }

    time += getNumberOfClearedRemains() * *mAddStunTime_s;
    _3c = ksys::Timer(time, time);

    if (!boss->_14e8.isOnBit(1)) {
        playAS("DownWaitMaterial", false, 1, 0, -1.0f);
    } else {
        boss->_14e8.setBit(10);
        if (boss->_14e8.isOnBit(2))
            boss->_14e8.resetBit(2);
        boss->_14f8._30.resetBit(0);
        boss->update();
    }

    _3b = false;
    boss->_14f8._30.resetBit(8);
    boss->_14f8._30.resetBit(9);
}

void LastBossStun::leave_() {
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor)) {
        boss->_14e8.resetBit(3);
        boss->stunEnd();
    }
}

void LastBossStun::loadParams_() {
    getStaticParam(&mStunTime_s, "StunTime");
    getStaticParam(&mAddStunTime_s, "AddStunTime");
    getStaticParam(&mShockWaveDownTime_s, "ShockWaveDownTime");
}

// NON_MATCHING: the ey chase (load order, and the snap is a 12-byte copy in the original) and the timer compare.
void LastBossStun::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    auto* boss = sead::DynamicCast<act::LastBoss>(mActor);
    if (!boss) {
        setFailed();
        return;
    }

    boss->_14f8._30.resetBit(8);
    boss->_14f8._30.resetBit(9);

    if (auto* life = mActor->getLife(); life && *life == 0 && !_38 && !_39 && _3a) {
        setFinished();
        return;
    }

    if (_38) {
        if (sub_71005DD5B0(mActor, 0x2f, nullptr, 0, 0)) {
            controller->sub_7100F5EF08(true);
            controller->sub_7100F62B70(0.1f);
            controller->sub_7100F5F458(ksys::act::MotionType::_0);
            _48 = controller->get70();
            _48.normalize();
            controller->sub_7100F5EE1C(sead::Vector3f::ey * -29.0f);
            boss->_14e4 = 0;
            _38 = false;
            _39 = true;
            if (auto* bone_control = sub_71007398C0(mActor)) {
                bone_control->sub_7100D86C90();
                bone_control->sub_7100D895C8();
                bone_control->sub_7100D89E34();
                bone_control->sub_7100D8A130();
            }
        }
    } else if (_39) {
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        sead::Vector3f home;
        mActor->getHomePos(&home);

        const f32 max_step = ksys::VFR::instance()->getDeltaFrame() * 0.1f;
        const sead::Vector3f diff = sead::Vector3f::ey - _48;
        const f32 dist = diff.length();
        if (dist <= max_step)
            _48 = sead::Vector3f::ey;
        else
            _48 += diff * (1.0f / dist) * max_step;
        _48.normalize();

        sead::Vector3f dir = home;
        dir -= pos;
        ksys::util::sub_71011EFA00(&dir, dir, _48);
        dir.normalize();
        sub_710073FA94(&_60, mActor);
        sub_710074006C(&_60, dir, _48, true, 0.16f, 0.16f, 0.016f);
        controller->sub_7100F5EDE8(_48);
        sub_7100740E04(_60, controller);

        if (!_3a && pos.y - home.y < 5.0f) {
            _39 = false;
            _3a = true;
            playAS("Down_Start", false, 0, 0, -1.0f);
            _3c = ksys::Timer(*mStunTime_s, *mStunTime_s);
        }
    } else {
        sub_71007377D4(controller, 0.8f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }

    _3c.update();
    if (_3a && *mStunTime_s - _3c.value > 10.0f) {
        boss->_14e8.resetBit(3);
        const auto is_recovered = [this] {
            auto* last_boss = sead::DynamicCast<act::LastBoss>(mActor);
            return last_boss &&
                   !(last_boss->_1538 > last_boss->_1534 && last_boss->_1540 > last_boss->_153c);
        };
        if (_3c.value <= std::numeric_limits<f32>::epsilon() || is_recovered()) {
            controller->sub_7100F5FB24(sead::Vector3f::zero);
            setFinished();
        }
    }

    if (boss->_14e8.isOnBit(1)) {
        if (_3b)
            playAS("DownWaitMaterial", false, 1, 0, -1.0f);
        _3b = isFinishedAS(1, 0);
    }
}

}  // namespace uking::action
