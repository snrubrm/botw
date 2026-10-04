#include "Game/Actor/actHorseObject.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actModelMaterialUtil.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Chemical/chmSystemConfig.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::act {

Unk_71024ebb00::Unk_71024ebb00() : ActorBindSet(16, mStorage) {}

Unk_71024ebb00::~Unk_71024ebb00() {
    mEntries = nullptr;
}

HorseObject::HorseObject(const CreateArg& arg) : Actor(arg) {}

HorseObject::~HorseObject() = default;

ksys::act::BaseProc* HorseObject::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) HorseObject(arg);
}

void HorseObject::initMaybe() {
    if (_1410 & 1)
        clearFadeInCreate();
    _1410 = 0;
    _850.resetAll();
    sub_71011DA824(&_850);
    _1408 = sead::Color4u8(0, 0, 0, 0);
    Unk_710260af28::instance()->sub_7100F1E2F4(mModel, sead::Color4f{0.0f, 0.0f, 0.0f, 0.0f});
    _140c = 0;
    Unk_710260af28::instance()->sub_7100F1EAF8(mModel, 0.0f);
}

bool HorseObject::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return true;
}

// NON_MATCHING: instruction scheduling only (the flag store of the physics set after the argument setup, the order of the
// colour conversion, the operand order of the merged `and` of the flag byte)
void HorseObject::calcMaybe() {
    if (!mModel)
        return;
    auto* horse = sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr));
    if (!horse) {
        if (_850.mEntries->isValid(this))
            _850.resetAll();
    } else {
        if (!horse->getModel())
            return;
        if (!_850.mEntries->isValid(this)) {
            _850.mEntries->set(horse, "Root", this, "", &sead::Matrix34f::ident, true);
            _850.bindAll(horse, this, {_850.mCount != 0, _850.mEntries}, true);
        }
        if (auto* physics = mPhysics) {
            if (auto* rideable = horse->getHorseOptionsMaybe()) {
                if (rideable->RideableBase::_18._52 & 8) {
                    physics->getFlags().set(ksys::phys::InstanceSet::Flag::_20000);
                } else if (!(rideable->RideableBase::_8 & 0x40000) && !(rideable->RideableBase::_8 & 0x80000)) {
                    physics->getFlags().reset(ksys::phys::InstanceSet::Flag::_20000);
                    physics->sub_7100FBD324(true, true);
                } else {
                    physics->getFlags().reset(ksys::phys::InstanceSet::Flag::_20000);
                    physics->sub_7100FBD324(false, true);
                }
            }
            if (auto* chemical = horse->getChemicalStuff()) {
                physics->sub_7100FBD3EC(true);
                physics->sub_7100FBD410((chemical->_c & 0x1000000) ? &sead::Vector3f::zero : &chemical->_e4);
            } else {
                physics->sub_7100FBD3EC(false);
            }
        }
        if (auto* chemical = horse->getChemicalStuff()) {
            if ((chemical->mMaterial->attribute.ref() & 0x10000) && chemical->_19c != _140c) {
                _140c = chemical->_19c;
                Unk_710260af28::instance()->sub_7100F1EAF8(mModel, chemical->_19c);
            }
        }
        if (auto* horse_base = sead::DynamicCast<HorseBase>(horse)) {
            if (!(_1408 == horse_base->_b94)) {
                _1408 = horse_base->_b94;
                const sead::Color4f color(_1408.r / 255.0f, _1408.g / 255.0f, _1408.b / 255.0f, _1408.a / 255.0f);
                Unk_710260af28::instance()->sub_7100F1E2F4(mModel, color);
            }
        }
        sub_71011CCB1C(horse->m139());
        x_3(horse->get4f4());
    }
    if ((_1410 & 6) == 6) {
        _1410 &= ~6;
    } else if (_1410 & 2) {
        mActorFlags2.reset(ActorFlag2::_20);
        _1410 &= ~2;
    } else if (_1410 & 4) {
        mActorFlags2.set(ActorFlag2::_20);
        _1410 &= ~4;
    }
}

// NON_MATCHING: operand order of the merged `and` of the flag byte
void HorseObject::m70() {
    f32 value;
    if (auto* horse = sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr)))
        value = horse->m139();
    sub_71011CCB1C(value);
    if ((_1410 & 6) == 6) {
        _1410 &= ~6;
    } else if (_1410 & 2) {
        mActorFlags2.reset(ActorFlag2::_20);
        _1410 &= ~2;
    } else if (_1410 & 4) {
        mActorFlags2.set(ActorFlag2::_20);
        _1410 &= ~4;
    }
}

// NON_MATCHING: the original keeps the result in w0 (ours moves it from w8 after the last block)
bool HorseObject::m81(const ksys::Message& message) {
    if (message.getType() != ksys::MessageType(0x3800002))
        return false;
    void* data = message.getUserData();
    {
        auto* model = mModel;
        const auto key = model->searchMaterial("Mt_Hair");
        if (key.isValid())
            setMaterialVisible(model, key, data == nullptr);
    }
    {
        auto* model = mModel;
        const auto key = model->searchMaterial("Mt_Hair_Ribbon_");
        if (key.isValid())
            setMaterialVisible(model, key, data == nullptr);
    }
    {
        auto* model = mModel;
        const auto key = model->searchMaterial("Mt_PlantFlowerAlpine_A");
        if (key.isValid())
            setMaterialVisible(model, key, data == nullptr);
    }
    return true;
}

ksys::act::Actor* HorseObject::m31() {
    return sead::DynamicCast<ksys::act::Actor>(_840.getProc(nullptr, nullptr));
}

bool HorseObject::shouldUnload(s32* a1) {
    if (_840.hasProc())
        return false;
    return shouldUnloadBecauseOfDistance(a1);
}

HorseReins::HorseReins(const CreateArg& arg) : Actor(arg) {}

HorseReins::~HorseReins() = default;

ksys::act::BaseProc* HorseReins::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) HorseReins(arg);
}

bool HorseReins::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return true;
}

ksys::act::Actor* HorseReins::m31() {
    return sead::DynamicCast<ksys::act::Actor>(_840.getProc(nullptr, nullptr));
}

bool HorseReins::shouldUnload(s32* a1) {
    if (_840.hasProc())
        return false;
    return shouldUnloadBecauseOfDistance(a1);
}

void HorseReins::initMaybe() {
    if (_868.isOn(4))
        clearFadeInCreate();
    mActorFlags2.reset(ActorFlag2::_20);
    _868.setDirect(3);
    _860 = 0;
    Unk_710260af28::instance()->sub_7100F1E2F4(mModel, sead::Color4f{0.0f, 0.0f, 0.0f, 0.0f});
    _864 = 0;
    Unk_710260af28::instance()->sub_7100F1EAF8(mModel, 0.0f);
}

ksys::act::Actor* HorseReins::sub_7100E7BA64() {
    return sead::DynamicCast<ksys::act::Actor>(_840.getProc(nullptr, nullptr));
}

void HorseReins::sub_7100E7BC10(ksys::act::BaseProc* horse) {
    _840.acquire(horse, false);
}

void HorseReins::updatePositionMaybe() {
    if (_868.isOn(8))
        mActorFlags2.set(ActorFlag2::_20);
}

}  // namespace uking::act
