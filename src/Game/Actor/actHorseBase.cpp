#include "Game/Actor/actHorseBase.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorse.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseUnit.h"

namespace uking::act {

HorseBase::HorseBase(const CreateArg& arg) : Actor(arg), _8d0() {
    _1c0 = 2;
}

// NON_MATCHING: the original releases _a70 from a member destructor (after ExtendedEntity's)
HorseBase::~HorseBase() {
    if (_a70)
        _a70->release();
}

s32 HorseBase::x() const {
    const auto* param = getParam();
    if (!param)
        return 1;
    const auto* gparams = param->getRes().mGParamList;
    if (!gparams)
        return 1;
    const auto* unit = gparams->getHorseUnit();
    if (!unit)
        return 1;
    return unit->mRiddenAnimalType.ref();
}

int HorseBase::m109() {
    return _b70 >> 7 & 2 ^ 10;
}

bool HorseBase::canWakeUp_() {
    return Actor::canWakeUp_();
}

u8 HorseBase::sub_7100E68270() const {
    return getParam()->getRes().mGParamList->getHorse()->mIsDecoy.ref();
}

s32 HorseBase::sub_7100E68298() const {
    return getParam()->getRes().mGParamList->getHorse()->mNature.ref();
}

bool HorseBase::sub_7100E696D4() const {
    if (!_b10)
        return false;
    if (u8(_b10->Unk_7100e8b2b8::_8) != 3)
        return false;
    return _b40 == nullptr;
}

void HorseBase::sub_7100E6AD3C() {
    _b10->m29();
}

f32 HorseBase::sub_7100E6AD4C() {
    return _b10->m31();
}

void HorseBase::m114() {
    if (_b10)
        _b10->m9();
}

bool HorseBase::sub_7100E6AF2C(ksys::act::BaseProc* proc) const {
    return _870.hasProcById(proc);
}

bool HorseBase::sub_7100E6B068(ksys::act::BaseProc* proc) const {
    return _880.hasProcById(proc);
}

void HorseBase::sub_7100E6BA08() {
    auto* controller = getCharacterController();
    if (!controller)
        return;
    controller->sub_7100F60500(_b10->_1c4);
    controller->sub_7100F5F6FC(sead::Vector3f::zero);
    _b74 |= 0x100;
}

// NON_MATCHING: operands of the `and` swapped (the original ANDs the loaded bits with the mask)
bool HorseBase::sub_7100E6BE40() const {
    return _a90.isOnBit(Flag(Flag::_0));
}

f32 HorseBase::sub_7100E6BE6C() const {
    if (!_a98._10)
        return 1.0f;
    return _a98._2c + 1.0f;
}

void HorseBase::sub_7100E6BE8C(f32 delta) {
    _b84 = sead::Mathf::clamp(_b84 + delta, 0.0f, 1.0f);
}

void HorseBase::sub_7100E6BEC0(bool on) {
    if (!_b18)
        return;
    _b18->_8.changeBit(Unk_71024eb548::Flag(Unk_71024eb548::Flag::_1), on);
}

// NON_MATCHING: operands of the `and` swapped (the original ANDs the loaded bits with the mask)
bool HorseBase::sub_7100E6BF00() const {
    if (!_b18)
        return false;
    return _b18->_8.isOnBit(Unk_71024eb548::Flag(Unk_71024eb548::Flag::_1));
}

void HorseBase::sub_7100E6BF3C(bool on) {
    if (!_b18)
        return;
    _b18->_8.changeBit(Unk_71024eb548::Flag(Unk_71024eb548::Flag::_2), on);
}

Rideable* HorseBase::getHorseOptionsMaybe() {
    return _b10;
}

RideableBase* HorseBase::m132() {
    return _b10;
}

Unk_7100e8b2b8* HorseBase::getMotorcyclePriorityStuffMaybe() {
    return _b10;
}

ksys::act::Actor* HorseBase::m31() {
    if (_b10)
        return _b10->sub_7100E8B644();
    return Actor::m31();
}

ksys::act::Actor* HorseBase::m48() {
    if (_b10)
        return _b10->sub_7100E8B6E0();
    return nullptr;
}

}  // namespace uking::act
