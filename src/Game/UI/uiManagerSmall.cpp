#include <container/seadBuffer.h>
#include "Game/UI/euiCapturePane.h"
#include "Game/gameRuneMgr.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/UI/euiTraceGaugeControl.h"
#include "Game/UI/uiTimer.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiAnimator.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "Game/UI/uiManager.h"
#include "KingSystem/XLink/xlinkManager.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/System/SeadController.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/Utils/Thread/TaskThread.h"
#include "Game/UI/euiUIController.h"
#include "Game/gameGraphics.h"
#include "Game/gameRadarMgr.h"
#include "Game/gameRoot38.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiSwkbdMgr.h"
#include "Game/UI/uiUnk_71025d6560.h"
#include <cstddef>
#include <new>
#include <devenv/seadEnvUtil.h>
#include <heap/seadExpHeap.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Resource/resLoadRequest.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace uking::ui {

// The manager's static screen load / unload lists (native 0x71025f5f90; each list is a sead::Buffer of 12-byte
// entries whose first word is the ScreenId). The manager destructor unloads these lists.
namespace {
struct ScreenLoadEntry {
    s32 id;
    s32 _4;
    s32 _8;
};
struct ScreenLoadLists {
    u8 _0[0x170];
    sead::Buffer<ScreenLoadEntry> mListA;  // 0x170
    sead::Buffer<ScreenLoadEntry> mListB;  // 0x180
    sead::Buffer<ScreenLoadEntry> mListC;  // 0x190
    sead::Buffer<ScreenLoadEntry> mListD;  // 0x1a0
    sead::Buffer<ScreenLoadEntry> mListE;  // 0x1b0
    sead::Buffer<s32> mListF;              // 0x1c0
};
ScreenLoadLists sUnk_71025F5F90;
}  // namespace

// 0x7100a7b8cc
bool Manager::sub_7100A7B8CC(s32 id) {
    const s32 count = sUnk_71025F5F90.mListE.size();
    for (s32 i = 0; i < count; ++i) {
        if (sUnk_71025F5F90.mListE[i].id == id)
            return true;
    }
    return false;
}

// 0x7100a7b92c
bool Manager::sub_7100A7B92C(s32 id) {
    const s32 count = sUnk_71025F5F90.mListA.size();
    if (count < 1)
        return false;
    if (id > 0x4d)
        return true;
    for (s32 i = 0; i < count; ++i) {
        if (sUnk_71025F5F90.mListA[i].id == id)
            return true;
    }
    return false;
}

// 0x7100a7da38
void Manager::sub_7100A7DA38() {
    sub_7100AA8698();
    _64c28 = 1;
    _64c2c = 1;
    _64c30 |= 0x80000000002;
}

// 0x7100a7fe9c
void Manager::sub_7100A7FE9C() {
    _65387 = 0;
}

// 0x7100a7f0d0
void Manager::sub_7100A7F0D0() {
    mLocationResource.unload();
    if (checkLoadResource(&mLocationResource, "Map/MainField/Location.mubin"))
        parseLocations();
}

// 0x7100a7f13c
bool Manager::checkLoadResource(ksys::res::Handle* handle, const sead::SafeString& path) {
    if (handle->requestedLoad())
        handle->requestUnload2();
    if (handle->requestedLoad()) {
        handle->checkLoadStatus();
        return handle->isSuccess();
    }

    ksys::res::Handle::Status status = ksys::res::Handle::Status::NoFile;
    ksys::res::LoadRequest request;
    request.mRequester = "uiManager";
    request._22 = true;
    request._26 = false;
    sead::DynamicCast<sead::DirectResource>(handle->load(path, &request, &status));
    switch (status) {
    case ksys::res::Handle::Status::_1:
    case ksys::res::Handle::Status::SizeZero:
    case ksys::res::Handle::Status::_3:
        return false;
    case ksys::res::Handle::Status::_4:
    case ksys::res::Handle::Status::_5:
    case ksys::res::Handle::Status::_6:
    case ksys::res::Handle::Status::_7:
        return true;
    default:
        return false;
    }
}

