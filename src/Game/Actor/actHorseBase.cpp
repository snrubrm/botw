#include "Game/Actor/actHorseBase.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actHorseObject.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/GameData/gdtManager.h"
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

bool HorseBase::shouldUnload(s32* a1) {
    if (_b10) {
        if (_b10->sub_7100E8BFF4() || _b10->sub_7100E8C018())
            return false;
        if (int(Unk_7100e8b2b8::Unk8(_b10->Unk_7100e8b2b8::_8 & 0xff)) != Unk_7100e8b2b8::Unk8::_0)
            return false;
        if (_b74.isOn(2))
            return false;
    }
    return shouldUnloadBecauseOfDistance(a1);
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

HorseBase::IsSpecialJobTypeResult HorseBase::isSpecialJobType_(ksys::act::JobType type) {
    const auto result = Actor::isSpecialJobType_(type);
    if (_b10)
        return IsSpecialJobTypeResult(_b10->sub_7100E8BB4C(int(result)));
    return result;
}

bool HorseBase::canWakeUp_() {
    return Actor::canWakeUp_();
}

bool HorseBase::sub_7100E68270() const {
    return getParam()->getRes().mGParamList->getHorse()->mIsDecoy.ref();
}

HorseBase::Nature HorseBase::sub_7100E68298() const {
    return Nature(getParam()->getRes().mGParamList->getHorse()->mNature.ref());
}

bool HorseBase::sub_7100E696D4() const {
    if (!_b10)
        return false;
    if (u8(_b10->Unk_7100e8b2b8::_8) != 3)
        return false;
    return _b40 == nullptr;
}

void HorseBase::sub_7100E6AD3C(f32 value) {
    _b10->m29(value);
}

f32 HorseBase::sub_7100E6AD4C() {
    return _b10->m31();
}

HorseReins* HorseBase::getReinsA() {
    return sead::DynamicCast<HorseReins>(_860.getProc(nullptr, nullptr));
}

HorseReins* HorseBase::getReinsB() {
    return sead::DynamicCast<HorseReins>(_870.getProc(nullptr, nullptr));
}

HorseReins* HorseBase::getReinsC() {
    return sead::DynamicCast<HorseReins>(_880.getProc(nullptr, nullptr));
}

HorseReins* HorseBase::getReinsB2() {
    return sead::DynamicCast<HorseReins>(_870.getProc(nullptr));
}

HorseReins* HorseBase::getReinsC2() {
    return sead::DynamicCast<HorseReins>(_880.getProc(nullptr));
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
    _b74.set(0x100);
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

// NON_MATCHING: store scheduling of the accessor init (strb [sp+0x18] hoisted) in blocks 2-5
void HorseBase::onPreDeleteStart_(PrepareArg& arg) {
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_840, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_1a);
    }
    _840.reset();
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_850, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_1a);
    }
    _850.reset();
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_860, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_1a);
    }
    _860.reset();
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_870, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_1a);
    }
    _870.reset();
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_880, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_1a);
    }
    _880.reset();
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

void HorseBase::onDeleteRequested_(DeleteReason reason) {
    Actor::onDeleteRequested_(reason);
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_840, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_1a);
    }
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_850, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_1a);
    }
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_860, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_1a);
    }
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_870, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_1a);
    }
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_880, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_1a);
    }
    if (x() == 9)
        ksys::gdt::Manager::instance()->setBool(false, "AnimalMaster_Existence");
}

void HorseBase::onPreFadeOutDelete() {
    Actor::onPreFadeOutDelete();
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_840, &accessor))
            accessor.deleteEx(ksys::act::BaseProc::DeleteReason::_0);
    }
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_850, &accessor))
            accessor.deleteEx(ksys::act::BaseProc::DeleteReason::_0);
    }
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_860, &accessor))
            accessor.deleteEx(ksys::act::BaseProc::DeleteReason::_0);
    }
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_870, &accessor))
            accessor.deleteEx(ksys::act::BaseProc::DeleteReason::_0);
    }
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_880, &accessor))
            accessor.deleteEx(ksys::act::BaseProc::DeleteReason::_0);
    }
    if (x() == 9)
        ksys::gdt::Manager::instance()->setBool(false, "AnimalMaster_Existence");
}

// NON_MATCHING: everything matches except the eight DynamicCast + x_17 forwards: the original tests the
// proc pointer a second time after the virtual call (`cbz x21; eor w8, w0, #1; tbnz w8`) where we emit
// a single `tbz w0`
void HorseBase::m117(ksys::act::Unk117* arg) {
    if (_b10 && !_b10->sub_7100E8B780(arg)) {
        if (auto* actor = sead::DynamicCast<HorseReins>(_860.getProc(nullptr, nullptr)))
            actor->x_17(arg);
        if (auto* actor = sead::DynamicCast<HorseReins>(_870.getProc(nullptr, nullptr)))
            actor->x_17(arg);
        if (auto* actor = sead::DynamicCast<HorseReins>(_880.getProc(nullptr, nullptr)))
            actor->x_17(arg);
        _b70.setBitOn(7);
        return;
    }

    if (arg->_0 == 3 && arg->_8) {
        for (int i = 0; i < 4; ++i) {
            auto* entry = arg->_8->mItems[i].mEntry;
            if (!entry)
                continue;
            if (entry->_10 == "HyruleCastle" && entry->_68 == "GanonDead") {
                _b70.setBitOn(6);
                break;
            }
        }
    }

    if (auto* actor = sead::DynamicCast<HorseObject>(_840.getProc(nullptr, nullptr)))
        actor->x_17(arg);
    if (auto* actor = sead::DynamicCast<HorseObject>(_850.getProc(nullptr, nullptr)))
        actor->x_17(arg);
    if (auto* actor = sead::DynamicCast<HorseReins>(_860.getProc(nullptr, nullptr)))
        actor->x_17(arg);
    if (auto* actor = sead::DynamicCast<HorseReins>(_870.getProc(nullptr, nullptr)))
        actor->x_17(arg);
    if (auto* actor = sead::DynamicCast<HorseReins>(_880.getProc(nullptr, nullptr)))
        actor->x_17(arg);
}


// NON_MATCHING: orr/and/csel operand order differs for the _b74 flag update and LodState bit select
bool HorseBase::sub_7100E6C094(bool on) {
    _b74.change(0x4000, on);
    const bool lod_flag = ((_b74.getDirect() >> 14) & 3) != 0;
    if (auto* lod = getLodState())
        lod->mFlags10.changeBit(6, lod_flag);
    return lod_flag;
}

// NON_MATCHING: orr/and/csel operand order differs for the _b74 flag update and LodState bit select
bool HorseBase::sub_7100E6C0E0(bool on) {
    _b74.change(0x8000, on);
    const bool lod_flag = ((_b74.getDirect() >> 14) & 3) != 0;
    if (auto* lod = getLodState())
        lod->mFlags10.changeBit(6, lod_flag);
    return lod_flag;
}

}  // namespace uking::act
