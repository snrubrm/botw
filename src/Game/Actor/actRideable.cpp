#include <cstdarg>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actHorseStrings.h"
#include <prim/seadFormatPrint.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseUnit.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::act {

Rideable::Rideable() = default;

Rideable::~Rideable() = default;

// NON_MATCHING: matrix snapshot stores and translation extraction use different registers and scheduling.
bool Rideable::m4(ksys::act::Actor* actor, sead::Heap* heap) {
    if (!RideableBase::m4(actor, heap))
        return false;
    if (!Unk_7100e8b2b8::m4(actor, heap))
        return false;
    const sead::Matrix34f matrix = RideableBase::mActor->getMtx();
    _1c4 = matrix;
    _200 = matrix;
    _1f4 = matrix.getTranslation();
    _230 = matrix.getTranslation();
    _23c.set(0.0f, -sead::Mathf::epsilon(), 0.0f);
    return true;
}

s32 Rideable::getCalmDownNum() const {
    return RideableBase::mActor->getParam()->getRes().mGParamList->getHorseUnit()->mCalmDownNum.ref();
}

// NON_MATCHING: the original clears _1bc / _1c0 with one 8-byte store at a 4-aligned address
void Rideable::m6() {
    Unk_7100e8b2b8::m6();
    _1bc = 0;
    _1c0 = 0;
    _248 = 0;
    _278 = 0;
    _279 = 0;
    _270.set(0.0f, 0.0f);
    _254 = -1.0f;
    _268 = 0;
    _260 = 0;
    _258.set(0.0f, 0.0f);
}

void Rideable::m24() {
    RideableBase::_8 &= ~0x400u;
}

bool Rideable::m44() {
    const Gear gear(_18._b == 0 ? _18._9 : _18._b);
    return int(gear) > 1;
}

Rideable::Gear Rideable::m23() {
    const Gear target(_168);
    const Gear gear(_18._b == 0 ? _18._9 : _18._b);
    if (int(target) <= 2 && int(gear) == int(target))
        return Gear(3);
    return gear;
}

HorseReins* Rideable::m40() {
    return nullptr;
}

void Rideable::m42(int a1) {}

void Rideable::sub_7100E7EAD8(s32 level, const char* format, ...) {
    std::va_list args;
    va_start(args, format);
    va_end(args);
}

bool Rideable::sub_7100E7ECC8() const {
    auto* world = ksys::world::Manager::instance();
    if (!world)
        return false;
    sead::Vector3f pos;
    RideableBase::mActor->getMtx().getTranslation(pos);
    const auto climate = world->getClimate(pos);
    if (climate == ksys::world::Climate::GerudoDesertClimate ||
        climate == ksys::world::Climate::GerudoDesertClimateLv2) {
        return true;
    }
    return false;
}

void Rideable::sub_7100E7EF1C() {
    xlinkSearchAndEmit(RideableBase::mActor, "Attached", 2, nullptr);
    xlinkSearchAndEmit(RideableBase::mActor, "mc_HorseSoothe", 2, nullptr);
}

f32 Unk_7100e8b2b8::procLink13() {
    return 0.0f;
}

void sub_7100E7F6FC(ksys::as::ASList* as_list, ksys::phys::CharacterController* controller, f32 scale) {
    sead::Vector3f dir = as_list->sub_710115D2D4();
    sead::Vector3f vel = as_list->sub_710115D3B8();
    const f32 length = dir.normalize();
    controller->sub_7100F5EDD8(1.0f);
    controller->sub_7100F5EDE0(0.0f);
    controller->sub_7100F5EDBC(dir);
    controller->sub_7100F5E7F0(length * 30.0f * scale);
    vel *= 30.0f;
    controller->sub_7100F5FB24(vel);
}

// NON_MATCHING: only register allocation and block layout differ (the clamp's branch polarity and
// the s0/s9 argument registers). The logic, order and calls match.
void sub_7100E7F4FC(ksys::as::ASList* as_list, ksys::phys::CharacterController* controller, f32 scale) {
    const sead::Vector3f& dir = as_list->sub_710115D2D4();
    const f32 x = dir.x;
    const f32 z = dir.z;
    sead::Vector3f forward;
    sead::Matrix34f mtx;
    controller->physicsXXXGetMtx_1(&mtx);
    forward.set(mtx.m[0][2], 0.0f, mtx.m[2][2]);
    forward.normalize();

    const f32 ax = sead::Mathf::abs(x);
    const f32 az = sead::Mathf::abs(z);
    f32 a;
    f32 b;
    f32 dominant;
    if (az >= ax) {
        a = 1.0f;
        b = z == 0.0f ? 0.0f : sead::Mathf::clamp(x / z, -1.0f, 1.0f);
        dominant = z;
    } else {
        b = 1.0f;
        a = x == 0.0f ? 0.0f : sead::Mathf::clamp(z / x, -1.0f, 1.0f);
        dominant = x;
    }
    controller->sub_7100F5EDD8(a);
    controller->sub_7100F5EDE0(b);
    controller->sub_7100F5EDBC(forward);
    controller->sub_7100F5E7F0(dominant * 30.0f * scale);
}

// 0x7100e74604 (CSV formatAnimalMoveString): the AS name of one animal move (`gear` 0 is the default
// "Wait" name, move type 0 ignores the type name).
// NON_MATCHING: same calls and order but the original keeps a separate StringPrintFormatter stack slot per branch
// (0xd0 frame); ours reuses one (0x90). The original's sead::BufferedSafeStringBase::format is the inline
// PrintFormatter version (see libwork), so the manual formatter is used here.
void formatAnimalMoveString(sead::BufferedSafeString* out, int move_type, u32 gear) {
    if (gear == 0) {
        out->copy(sUnk_7102603110);
    } else if (move_type == 0) {
        sead::StringPrintFormatter formatter(out);
        formatter << "Move_Gear%d";
        formatter, gear;
        formatter.flush();
    } else {
        sead::StringPrintFormatter formatter(out);
        formatter << "Move_%s_Gear%d" << AnimalMoveType::text(move_type);
        formatter, gear;
        formatter.flush();
    }
}

// 0x7100e74498 (CSV name): builds the animal move name table (called by loadAnimationDrivenSpeedAnimal).
// In actRideable.cpp so the builder stays out of line (the original wrapper is a 4-byte tail call).
void sub_7100E7449C();

void formatAnimalMoveStrings() {
    sub_7100E7449C();
}

}  // namespace uking::act