// UI heap storage; the name is a placeholder.
sead::Heap* sUnk_71025f59d0;

sead::Heap* getHeap() {
    return sUnk_71025f59d0;
}

// 0x7100a6d344
// NON_MATCHING: the original keeps the two region compares branchy (b.eq-big after the first,
// b.ne-small after the second); ours if-converts the second test to a csel. Tried the || form below,
// if/else-if/else and the nested !=/== form, all with the RegionID::US/EU names - the second test
// always becomes a csel. All loads/stores/calls match.
void createUiHeap(sead::Heap* parent) {
    size_t size;
    if (sead::EnvUtil::getRegion() == sead::RegionID::US ||
        sead::EnvUtil::getRegion() == sead::RegionID::EU) {
        size = 0x1c00000;
    } else {
        size = 0x1b00000;
    }
    sUnk_71025f59d0 = sead::ExpHeap::create(size, "UiHeap", parent, 8,
                                            sead::Heap::cHeapDirection_Forward, true);
    UI::instance()->_38 = sUnk_71025f59d0;
}

// 0x7100a6d3ec
void sub_7100A6D3EC() {}

SEAD_SINGLETON_DISPOSER_IMPL(Manager)


// 0x71009452d0
// NON_MATCHING: Mathf::min lowers to fminnm instead of the native fmin.
void sub_71009452D0(CookingInfo* out, s32 level) {
    out->_10 = sead::Mathf::min(f32(level), 3000.0f);
    out->level = s32(out->_10 / 200.0f);
}

// 0x71009452fc
// NON_MATCHING: Mathf::min lowers to fminnm instead of the native fmin.
void sub_71009452FC(CookingInfo* out, s32 level) {
    out->_10 = sead::Mathf::min(f32(level) * 200.0f, 2000.0f);
}

// 0x7100945320 / 0x7100945344: the two gauge ranges (value, maximum, default limit); names are guesses
void sub_7100945320(f32 value, f32 max) {
    Manager* manager = Manager::instance();
    manager->_50 = value;
    manager->_54 = max;
    manager->_58 = 3000.0f;
}

void sub_7100945344(f32 value, f32 max) {
    Manager* manager = Manager::instance();
    manager->_5c = value;
    manager->_60 = max;
    manager->_64 = 2000.0f;
}

// 0x7100a702e8 (CSV uiManager::x_1)
void Manager::sub_7100A702E8(eui::UIController* controller) {
    if (!controller)
        return;
    for (const auto& repeat : _649f8)
        controller->setPadRepeat(repeat.mask, repeat.delay_frame, repeat.pulse_frame);
}

// 0x7100a7f8e8
void Manager::sub_7100A7F8E8(const Unk_UiPinInfo* info) {
    if (info)
        _651e0 = info->_20;
}

// 0x7100a7f900
void Manager::sub_7100A7F900(Unk_UiPinInfo* info) const {
    if (info)
        info->_20 = _651e0;
}

// 0x7100a7f81c
bool Manager::sub_7100A7F81C() {
    auto lock = sead::makeScopedLock(_650f8);
    if (_650f0 > 0)
        return false;
    _650f0 = 1;
    Graphics::instance()->sub_7100F35DE8();
    return true;
}

// 0x7100a7f890
void Manager::sub_7100A7F890() {
    if (_651c4)
        _651ac.reset();
    _651c4 = true;
}

// 0x7100a7f8d4
void Manager::sub_7100A7F8D4() {
    _651c8.init(15.0f);
}

// 0x7100a7fdcc: advances the timer of state 2 (4.5 s; the value _653a0 = progress + 2 / 9, 1 after 150 frames)
// NON_MATCHING: block order (the original places the 150-frame case after the increment block)
void Manager::sub_7100A7FDCC() {
    if (_65387 == 1)
        return;
    if (_65387 == 2) {
        if (_653a4 >= 150) {
            _653a0 = 1.0f;
            _65387 = 2;
            return;
        }
    } else {
        _65388.init(4.5f);
        _653a4 = 0;
    }
    ++_653a4;
    _653a0 = _65388.getProgress() + 2.0f / 9.0f;
    _65387 = 2;
}

