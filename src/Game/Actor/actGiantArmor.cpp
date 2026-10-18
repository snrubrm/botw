#include "Game/Actor/actGiantArmor.h"
#include <basis/seadNew.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGiantArmor.h"

namespace uking::act {

GiantArmor::GiantArmor(const CreateArg& arg) : DynamicActor(arg) {}

ksys::act::BaseProc* GiantArmor::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) GiantArmor(arg);
}

f32 GiantArmor::sub_7100029B54() const {
    return getParam()->getRes().mGParamList->getGiantArmor()->mDamageScale.ref();
}

bool GiantArmor::sub_7100029E7C(Actor* owner, s32 index) {
    const auto lock = sead::makeScopedLock(_b90._0);
    _b90._40.acquire(owner, false);
    _be0 = index;
    return true;
}

void GiantArmor::sub_7100029AF8(f32* out_scale, s32* out_level,
                                const ai::Unk_71023f36d8::Info* info) {
    if (_c00._10) {
        _c00._10->m4(out_scale, out_level, info);
        return;
    }
    const f32 scale = getParam()->getRes().mGParamList->getGiantArmor()->mDamageScale.ref();
    s32 level = info->level;
    if (scale <= 0.0f)
        level = 1;
    if (out_scale)
        *out_scale = scale;
    if (out_level)
        *out_level = level;
}

void GiantArmor::initMaybe() {
    _c18 = 0;
    _c00._8 = 0;
    DynamicActor::initMaybe();
}

ksys::act::Actor* GiantArmor::m31() {
    return sead::DynamicCast<Actor>(_be8.getProc(nullptr, nullptr));
}

void GiantArmor::updatePositionMaybe() {
    DynamicActor::updatePositionMaybe();
    if (auto* actor = sead::DynamicCast<Actor>(_be8.getProc(nullptr, this)))
        sub_71011CCB1C(actor->m139());
}

void GiantArmor::m73() {
    DynamicActor::m73();
}

bool GiantArmor::canWakeUp_() {
    if (!Actor::canWakeUp_())
        return false;
    auto* actor = sead::DynamicCast<Actor>(_b90._40.getProc(nullptr, nullptr));
    if (actor && actor->getState() != State::Calc)
        return false;
    return true;
}

void GiantArmor::sub_7100029AA8(Actor* actor) {
    if (_b90._40.hasProcById(actor) || _be8.hasProcById(actor)) {
        _c00.sub_7100029308(actor);
        _c18 = 1;
    }
}

// 0x71000294f0: finds the attack info of the actor linked at _be8 whose rigid body is the armor slot's
// rigid body (GParamList GiantArmorSlot) and classifies it with sub_7100739634.
bool GiantArmor::Unk_c00::sub_71000294F0(Unk_7100739634Result* out, Actor* actor) {
    auto* other = sead::DynamicCast<Actor>(mOwner->_be8.getProc(nullptr, actor));
    if (!other)
        return false;
    if (!sub_71007A2604(other))
        return false;
    ksys::act::Chemical* chemical = mOwner->getChemicalStuff();
    if (!chemical)
        return false;
    const s32 count = sub_71007A26AC(other);
    if (count < 1)
        return false;

    bool result = false;
    for (s32 i = 0; i < count; ++i) {
        auto* info = sub_71007A255C(other, i);
        if (!info)
            continue;
        const sead::SafeString body_name = info->_c0->getHkBodyName();
        if (sub_710072D53C(other, mOwner->_bf8) == body_name) {
            result = sub_7100739634(out, chemical, info, nullptr);
            break;
        }
    }
    return result;
}

// NON_MATCHING: the two state-bit updates are the same; clang 4 keeps result.kind in x20 and lays the
// skip path out of line, while this build reuses the result._c comparison (cset) across both halves.
// 0x7100029308: refreshes the two weak-point state bits from the actor's attack classification.
void GiantArmor::Unk_c00::sub_7100029308(Actor* actor) {
    Unk_7100739634Result result{};
    result._c = -1;
    sub_71000294F0(&result, actor);

    if (_8 & 4) {
        ksys::act::Chemical* chemical = mOwner->getChemicalStuff();
        if (!chemical || chemical->_c0 != 2)
            _8 &= ~4;
    } else {
        if (result._c != 2) {
            ksys::act::Chemical* chemical = mOwner->getChemicalStuff();
            if (result.kind == 2 || (chemical && chemical->_c0 == 2)) {
                chemical = mOwner->getChemicalStuff();
                if (chemical && chemical->_c0 != 2)
                    chemical->sub_7100D90858(false, 2, false, true, false);
                _8 |= 4;
            }
        }
    }

    if (_8 & 0x10) {
        bool keep = false;
        if (result._c != 2) {
            ksys::act::Chemical* chemical = mOwner->getChemicalStuff();
            if (chemical && (chemical->mMaterial->attribute.ref() & 8) && !(chemical->_be & 4)) {
                chemical = mOwner->getChemicalStuff();
                keep = result.kind == 4 || (chemical && chemical->_1b8 > 0);
            }
        }
        if (!keep)
            _8 &= ~0x10;
    } else if (result._c != 2) {
        ksys::act::Chemical* chemical = mOwner->getChemicalStuff();
        if (chemical && (chemical->mMaterial->attribute.ref() & 8) && !(chemical->_be & 4)) {
            chemical = mOwner->getChemicalStuff();
            if (result.kind == 4 || (chemical && chemical->_1b8 > 0))
                _8 |= 0x10;
        }
    }
}

}  // namespace uking::act
