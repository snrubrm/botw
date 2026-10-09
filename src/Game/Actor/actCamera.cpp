#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <mc/seadCoreInfo.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiActionBase.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Framework/frmWorkerSupportThreadMgr.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectCamera.h"
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
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_850, &accessor);
    return sub_7100791B00(accessor);
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
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_850, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    return Actor::prepareForPreDelete_();
}

int Camera::getCalcTiming() {
    return 1;
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