// 0x7100a7f918
bool Manager::sub_7100A7F918() const {
    return mTaskList.size() > 0;
}

void Unk_71025d6ac0::sub_7100968040() {
    _30.init(_48);
    _58.init(_70);
    ksys::xlink::Manager::instance()->setGlobalProperty(26, 10000.0f);
    ksys::xlink::Manager::instance()->setGlobalProperty(27, 0.0f);
}

void Unk_71025d6ac0::sub_71009680DC() {
    ksys::xlink::Manager::instance()->setGlobalProperty(26, 10000.0f);
    ksys::xlink::Manager::instance()->setGlobalProperty(27, 0.0f);
}

// Complete child 9BFCC4 passes this singleton and consumes the two bool predicates.
bool Unk_71025d6ac0::sub_71009684B4() const {
    return true;
}

bool Unk_71025d6ac0::sub_71009684BC() const {
    return false;
}

void Unk_71025d6ac0::sub_71009684D8() {
    _2a = _29;
    _29 = _4c < 1.0f && _4c >= 0.0f;
    if (_2c)
        _30.update();
    else
        _30.reset();
    _2c = false;
    _2b = RadarMgr::instance() ? RadarMgr::instance()->_52 : false;
}

void Unk_71025d6ac0::sub_710096809C() {
    ksys::xlink::Manager::instance()->setGlobalProperty(26, 10000.0f);
    ksys::xlink::Manager::instance()->setGlobalProperty(27, 0.0f);
}

bool Unk_71025d6ac0::sub_710096828C() const {
    return UiSubsys1::instance()->_38ac;
}

bool Unk_71025d6ac0::sub_71009682B4() const {
    return UiSubsys1::instance()->_38d8;
}

s32 Unk_71025d6ac0::sub_71009682CC() const {
    return UiSubsys1::instance()->_38a8;
}

void Unk_71025d6ac0::sub_71009682A4() {
    _29 = false;
    _4c = 1.0f;
}

void Unk_71025d6ac0::sub_71009684A0() {
    _4c = 1.0f;
    _29 = false;
    _2a = false;
    _58.reset();
}

// Const spelling is source inference from the read-only native bodies and callers.
bool Unk_71025d6ac0::sub_71009684C4() const {
    return _28;
}

void Unk_71025d6ac0::sub_71009684CC(bool value) {
    _28 = value;
}

bool Unk_71025d6ac0::sub_7100968550() const {
    return _2b;
}

bool Unk_71025d6ac0::sub_7100968564() const {
    return RadarMgr::instance() && _4c != 1.0f && !sub_7100AA8F74();
}

// 0x71009685c4 (placeholder name): sets _4c to the radar's _9c as a fraction of _50 (clamped to 0-1) while
// _74 is set; 1 when the UI Manager state is 1, there is no radar target or _9c is -1.
void Unk_71025d6ac0::sub_71009685C4() {
    f32 value = 0.0f;
    if (_74 != 0) {
        value = 1.0f;
        if (!sub_7100A9C110(1)) {
            auto* radar = RadarMgr::instance();
            if (radar && (!radar->_108.isEmpty() || _54) && radar->_9c != -1.0f) {
                const f32 ratio = radar->_9c / _50;
                value = sead::Mathf::clamp(ratio, 0.0f, 1.0f);
            }
        }
    }
    _4c = value;
}

bool Unk_71025d6ac0::sub_71009685BC() const {
    return _54;
}

void Unk_71025d6ac0::sub_710096867C(bool value) {
    _54 = value;
}

void Unk_71025d6ac0::sub_7100968688() {
    _58.reset();
}

void Unk_71025d6ac0::sub_7100968690() {
    _58.reset();
}

bool Unk_71025d6ac0::sub_7100968698() {
    return _58.updateAndCheckEnded();
}

f32 Unk_71025d6ac0::sub_7100968558() const {
    return 0.01f;
}

bool Unk_71025d6ac0::sub_71009686E8() const {
    return false;
}

// 0x71009686a0
bool Unk_71025d6ac0::sub_71009685AC(s32 value) const {
    return _74 == value;
}

