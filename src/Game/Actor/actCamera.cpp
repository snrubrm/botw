#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "Game/Actor/actEditCamera.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <mc/seadCoreInfo.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiActionBase.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Framework/frmWorkerSupportThreadMgr.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectCamera.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ksys.h"

Unk_7102459708::Unk_7102459708(ksys::act::ai::ActionBase* owner) : mOwner(owner) {}

const ksys::res::GParamListObjectCamera* Unk_7102459708::sub_7100791DE8() const {
    if (!mOwner)
        return nullptr;
    auto* actor = mOwner->getActor();
    if (!actor)
        return nullptr;
    auto* param = actor->getParam();
    if (!param)
        return nullptr;
    auto* list = param->getRes().mGParamList;
    if (!list)
        return nullptr;
    return list->getCamera();
}

void uking::act::Camera::requestCameraPack(const Unk_7100791b1c& request) {
    auto& slot = _860._5a0[sead::CoreInfo::getPlatformCoreId(sead::CoreInfo::getCurrentCoreId())];
    if (slot._58 < request._58)
        slot.sub_7100791BAC(request);
}

void uking::act::Camera::sub_710079565C() {
    if (!(_13fd & 0x20))
        _13fd |= 0x20;
    const f32 far = _860.sub_710079AE60();
    _860._118._34 = far;
    _860._e0._34 = far;
    _860._a8._34 = far;
    _860._70._34 = far;
    _860._38._34 = far;
    _860._0._34 = far;
    updateMatrix(true);
    _860._118 = _860._e0;
}

bool uking::act::Camera::sub_7100795F40(f32** out) {
    if (!out)
        return false;
    *out = &_1230[sead::CoreInfo::getPlatformCoreId(sead::CoreInfo::getCurrentCoreId())];
    return true;
}

uking::act::Camera* Unk_7102459708::getCamera() const {
    if (!mOwner)
        return nullptr;
    auto* actor = mOwner->getActor();
    if (!actor)
        return nullptr;
    return sead::DynamicCast<uking::act::Camera>(actor);
}

uking::act::Camera* Unk_7102459708::getCameraActor() const {
    if (!mOwner)
        return nullptr;
    auto* actor = mOwner->getActor();
    if (!actor)
        return nullptr;
    return sead::DynamicCast<uking::act::Camera>(actor);
}

f32 Unk_7102459708::sub_7100791E44(f32 t) const {
    return sub_710092523C(sub_71009251C4(getCamera()), t);
}

namespace uking::act {

// NON_MATCHING: vector arithmetic scheduling and the two stack temporaries use different slots.
void Camera::sub_7100799770(const Unk_71009214b8& src, Unk_71009214b8* dst) {
    // The native in-place callers require the direction before dst changes the source state.
    const sead::Vector3f direction = src._0 - src._c;
    dst->_c = src._c + _860._1a0;
    Unk_7100922700 polar(direction);
    polar._4 = angleStuff(sub_7100924CAC(angleStuff(_860._1b8 + polar._4)));
    polar._8 = angleStuff(_860._1bc + polar._8);
    polar._0 = sub_7100924D40(polar._0 + _860._1c0);
    dst->_0 = dst->_c + polar.sub_7100923254();
}

// NON_MATCHING: vector arithmetic scheduling and the two stack temporaries use different slots.
void Camera::sub_710079984C(const Unk_71009214b8& src, Unk_71009214b8* dst) {
    // The native in-place callers require the direction before dst changes the source state.
    const sead::Vector3f direction = src._0 - src._c;
    dst->_0 = src._0 + _860._1a0;
    Unk_7100922700 polar(direction);
    polar._4 = angleStuff(sub_7100924CAC(angleStuff(_860._1b8 + polar._4)));
    polar._8 = angleStuff(_860._1bc + polar._8);
    dst->_c = dst->_0 - polar.sub_7100923254();
}

void Camera::sub_7100795C44() {
    if (_860._1c8 != 0) {
        _860._0 = _860._38 = _860._70 = _860._a8 = _860._e0;
        _860._150 = _860._0._c;
        _1240.sub_71009298C4();
    } else {
        if (_860._1cc != 0)
            sub_7100799770(_860._0, &_860._0);
        else
            sub_710079984C(_860._0, &_860._0);
        _860._0._24 = sub_7100924D50(_860._0._24 + _860._1c4);
    }
    _860.sub_710079AEE0();
}

void Camera::sub_7100795E08(const Unk_71009214b8& src, Unk_71009214b8* dst) {
    *dst = src;
    if (_860._1cc != 0)
        sub_7100799770(src, dst);
    else
        sub_710079984C(src, dst);
    dst->_24 = sub_7100924D50(src._24 + _860._1c4);
}

bool Camera::sub_7100792360(void*) {
    sub_7100793924();
    sub_7100793BD8();
    return true;
}

Unk_7100928644::Unk_7100928644() : _0(0), _4(0), _8(0), _c(0), _10(0), _14(0) {}


bool sub_710079BE9C(int idx) {
    return idx < 1;
}

Unk_710079a8e8::~Unk_710079a8e8() = default;

void Camera::sub_71007953C8() {
    if (sub_7100922078())
        return;
    const f32 rate = sub_710092523C(Unk_7102459cc0::_8, 0.6f);
    _860._0._28 += rate * (0.0f - _860._0._28);
}

EditCamera::CameraNames* Camera::sub_7100795414() {
    if (!_850.hasProc())
        return nullptr;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_850, &accessor);
    return sub_7100791B00(accessor);
}

