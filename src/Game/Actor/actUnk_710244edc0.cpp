#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"

namespace uking::act {

bool Unk_710244edc0::m4(sead::Heap*) {
    return true;
}

void Unk_710244edc0::m5() {
    _68 = false;
    _8.makeAllZero();
}

void Unk_710244edc0::m10() {
    if (sub_71006DFB58())
        return;
    sub_71006E8770();
    sub_71006E8AD0();
    sub_71006E8D00();
    sub_71006E8E04();
    sub_71006E8F20();
    sub_71006E90A0();
    sub_71006E916C();
}

void Unk_710244edc0::m13(int index) {
    _8.resetBit(index);
}

void Unk_710244edc0::m7() {
    Unk_71025ae680::m7();
}

void Unk_710244edc0::m11(bool enable) {
    auto* chemical = _10->getChemicalStuff();
    if (!chemical)
        return;
    if (enable)
        chemical->sub_7100D8EEE0();
    chemical->sub_7100D90C2C(enable);
    chemical->sub_7100D90CD8(enable);
    chemical->sub_7100D90D7C(enable);
    chemical->sub_7100D90F60(enable);
}

bool Unk_710244edc0::m8(const ksys::Message& message) {
    return _30.m2(message);
}

void Unk_710244edc0::sub_71006E8D00() {
    if (sub_71006E9780()) {
        auto* param = sub_71006DF5A4();
        if (param && param->mCurseAffect.ref() && !_8.isOn(0x800)) {
            sub_71006DF750();
            param = sub_71006DF5A4();
            _24 = param ? static_cast<f32>(param->mCurseInterval.ref()) : 0.0f;
            _8.set(0x800);
            param = sub_71006DF5A4();
            if (param && param->mCurseDamage.ref() >= 1) {
                act::ConditionDamageInfo info;
                info.mKind = 11;
                info.mDamage = param->mCurseDamage.ref();
                sub_71006DF5CC(info);
            }
        }
        _28 = 60.0f;
    } else if (_28 > 0.0f) {
        ksys::Timer::update(&_28, -1.0f);
    } else {
        sub_71006DF750();
    }
    _30.x();
}

// 60.0f at 0x7101DA2354 (read by sub_71006E90A0).
extern const f32 sUnk_7101DA2354;
const f32 sUnk_7101DA2354 = 60.0f;

void Unk_710244edc0::sub_71006E90A0() {
    if (!_8.isOnBit(11))
        return;
    if (_24 < 0.0f)
        return;
    if (_28 < sUnk_7101DA2354)
        return;
    ksys::Timer::update(&_24, -1.0f);
    if (_24 < 0.0f) {
        if (_8.isOnBit(11)) {
            if (auto* param = sub_71006DF5A4()) {
                const s32 damage = param->mCurseContinuousDamage.ref();
                if (damage >= 1) {
                    ConditionDamageInfo info{};
                    info.mKind = 11;
                    info.mDamage = damage;
                    info.mFlags = 1;
                    sub_71006DF5CC(info);
                }
            }
            if (auto* param = sub_71006DF5A4())
                _24 = f32(param->mCurseInterval.ref());
            else
                _24 = 0.0f;
        }
    }
}

void Unk_710244edc0::sub_71006E916C() {
    if (!_8.isOnBit(1))
        return;
    if (_20 < 0.0f)
        return;
    ksys::Timer::update(&_20, -1.0f);
    if (_20 <= 0.0f) {
        auto* param = sub_71006DF5A4();
        if (!param)
            return;
        if (!param->mIsDeadIce.ref() && !param->mIsMetamorIce.ref())
            return;
        ConditionDamageInfo info{};
        info.mKind = 3;
        info.mDamage = _10->getMaxLife();
        if (auto* metamor = sub_71006DF5A4()) {
            if (metamor->mIsMetamorIce.ref())
                info.mFlags = 0x20;
        }
        sub_71006DF5CC(info);
        _8.setBit(3);
    }
}

}  // namespace uking::act