void Unk_71025d6ac0::sub_71009686A0(s32 value) {
    _74 = value;
    _80 = 0;
}

// 0x71009686bc
void Unk_71025d6ac0::sub_71009686BC(s32 value) {
    _80 = 0;
    _84 = value * 2;
}

void Unk_71025d6ac0::sub_71009686AC() {
    _74 = 1;
    _80 = 0;
}

void Unk_71025d6ac0::sub_71009686C8() {
    ++_80;
}

bool Unk_71025d6ac0::sub_71009686D8() const {
    return _80 == _84;
}

// 0x7100a7fd64
// NON_MATCHING: the original reloads the count after the pointer store (it assumes the store may alias the count: no
// type-based aliasing between them), ours (also as sead::PtrArray::pushBack) increments it from the value already loaded.
void Manager::sub_7100A7FD64(nn::ui2d::Pane* pane) {
    if (pane && _652f0 < _652f4)
        _652f8[_652f0++] = pane;
}

// 0x7100a7fdb4
bool Manager::sub_7100A7FDB4() const {
    return _65387 != 0;
}

// 0x7100a76420 (CSV nullsub_6139)
void Manager::sub_7100A76420() {}

// 0x7100a79968
void Manager::sub_7100A79968() {
    switch (_64c2c) {
    case 2:
        sub_7100A79A04();
        _64c2c = 3;
        break;
    case 4:
        if (!sub_7100A79B38())
            return;
        _64c2c = 5;
        break;
    }
    if (!isPausedMaybe())
        _cc = -1;
}

// 0x7100a7a6c0 (CSV uiManager::__auto6)
void Manager::sub_7100A7A6C0(f32 value) {
    _653a8 = value;
    if (_649f0)
        sub_7100A6C0EC(_649f0, value);
}

// 0x7100a7ef28 (CSV uiManager::__auto7)
void Manager::sub_7100A7EF28() {
    _653a8 = 40.0f;
    if (_649f0)
        sub_7100A6C0EC(_649f0, 40.0f);
}

// 0x7100a7a6e4
void Manager::sub_7100A7A6E4(s32 a1) {
    _64b0c |= 1 << a1;
}

// 0x7100a7a704
void Manager::sub_7100A7A704(s32 a1) {
    if (a1 == 6)
        return;
    _64b10 |= 1 << a1;
}

// 0x7100a7c8d4
void Manager::sub_7100A7C8D4() {
    sub_7100AA8698();
    _64c28 = 1;
    _64c2c = 1;
}

// 0x7100a7c904
void Manager::sub_7100A7C904() {
    if (eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindowNoBtn))
        return;
    _64c28 = _64c24;
    _64c2c = 4;
    sub_7100A7A1A8();
    sub_7100AA8698();
    static_cast<ksys::SeadController*>(_649f0)->sub_7100D9D8DC(~u32(0));
    sub_7100A7E590();
    _64c30 &= ~u64(3);
}

// 0x7100a7c9ac
void Manager::sub_7100A7C9AC() {
    _64c2c = 8;
}

void Manager::sub_7100A7C9C0() {
    if (eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindowNoBtn))
        return;
    _64c28 = _64c24;
    _64c2c = 4;
    sub_7100A7A1A8();
    sub_7100AA8698();
    static_cast<ksys::SeadController*>(_649f0)->sub_7100D9D8DC(~u32(0));
    sub_7100A7E590();
    _64c30 &= ~u64(3);
}

void Manager::sub_7100A7CACC() {
    if (eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindowNoBtn))
        return;
    _64c28 = _64c24;
    _64c2c = 4;
    sub_7100A7A1A8();
    sub_7100AA8698();
    static_cast<ksys::SeadController*>(_649f0)->sub_7100D9D8DC(~u32(0));
    sub_7100A7E590();
    _64c30 &= ~u64(3);
}

// 0x7100a7ca68
void Manager::sub_7100A7CA68() {
    if (!Root38::instance()->hasAnyFlag() && !(_64c30 & 2))
        Root38::instance()->setFlag(2, true);
    _64c28 = 4;
    _64c2c = 1;
}

