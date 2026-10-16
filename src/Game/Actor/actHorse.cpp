#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/actHorse.h"
#include <basis/seadNew.h>
#include "Game/Actor/actRideable.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Ecosystem/ecoSystem.h"

// Declaration only; the original helper's source owner and namespace are unknown.
void sub_7100D2D424(uking::act::DamageManagerBase* manager);

namespace uking::act {

Horse::Horse(const CreateArg& arg) : HorseBase(arg) {}

ksys::act::BaseProc* Horse::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Horse(arg);
}

// NON_MATCHING: member types incomplete (DamageManager, Unk_710244dd20)
Horse::~Horse() = default;

void Horse::onPreDeleteStart_(PrepareArg& arg) {
    HorseBase::onPreDeleteStart_(arg);
}

void Horse::preDelete2_(const PreDeleteArg& arg) {
    HorseBase::preDelete2_(arg);
    _c58.free();
    _cd8.m6();
    _f50.sub_71006ECD08();
    sub_7100D2D424(&_d20);
    // called through a pointer in the original (not devirtualised)
    (&_d20)->preDelete1();
    (&_d20)->preDelete2();
}

// NON_MATCHING: operands of the `and` swapped (the original ANDs the loaded bits with the mask), as in
// HorseBase::sub_7100E6BE40
void Horse::onEnterSleep_() {
    HorseBase::onEnterSleep_();
    if (_11a8.isOnBit(Flag(Flag::_0))) {
        _d20.removeDamageCallback(&_1170);
        _11a8.resetBit(Flag(Flag::_0));
    }
}

// NON_MATCHING: the original calls m10 virtually (probably an inline member of Unk_71025ae680)
void Horse::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    if (sub_7100E68270())
        return;
    if ((_1028._a & 3) == 0)
        _1028.m10();
    _1028._a &= ~0x24;
    m149();
}

void Horse::m73() {
    _1028.m7();
}

bool Horse::m50() {
    if (Actor::m50())
        return true;
    if (auto* rideable = getHorseOptionsMaybe()) {
        auto* actor = rideable->sub_7100E8B6E0();
        if (actor && actor->m50())
            return true;
    }
    return false;
}

void Horse::loadReduceAncientEnemyDamageInfo() {
    ksys::eco::StatusEffectInfo info;
    const int level = (_b70 >> 9 & 1) + (_b70 >> 10 & 1);
    ksys::eco::Ecosystem::instance()->getStatusEffectInfo(
        ksys::eco::StatusEffect_ReduceAncientEnemyDamge, level, &info);
    _d20._74 = info.val._f32;
}

bool Horse::m81(const ksys::Message& message) {
    if (HorseBase::m81(message))
        return true;
    return _1028.m8(message);
}

}  // namespace uking::act

// NON_MATCHING: null and Actor cast results use conditional selection rather than native branches.
namespace uking::act {

// NON_MATCHING: the original keeps `prev_life != 0` as a flag and schedules the colour / direction
// loads differently.
void Horse::m149() {
    auto* rideable = getHorseOptionsMaybe();
    if (!rideable)
        return;

    s32* life = getLife();
    const s32 prev_life = *life;
    if (_d20.getDamage() != 0) {
        const s32 type = _d20.getField54();
        _d20.getAttackOtherMaterialMask();
        auto* attacker = _d20.m37();
        _d20.applyDamage(*life);
        if (auto* chemical = getChemicalStuff()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            if (ksys::act::acquireActor(attacker, &accessor))
                accessor.sub_7100D12640(chemical, 3);
        }

        if (type != -1 && prev_life != 0) {
            sead::BitFlag8 flags;
            sub_7100732864(&flags, this);
            if (!flags.isZero()) {
                ksys::phys::MaterialMask mask(0x12u);
                DamageReactionInfo info;
                sub_7100732B28(&info, this);
                info._30 = &mask;
                if (flags.isOnBit(0))
                    sub_7100733418(this, &info, nullptr);
                if (flags.isOnBit(1))
                    sub_71007357A8(this, &info);
            }
        }
    }

    if (prev_life != 0 && _d20.getField54() == 0 && _1198 <= 0.0f)
        _1198 = sUnk_7101E7C2BC;

    if (_1198 > 0.0f) {
        sead::Color4u8 color{0, 0, 0, 255};
        color.setf(sUnk_7101E7C2C0.x, sUnk_7101E7C2C0.y, sUnk_7101E7C2C0.z,
                   1.0f - sUnk_7101E7C2D0 * (1.0f - _1198 / sUnk_7101E7C2BC));
        _b94 = color;
        ksys::Timer::update(&_1198, -1.0f);
    } else {
        _b94 = {0, 0, 0, 0};
    }

    sead::Matrix34f mtx;
    if (_d20.getAttackSourceMtx(&mtx)) {
        sead::Vector3f dir = getMtx().getTranslation() - mtx.getTranslation();
        dir.normalize();
        rideable->_148 = dir;
    }
}

}  // namespace uking::act

bool sub_7100081354(const ksys::act::ActorLinkConstDataAccess& accessor, u16 mask) {
    ksys::act::Actor* actor = nullptr;
    if (auto* proc = accessor.getProc())
        actor = sead::DynamicCast<ksys::act::Actor>(proc);
    auto* horse = sead::DynamicCast<uking::act::Horse>(actor);
    return horse && horse->_1028._8.isOn(mask);
}
