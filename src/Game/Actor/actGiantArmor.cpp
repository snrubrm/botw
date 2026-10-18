#include "Game/Actor/actGiantArmor.h"
#include <basis/seadNew.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
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

// NON_MATCHING: the body matches; only the position of the cNullChar load differs (the original hoists
// it above the first ASList query, this build loads it after the query).
// 0x7100029bc8 (the calcMaybe override): when the linked actor has an animation name that this
// armor's list also has, start it.
void GiantArmor::calcMaybe() {
    DynamicActor::calcMaybe();
    auto* other = sead::DynamicCast<Actor>(_be8.getProc(nullptr, nullptr));
    if (!other)
        return;

    ksys::as::ASList* other_list = other->getASList();
    ksys::as::ASList* list = getASList();
    const sead::SafeString& name0 = other_list->x_1(2, 2);
    if (!name0.isEmpty() && list->sub_710115AA68(name0)) {
        list->startAnimationMaybe(-1.0f, -1.0f, name0, 0, 0, true);
        return;
    }
    const sead::SafeString& name1 = other_list->x_1(2, 1);
    if (!name1.isEmpty() && list->sub_710115AA68(name1)) {
        list->startAnimationMaybe(-1.0f, -1.0f, name1, 0, 0, true);
        return;
    }
    const sead::SafeString& name2 = other_list->x_1(2, 0);
    if (!name2.isEmpty() && list->sub_710115AA68(name2)) {
        list->startAnimationMaybe(-1.0f, -1.0f, name2, 0, 0, true);
        return;
    }
    const sead::SafeString& name3 = other_list->x_1(1, 2);
    if (!name3.isEmpty() && list->sub_710115AA68(name3)) {
        list->startAnimationMaybe(-1.0f, -1.0f, name3, 0, 0, true);
        return;
    }
    const sead::SafeString& name4 = other_list->x_1(1, 1);
    if (!name4.isEmpty() && list->sub_710115AA68(name4)) {
        list->startAnimationMaybe(-1.0f, -1.0f, name4, 0, 0, true);
        return;
    }
    const sead::SafeString& name5 = other_list->x_1(1, 0);
    if (!name5.isEmpty() && list->sub_710115AA68(name5)) {
        list->startAnimationMaybe(-1.0f, -1.0f, name5, 0, 0, true);
        return;
    }
    const sead::SafeString& name6 = other_list->x_1(0, 2);
    if (!name6.isEmpty() && list->sub_710115AA68(name6)) {
        list->startAnimationMaybe(-1.0f, -1.0f, name6, 0, 0, true);
        return;
    }
    const sead::SafeString& name7 = other_list->x_1(0, 1);
    if (!name7.isEmpty() && list->sub_710115AA68(name7)) {
        list->startAnimationMaybe(-1.0f, -1.0f, name7, 0, 0, true);
        return;
    }
    const sead::SafeString& name8 = other_list->x_1(0, 0);
    if (!name8.isEmpty() && list->sub_710115AA68(name8)) {
        list->startAnimationMaybe(-1.0f, -1.0f, name8, 0, 0, true);
        return;
    }
}

void GiantArmor::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    DynamicActor::m76(setter);
    if (!_c18)
        _c00.sub_7100029308(nullptr);
    _c18 = false;
    // C++14 evaluation order: the original evaluates the destination first
    _be8.operator=(_b90._40);
    _bf8 = _be0;
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