// 0x7100a7fba4
void Manager::sub_7100A7FBA4() {
    _65218 = _64c38 == 7;
}

// 0x7100a7fdac
bool Manager::sub_7100A7FDAC() {
    return false;
}

// 0x7100a7a4c0
void Manager::sub_7100A7A4C0() {
    sub_7100A7A4C4();
}

// 0x7100a7b994
int Manager::handleMessage(const ksys::Message* message) {
    const u32 broker = message->getBrokerId();
    if (broker - 2 <= 2)
        return sub_7100A7B9E8(*message);
    return 0;
}

// 0x7100a6e76c
// NON_MATCHING: the screen-list unloads, the available singleton deletes, the texture / GPU memory frees and the
// task-list clear are reproduced; the four singleton deletes whose deleteInstance is not defined in our build
// (HorseColorInfoMgr, UiShopMgr, UiSubsys1, agl::detail::DynamicUniformBlock), the 0x65138 slot-0x20 call and the
// two untyped pointer deletes at 0x65170 / 0x65178 are left out until their classes are modelled.
Manager::~Manager() {
    for (s32 i = 0; i < sUnk_71025F5F90.mListA.size(); ++i)
        unloadScreen(sUnk_71025F5F90.mListA[i].id);
    _64c30 &= ~u64(0x0E000000);

    for (s32 i = 0; i < sUnk_71025F5F90.mListD.size(); ++i)
        unloadScreen(sUnk_71025F5F90.mListD[i].id);
    _64c30 &= ~u64(0x40000000);

    for (s32 i = 0; i < sUnk_71025F5F90.mListB.size(); ++i)
        unloadScreen(sUnk_71025F5F90.mListB[i].id);
    _64c30 &= ~u64(0x400000000);

    for (s32 i = 0; i < sUnk_71025F5F90.mListC.size(); ++i)
        unloadScreen(sUnk_71025F5F90.mListC[i].id);
    _64c30 &= ~u64(0x40000000000);

    for (s32 i = 0; i < sUnk_71025F5F90.mListE.size(); ++i) {
        if (sUnk_71025F5F90.mListE[i].id <= 0x4e)
            sub_7100AA09D8(sUnk_71025F5F90.mListE[i].id);
    }

    if (UiLowPrioThreadMgr::instance())
        UiLowPrioThreadMgr::deleteInstance();
    if (Unk_71025d6578::instance())
        Unk_71025d6578::deleteInstance();
    if (SwkbdMgr::instance())
        SwkbdMgr::deleteInstance();
    if (Unk_71025d6560::instance())
        Unk_71025d6560::deleteInstance();
    if (PauseMenuDataMgr::instance())
        PauseMenuDataMgr::deleteInstance();
    if (Unk_71025d69f0::instance())
        Unk_71025d69f0::deleteInstance();

    if (mLocationResource.requestedLoad())
        mLocationResource.requestUnload2();
    if (_64bd0.requestedLoad())
        _64bd0.requestUnload2();
    _65140.deleteGPUMemBlock();
    mTextureData.getImagePtr().deleteGPUMemBlock();
    if (_65158) {
        operator delete[](_65158);
        _65158 = nullptr;
    }
    if (_65160) {
        operator delete[](_65160);
        _65160 = nullptr;
    }

    sead::ListNode* node = mTaskList.firstNode();
    while (node) {
        sead::ListNode* next = node->next();
        mTaskList.eraseNode(node);
        auto* entry = reinterpret_cast<ManagerTaskEntry*>(
            reinterpret_cast<u8*>(node) - offsetof(ManagerTaskEntry, mNode));
        entry->mNextFree = mTaskList.mFreeList;
        mTaskList.mFreeList = entry;
        node = next;
    }
    if (mTaskList.mBuffer)
        operator delete[](mTaskList.mBuffer);
    mTaskList.mCapacity = 0;
    mTaskList.mFreeList = nullptr;
    mTaskList.mBuffer = nullptr;
}

}  // namespace uking::ui

