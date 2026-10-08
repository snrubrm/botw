#include "Game/Actor/actWolfLink.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameWolfLinkMgr.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWolfLink.h"

namespace uking::act {

WolfLink::~WolfLink() = default;

void WolfLink::preDelete2_(const PreDeleteArg& arg) {
    Enemy::preDelete2_(arg);
    _1608.freeBuffer();
}

bool WolfLink::startPreparingForPreDelete_() {
    if (!Enemy::startPreparingForPreDelete_())
        return false;
    if (_c48._8.hasProc()) {
        _1638.sub_710070DCC0(&_c48._8, false);
        _c48._8.reset();
        _c48._7c = 0;
    }
    if (auto* manager = WolfLinkMgr::instance())
        manager->sub_7100682F80(this, true);
    return true;
}

// NON_MATCHING: comparator materialization and the final search result branch differ.
bool WolfLink::sub_71002F420C() {
    if (!_c48._8.hasProc())
        return false;
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(&_c48._8, &accessor))
        return false;
    const u32 id = accessor.getId();
    return _1608.binarySearch(id, +[](const Entry1608& entry, const u32& id) -> s32 {
        return (entry.mActorId > id) - (entry.mActorId < id);
    }) != -1;
}

void WolfLink::sub_71002F493C() {
    if (_c48._8.hasProc()) {
        _1638.sub_710070DCC0(&_c48._8, false);
        _c48._8.reset();
        _c48._7c = 0;
    }
}

bool WolfLink::shouldUnload(s32* a1) {
    s32 reason = 0;
    const bool unload = Enemy::shouldUnload(&reason);
    if (unload)
        uking::ui::showInfoOverlay(0x28);
    *a1 = reason;
    return unload;
}

void WolfLink::m156() {
    const s32 life_value = _168c;
    if (life_value < 0) {
        DynamicActor::m156();
        return;
    }
    if (s32* life = getLife())
        *life = life_value;
    _168c = -1;
}

s32 WolfLink::getBaseAtkPower() {
    auto* param = _1680;
    const f32 base = param->mAttackBase.ref();
    const f32 heart_mod = param->mAttackHeartMod.ref();
    const u16 flags = _1698;
    s32 power = base + heart_mod * (getMaxLife() / 4);
    if (flags & 0x1000)
        power *= _1680->mPowerUpFoodAttackMod.ref();
    return power;
}

s32 WolfLink::sub_71002F4428() {
    auto* param = _1680;
    const f32 base = param->mDefenseBase.ref();
    const f32 heart_mod = param->mDefenseHeartMod.ref();
    return base + heart_mod * (getMaxLife() / 4);
}

void WolfLink::sub_71002F4A40(const sead::Vector3f* pos, f32 a, f32 b) {
    const f32 dist_sq = (getMtx().getTranslation() - *pos).squaredLength();
    if (dist_sq > 1600.0f) {
        if (auto* bone_control = mBoneControl) {
            if (auto* controller = bone_control->_0) {
                controller->_8 = controller->_c;
                controller->_10._9c = controller->_10._98;
                controller->sub_7100D85774();
                _1698 &= ~8;
            }
        }
    } else {
        if (auto* bone_control = mBoneControl) {
            if (auto* controller = bone_control->_0) {
                if (b > 0.0f)
                    controller->_10.sub_7100D8A9D0(b);
                if (a > 0.0f)
                    controller->sub_7100D85600(a);
                controller->sub_7100D8571C(*pos);
                controller->sub_7100D85750();
                _1698 |= 8;
            }
        }
    }
}

void WolfLink::sub_71002F4B3C() {
    if (auto* bone_control = mBoneControl) {
        if (auto* controller = bone_control->_0) {
            controller->_8 = controller->_c;
            controller->_10._9c = controller->_10._98;
            controller->sub_7100D85774();
            _1698 &= ~8;
        }
    }
}

bool WolfLink::m81(const ksys::Message& message) {
    if (Enemy::m81(message))
        return true;
    if (message.getType() == 0x80000a7) {
        if (auto* mtx = static_cast<const sead::Matrix34f*>(message.getUserData())) {
            setMtx(*mtx, true, true);
            nullsub_4648();
        }
        return true;
    }
    if (message.getType() == 0x3000010) {
        mActorFlags2.set(ActorFlag2::_20);
        return true;
    }
    return false;
}

}  // namespace uking::act

void* Unk_71023d2f68::m2() {
    return nullptr;
}

void* Unk_71023d2f90::m2() {
    return nullptr;
}
