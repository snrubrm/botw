#include "Game/Actor/actCamera.h"
#include <basis/seadNew.h>
#include "Game/gameUnk_710246d058.h"
#include "Game/gameMaskController.h"
#include <heap/seadHeapMgr.h>
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/Awareness/actAwareness.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/World/worldManager.h"
#include "Game/Actor/actCameraUtil.h"
#include "Game/Actor/actEditCamera.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <mc/seadCoreInfo.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
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

// The D1 / D0 thunks for the second and third bases (0x710079248c .. 0x710079268c) are non-matching (m:
// they keep one more callee-saved register).
Camera::~Camera() = default;

ksys::act::BaseProc* Camera::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Camera(arg);
}

Camera::InitResult Camera::init_() {
    _1c0 = 5;
    {
        sead::Heap* heap = ksys::act::ActorHeapUtil::instance()->getBaseProcHeap();
        sead::ScopedCurrentHeapSetter setter(heap);
        auto* edit_camera = sead::DynamicCast<EditCamera>(
            ksys::act::ActorCreator::instance()->createActor("EditCamera", heap, nullptr, false, false));
        if (edit_camera) {
            edit_camera->sub_71007917CC(this);
            edit_camera->getActorFlags2().set(ActorFlag2::_2000);
            _850.acquire(edit_camera, false);
        }
    }
    _1080 = sub_7100923E74();
    const Unk_7100928644::Params params{0.01f, sead::Mathf::deg2rad(88.0f), sead::Mathf::deg2rad(84.0f),
                                        sead::Mathf::deg2rad(8.0f), sead::Mathf::deg2rad(12.0f)};
    _13a4.sub_7100928650(params);
    ksys::xlink::XLink::RebuildArg arg;
    arg.rootMtx = &mMtx;
    if (mXLink)
        mXLink->sub_7101230100(arg);
    ksys::sub_7100F40428(static_cast<Unk_7102459cc0*>(this));
    if (auto* root6 = Root6::getInstance())
        root6->sub_7100928838(this);
    return InitResult::Ok;
}

// NON_MATCHING: the last flag update is a csel in ours (branches in the original).
// Keeps bit 3 of _13fd as the previous bit 2 and sets bit 2 while controller key 13 is held.
void Camera::sub_7100796830() {
    if (_13fd & 4)
        _13fd |= 8;
    else
        _13fd &= ~8;
    _13fd &= ~4;
    auto* controller = MaskController::getControllerSafe(MaskController::ControllerIdx::_1);
    if (!controller)
        return;
    auto* mask_controller = sead::DynamicCast<Unk_710246d058>(controller);
    if (!mask_controller)
        return;
    if (mask_controller->playerCheckController(13))
        _13fd |= 4;
    else
        _13fd &= ~4;
}

// NON_MATCHING: the original computes &awareness->mLinks2 after the m148() argument (C++14 evaluation order;
// we build as C++17). Everything else matches.
void Camera::updatePositionMaybe() {
    if (_860._804.sub_710079ADC8(1))
        return;
    sub_7100796830();
    if (_10f8 != 1) {
        _10f8 = 0;
        return;
    }

    _860._0._30 = _860.sub_710079ADA0();
    _860._80e.sub_710079C1EC();
    if (_860._815[1] == 1)
        _860._80f.sub_710079C218();

    ksys::act::acc::PlayerBase accessor;
    sub_7100926A50(&accessor);
    if (accessor.hasProc() && accessor.m328())
        ksys::eft::searchAndEmitELink(this, "FireAreaEnter");

    if (_860._7fc.sub_710079C0CC(0x100) && ui::sub_7100A9C15C()) {
        if (auto* awareness = ksys::act::Awareness::instance())
            awareness->mLinks2.sub_7100D79640(m148(), 1, 0xffffffff);
    }
    if (!sub_7100926D24() && !_860._80c.isOnBit(0) && (_860._810 == 1 || _860._810 == 2))
        _860._810 = 0;
    if (_860.sub_710079C134(2) && _860._812 == 1)
        _860._812 = 0;
    if (auto* manager = ksys::world::Manager::instance()) {
        f32 dist = 1.0f;
        if (_860.sub_710079C0F4(&dist))
            manager->setFocusDist(dist);
    }
    _860.sub_710079AD90();
    _10f8 = 2;
    if (sub_7100922428())
        sub_710079691C();
}