// 0x71025d64e8 / 0x71025d64ec / 0x71025d6540 (placeholder names): flags of the gauge TU (direct adrp loads:
// hidden visibility)
KSYS_VISIBILITY_HIDDEN bool sUnk_71025d64e8;
KSYS_VISIBILITY_HIDDEN bool sUnk_71025d64ec;
KSYS_VISIBILITY_HIDDEN bool sUnk_71025d6540;

// 0x71009452c4
bool sub_71009452C4() {
    return sUnk_71025d64ec;
}

// 0x7100945364
Unk_7102474fd8::Unk_7102474fd8() = default;

// 0x7100945db8
void Unk_7102474fd8::sub_7100945DB8() {
    if (!uking::ui::sub_7100AA8F30()) {
        sUnk_71025d64e8 = false;
        sUnk_71025d64ec = false;
        sUnk_71025d6540 = false;
    }
    if (_8 && _8->_91 != 0) {
        for (auto& pane : _60)
            pane._db = true;
    }
    (this->*_a0)();
    _9d = false;
    _9e = false;
}

// 0x7100945c98
void Unk_7102474fd8::sub_7100945C98(bool a1) {
    if (_8 && (_8->_91 == 1 || _8->_91 == 2))
        _8->startAnimCloseImpl_(false, false);
    if (a1 && _8 && _8->_91 != 0)
        _8->startAnimCloseImpl_(false, true);
}

// 0x7100945ea4
void Unk_7102474fd8::sub_7100945EA4() {
    if (!_10)
        return;
    if (!_10->_6c) {
        _98 = _10->mTracingSpeed;
        return;
    }
    if (_10->_50 >= _98)
        _10->set50(_98);
    else if (!sead::Mathf::equalsEpsilon(_10->_50, _10->mTracingSpeed))
        return;
    sub_7100945D84(false);
}

// 0x7100945d70
void Unk_7102474fd8::sub_7100945D70() {
    if (_10)
        _10->setTracingSpeed(_10->_50);
}

// 0x7100945d98
bool Unk_7102474fd8::sub_7100945D98() const {
    return _10 && _10->_6c;
}

// 0x7100946604
void Unk_7102474fd8::sub_7100946604(u8 alpha) {
    if (_8 && _8->mPane)
        _8->mPane->SetAlpha(alpha);
}

// 0x71009465d8
void Unk_7102474fd8::sub_71009465D8(const sead::Vector2f& position) {
    if (_8 && _8->mPane)
        _8->mPane->SetPosition(nn::util::Float3{position.x, position.y, 0.0f});
}

// 0x710094661c
void Unk_7102474fd8::sub_710094661C(f32 scale) {
    if (_8 && _8->mPane)
        _8->mPane->SetScale({scale, scale});
}

// 0x7100946664
void Unk_7102474fd8::sub_7100946664(bool max) {
    if (!_50)
        return;
    if (max)
        _50->StopAtMax();
    else
        _50->StopAtMin();
}

// 0x7100946898
void Unk_7102474fd8::sub_7100946898() {
    _28->PlayAuto(1.0f);
}

// 0x71009468ac
void Unk_7102474fd8::sub_71009468AC() {
    _58->PlayAuto(1.0f);
}

// 0x710094574c
void Unk_7102474fd8Gauge::sub_710094574C(f32 value) {
    if (_10) {
        f32 speed = 0;
        uking::ui::sub_7100AA8FCC(&speed, value, m8());
        _10->setTracingSpeed(speed);
    }
}

// 0x71009457b4
void Unk_7102474fd8Gauge::sub_71009457B4(f32 value) {
    if (_10) {
        f32 shown = 0;
        uking::ui::sub_7100AA8FCC(&shown, value, m8());
        _10->set50(shown);
    }
}

// 0x7100945d84
void Unk_7102474fd8::sub_7100945D84(bool value) {
    if (_10)
        _10->_6c = value;
}

// 0x7100946864
s32 Unk_7102474fd8::sub_7100946864() const {
    s32 count = 1;
    if (_8c > 1000.0f) {
        f32 rest = _8c;
        do {
            rest += -1000.0f;
            ++count;
        } while (rest > 1000.0f);
    }
    return count;
}