// Takes the camera pack request with the highest priority (the first one on ties) and clears all of them.
void Camera::sub_7100795518() {
    auto& requests = _860._5a0;
    s32 idx = 0;
    s32 priority = requests[0]._58;
    if (priority < requests[1]._58) {
        idx = 1;
        priority = requests[1]._58;
    }
    if (priority < requests[2]._58)
        idx = 2;
    _860._530.sub_7100791BAC(requests(idx));
    for (auto& request : requests)
        request.sub_7100791B88();
}

// NON_MATCHING: the original keeps the address of the chosen string pointer and loads it at one shared exit.
// The camera child name: the requested camera pack, else "DefaultIndoor_031" when the player is indoors (outside
// main field dungeons and Hyrule Castle), else "Default".
const char* Camera::sub_710079558C() {
    if (!_860._530._0.isEmpty())
        return _860._530._0.cstr();
    ksys::act::acc::PlayerBase accessor;
    sub_7100926A50(&accessor);
    if (!ksys::StageInfo::sIsMainFieldDungeon && !ksys::gdt::getFlag_IsInHyruleCastleArea(false) &&
        (accessor.x_33() || accessor.x_35())) {
        return sUnk_71024741b0;
    }
    return sUnk_71024741A8;
}

void Camera::sub_71007929E0() {
    _860._0 = _860._38 = _860._70 = _860._a8 = _860._e0;
    _860._150 = _860._0._c;
    _1240.sub_710092A83C();
    _860.sub_710079AEE0();
    _860._7fc.sub_710079B62C(0x8000);
    _13f8 = 0;
    _13fd &= ~0x80;
    _860._7c0[!(_860._81a & 1)].reset();
}

void Camera::sub_7100799920() {}

Camera* Camera::m148() {
    return this;
}

Camera* Camera::m149() {
    return this;
}

void Camera::m155(f32 degrees) {
    m154(sead::Mathf::deg2rad(degrees), true);
}

sead::Vector3f Camera::m156() {
    return {_860._e0.sub_7100921C04(), _860._e0.sub_7100921C50(), _860._e0.sub_7100921C98()};
}

void Camera::m157(void* a1, const sead::Matrix34f& mtx) {
    _1088 = a1;
    _1090 = mtx;
}

void Camera::x_1(u8) {
    _860._72c._4.save(_860);
    _860._7b4.sub_710079A884();
}

void Camera::sub_7100795C38(u8) {
    _860._7b4.sub_710079A8BC();
}

void Camera::setSunazarashiTurnParam(const f32& value) {
    _860.sub_710079BDC4(value);
}

void* Camera::m158() {
    return _1088;
}

sead::Matrix34f* Camera::m159() {
    return &_1090;
}

void Camera::m160() {
    if (sub_7100922428())
        return;
    sub_7100793924();
}

void Camera::m161() {
    if (sub_7100922428())
        return;
    sub_7100793BD8();
}

void Camera::sub_7100793DB4() {
    sead::Vector3f target = _860._0._c;
    ksys::act::acc::PlayerBase accessor;
    sub_7100926A50(&accessor);
    if (accessor.hasProc()) {
        const sead::Vector3f& look_at = accessor.getLookAtPosForCamera();
        if (!ksys::util::sub_71011F1040(look_at))
            target = look_at;
    }
    _860._170 = true;
    _860._164 = target;
    m153(&target, false);
    updateMatrix(true);
}

void Camera::sub_7100793D88() {
    sub_7100793DB4();
    _860._804.sub_710079AE20(0x80000);
}

void Camera::m162() {
    _860._804.sub_710079AE20(1);
}

bool Camera::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    if (sub_7100922080() >= 1)
        _13d8.allocBuffer(sub_7100922080(), heap, 8);
    return true;
}

void Camera::onPreDeleteStart_(PrepareArg& arg) {
    _13d8.freeBuffer();
}

Camera::PreDeletePrepareResult Camera::prepareForPreDelete_() {
    _13fe = 1;
    if (auto* root = Root6::getInstance())
        root->sub_7100928854(this);
    ksys::sub_7100F40428(nullptr);
    if (_850.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_850, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    return Actor::prepareForPreDelete_();
}

int Camera::getCalcTiming() {
    return 1;
}

void Camera::calcMaybe() {
    if (_860._804.sub_710079ADC8(1))
        return;
    _860.sub_710079B16C();
    _860.sub_710079B2C4();
    _860.sub_710079B308(this);
    _860.sub_710079B3C8(this);
    _860.sub_710079B4F0();
    _860.sub_710079B4F4();
    _860.sub_710079BAE4();
    _860.sub_710079BBA8();
    _10f8 = 1;
}

void Camera::m73() {
    if (sub_7100922428())
        return;
    sub_710079691C();
}

void Camera::m75() {
    if (_860._804.sub_710079ADC8(1))
        return;
    if (sub_7100922428())
        _1421 = 1;
    else
        sub_71007970E0();
}

void Camera::m163() {
    if (_1420) {
        ksys::frm::WorkerSupportThreadMgr::instance()->waitForTask(1);
        _1420 = 0;
    }
}

void Camera::m164() {
    if (_1421) {
        sub_71007970E0();
        _1421 = 0;
        return;
    }
    sub_7100793F8C();
}

void* Camera::m165() {
    return _1088;
}

bool Camera::sub_7100794FD0() const {
    return _860._800.sub_710079C0CC(0x8000);
}

bool Camera::sub_710079614C() const {
    return (_13fd & 0xc) == 4;
}

bool Camera::sub_7100796164() const {
    return _13fd & 4;
}

}  // namespace uking::act