void Camera::initMaybe() {
    _13fd &= ~0x80;
    if (mPhysics)
        mPhysics->sub_7100FBA9BC();
    if (auto* awareness = _548) {
        awareness->m8()->m9(0, 1.0f);
        awareness->m8()->m9(1, 0.0f);
        awareness->m8()->m9(2, 0.0f);
        awareness->m8()->m9(3, 0.0f);
    }
    _860.sub_710079AE30();
    _860.sub_710079AED0();
    _860._815[1] = 0;
    _860._817 = 0;
    _860._7fc.sub_710079B62C(0x100000);
    _860._804.sub_710079AE40(0x80000);
    _860._804.sub_710079AE40(0x100000);
    _860._7c0[0].reset();
    _860._7c0[1].reset();
    _860._81a = 0;
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

// NON_MATCHING: the original tests the sub_71009223C4 result with `cmp w0, #0` (ours `tst w0, #1`).
void Camera::someCalculation(const sead::Matrix34f& mtx, sead::Vector3f* at, sead::Vector3f* pos) {
    *pos = mtx.getTranslation() + sead::Vector3f::ey * 1.6f;
    sead::Vector3f dir(-mtx(0, 2), -mtx(1, 2), -mtx(2, 2));
    const f32 len = dir.length();
    if (len > 0.0f)
        dir *= 6.0f / len;
    *at = (sub_71009223C4() ? dir : -dir) + *pos;
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

// The bool argument is not read.
void Camera::m150(const sead::Vector3f* pos, const sead::Vector3f* at, f32 fovy, f32 roll, bool a5) {
    Unk_71009214b8 camera;
    camera = _860._0;
    camera._0 = *pos;
    camera._c = *at;
    camera._24 = fovy;
    camera._28 = roll;
    camera.sub_71009237BC();
    u32 error = 0;
    camera.sub_7100921CAC(&error);
    if (error != 0) {
        nullsub_4649();
        return;
    }
    _860._0 = _860._38 = _860._70 = _860._a8 = _860._e0 = camera;
    _860._7fc.sub_710079B62C(0x800);
    _860._7fc.sub_710079B62C(0x1000);
    _860._7fc.sub_710079B62C(0x2000);
    _860._818 |= 1;
    _860._150 = camera._c;
    sub_71007929E0();
    _10f8 = 0;
    _860.sub_710079BC8C();
}

// The bool argument is not read.
void Camera::m151(const sead::Vector3f* pos, const sead::Vector3f* at, bool a3) {
    Unk_71009214b8 camera;
    camera = _860._0;
    camera._0 = *pos;
    camera._c = *at;
    camera.sub_71009237BC();
    u32 error = 0;
    camera.sub_7100921CAC(&error);
    if (error != 0) {
        nullsub_4649();
        return;
    }
    _860._0 = _860._38 = _860._70 = _860._a8 = _860._e0 = camera;
    _860._7fc.sub_710079B62C(0x800);
    _860._7fc.sub_710079B62C(0x1000);
    _860._7fc.sub_710079B62C(0x2000);
    _860._818 |= 1;
    _860._150 = camera._c;
    sub_71007929E0();
    _10f8 = 0;
    _860.sub_710079BC8C();
}

// NON_MATCHING: the two fadd of the length have their operands swapped (y*y + x*x, then z*z + sum).
// The bool argument is not read.
void Camera::m153(const sead::Vector3f* pos, bool a2) {
    Unk_71009214b8 camera;
    camera = _860._0;
    camera._c = *pos;
    sead::Matrix34f mtx = sead::Matrix34f::ident;
    ksys::act::ActorLinkConstDataAccess accessor;
    sub_7100924BE4(&accessor);
    const auto& player_mtx = accessor.getActorMtx();
    if (!ksys::util::sub_71011F10F4(player_mtx))
        mtx = player_mtx;
    sead::Vector3f dir = -mtx.getBase(2);
    const f32 length = dir.length();
    if (length > 0.0f)
        dir *= 6.0f / length;
    camera._0 = dir + camera._c;
    camera.sub_71009237BC();
    u32 error = 0;
    camera.sub_7100921CAC(&error);
    if (error != 0) {
        nullsub_4649();
        return;
    }
    _860._0 = _860._38 = _860._70 = _860._a8 = _860._e0 = camera;
    _860._7fc.sub_710079B62C(0x800);
    _860._150 = camera._c;
    sub_71007929E0();
    _10f8 = 0;
    _860.sub_710079BC8C();
}

// The bool argument is not read.
void Camera::m154(f32 value, bool a2) {
    Unk_71009214b8 camera;
    camera = _860._0;
    camera._24 = value;
    camera.sub_71009237BC();
    u32 error = 0;
    camera.sub_7100921CAC(&error);
    if (error != 0) {
        nullsub_4649();
        return;
    }
    _860._0 = _860._38 = _860._70 = _860._a8 = _860._e0 = camera;
    _860._7fc.sub_710079B62C(0x800);
    _860._150 = camera._c;
    sub_71007929E0();
    _10f8 = 0;
    _860.sub_710079BC8C();
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