// 0x71009468e0
void Unk_7102474fd8::sub_71009468E0(f32 frame) {
    _58->Stop(frame);
}

// NON_MATCHING: we compile as C++17, so `_18->Stop(...)` loads the callee before evaluating the frame (the original
// reads _18 again after GetFrameSize); the trace gauge locals share one stack slot in ours
// 0x7100945f78
void Unk_7102474fd8Gauge::sub_7100945F78() {
    const f32 value = m7();
    if (_88 != _8c)
        _88 = _8c;
    _8c = value;
    const f32 rate = m9(value);
    _18->Stop(rate * _18->GetFrameSize());
    const f32 current = m6();
    _90 = current;
    _94 = current;
    if (_10) {
        f32 speed = 0;
        uking::ui::sub_7100AA8FCC(&speed, current, m8());
        _10->setTracingSpeed(speed);
    }
    if (_10) {
        f32 shown = 0;
        uking::ui::sub_7100AA8FCC(&shown, _90, m8());
        _10->set50(shown);
    }
    sub_7100946318();
    if (_38)
        _38->StopAtMin();
    if (_48)
        _48->StopAtMin();
}

// 0x71009461b8
void Unk_7102474fd8Gauge::sub_71009461B8() {
    if (m10()) {
        auto* rune = uking::RuneMgr::instance();
        bool open;
        if ((rune->_94 & 0x80) && !(rune->_90 & 0x20))
            open = true;
        else if ((rune->_94 & 0x20) && !(rune->_90 & 0x10))
            open = rune->isSelectedRune(5);
        else
            open = false;
        sub_7100946740(open, true);
    } else {
        sub_7100945C98(uking::ui::sub_7100AA8F50() || !uking::ui::sub_7100AA948C());
    }
}

// 0x7100946740
void Unk_7102474fd8Gauge::sub_7100946740(bool a1, bool update) {
    if (!_8)
        return;
    if (_8->_91 == 3 || _8->_91 == 0) {
        if (update)
            sub_7100945F78();
        _8->sub_7100BDDE7C(false, 0, true);
        m12();
    }
    if (a1 && !(_8 && _8->_91 == 2))
        _8->sub_7100BDDE7C(false, 1, true);
}

// 0x71009479c4
Unk_7102474fd8::~Unk_7102474fd8() {
    _60.freeBuffer();
}

// 0x71009468f0
void Unk_7102475050::m4() {
    Unk_7102474fd8::m4();
    if (_8) {
        _b8 = _8->tryCreateAnimatorAuto("Born", false);
        if (_b8)
            _b8->StopAtMin();
        _c0 = _8->tryCreateAnimatorAuto("Dead", false);
        if (_c0)
            _c0->StopAtMax();
    }
    _c8.setToEnd();
}

// 0x71009469b4
bool Unk_7102475050::m10() {
    auto* info = uking::act::PlayerInfo::instance();
    if (!info)
        return false;
    auto* player = info->getPlayer();
    if (!player || player->_cf0.isOnBit(19) || player->sub_710084A6B8())
        return false;
    if (uking::ui::sub_7100AA8F30())
        return sUnk_71025d64e8;
    if (!_9e && uking::act::PlayerInfo::instance()->getPlayer()->m139() < 1.0f)
        return false;
    if (_9d)
        return false;
    return !_c8.isDone();
}

// 0x7100946a5c
bool Unk_7102475050::sub_7100946A5C() const {
    return !_c8.isDone();
}

// 0x7100946688
void Unk_7102475050::m11() {
    if (!_30)
        return;
    const f32 value = _8c;
    if (value != _90) {
        _c8.init(1.0f);
        _c8.update();
        return;
    }
    const f32 shown = _94;
    _c8.update();
    if (shown == value || uking::ui::sub_7100AA8F10() || !_8 || _8->_91 != 2 || _30->mRate != 0.0f)
        return;
    _30->PlayAuto(1.0f);
}

// 0x71009467d8
void Unk_7102475050::m12() {
    if (_8c == _90) {
        _c8.setToEnd();
        if (_a0 == &Unk_7102474fd8::sub_710094581C && !uking::ui::sub_7100AA8F30() && !_9e)
            _8->startAnimCloseImpl_(false, true);
    }
}

// 0x7100946968
f32 Unk_7102475050::m6() {
    return uking::ui::sub_7100A9B6D0();
}

// 0x710094696c
f32 Unk_7102475050::m7() {
    return uking::ui::sub_7100A9B6F0();
}

// 0x7100946970
f32 Unk_7102475050::m8() {
    return 3000.0f;
}

// 0x710094697c
// NON_MATCHING: the clamp compiles to branches instead of fcsel / fccmp
f32 Unk_7102475050::m9(f32 value) {
    const f32 rate = (value + -1000.0f) / 2000.0f;
    return rate < 0.0f ? 0.0f : (rate > 1.0f ? 1.0f : rate);
}

// 0x7100947318
bool Unk_71024750c8::m10() {
    auto* info = uking::act::PlayerInfo::instance();
    if (!info || !info->getPlayer())
        return false;
    if ((uking::RuneMgr::instance()->_90 & 0x10) && uking::RuneMgr::instance()->isSelectedRune(5))
        return false;
    if (uking::RuneMgr::instance()->_90 & 0x20)
        return false;
    if (!(_90 > 0 || _8c > 0 || !_10 || !sead::Mathf::equalsEpsilon(_10->_50, _10->mTracingSpeed)) && !_9c)
        return false;
    if (uking::ui::sub_7100AA8F30())
        return sUnk_71025d64ec;
    if (!_9e && uking::act::PlayerInfo::instance()->getPlayer()->m139() < 1.0f)
        return false;
    return !_9d;
}

// 0x71009472cc
f32 Unk_71024750c8::m6() {
    return uking::ui::sub_7100A9B710();
}

// 0x7100947288
// NON_MATCHING: compare scheduling (the original selects without a branch)
f32 Unk_71024750c8::m7() {
    static const f32 sLimits[] = {1000.0f, 2000.0f};
    const f32 value = m6();
    return value > 0.0f ? sLimits[!(value <= 1000.0f)] : 0.0f;
}

// 0x7100947244
void Unk_71024750c8::m4() {
    Unk_7102474fd8::m4();
    if (_40)
        _40->StopAtMin();
    _40 = nullptr;
}

// 0x710094727c
f32 Unk_71024750c8::m8() {
    return 2000.0f;
}

// 0x71009472d0
f32 Unk_71024750c8::m9(f32 value) {
    if (_8c > 1000.0f) {
        s32 count = 1;
        f32 rest = _8c;
        do {
            rest += -1000.0f;
            ++count;
        } while (rest > 1000.0f);
        return static_cast<f32>(count) - 1.0f;
    }
    return 0.0f;
}

// 0x710094784c
Unk_7102475050::~Unk_7102475050() = default;

// NON_MATCHING: placeholder destructor (keeps the vtable emitted); the original's slot is the base D2 0x71009479c4
// and its D0 is 0x71009479d8.
Unk_71024750c8::~Unk_71024750c8() = default;

// 0x7100a7f290
Unk_710249c5e8::~Unk_710249c5e8() {
    _8 = -1;
    _10 = nullptr;
    _18 = nullptr;
    _20 = 0;
}

// 0x7100a7ef58
Unk_710249c5b8::~Unk_710249c5b8() {
    _28 = nullptr;
    _30 = -1;
    _34 = 0;
    _38 = false;
    _3c = -1;
}

// 0x7100a800f0
Unk_710249c558::~Unk_710249c558() {
    _8.clear();
    _60 = -1;
}

// 0x7100a80270
Unk_710249c588::~Unk_710249c588() {
    _8.clear();
    _60 = -1;
}

// 0x7100a80550
Unk_710249c630::~Unk_710249c630() = default;

sead::DirectResource* Unk_710249c630::newResource_(sead::Heap* heap_, s32 alignment) {
    sead::Heap* heap = ksys::util::getHeapOrCurrentHeap(heap_);
    sead::ScopedCurrentHeapSetter setter{heap};
    return new (heap, alignment, std::nothrow_t{}) Unk_710247e8c0;
}





