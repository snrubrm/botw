#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameSaveSystem.h"
#include "KingSystem/AOC/aocManager.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/ActorSystem/actBaseProcAccessor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/System/CameraS1.h"
#include <geom/seadRay.h>
#include <gfx/seadViewport.h>
#include <aal/aalGroup.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalSoundParam.h>
#include <aal/aalSystemAccessor.h>

bool sub_710092DA58(sead::PerspectiveProjection* projection) {
    if (auto* camera = sub_7100923E74()) {
        sub_7100D8AED0(camera, projection);
        return true;
    }
    return false;
}

bool sub_710092DA88(sead::PerspectiveProjection* projection) {
    if (auto* camera = sub_7100923E74()) {
        sub_7100D8AED0(camera, projection);
        return true;
    }
    return false;
}

const sead::Viewport* sub_710092DAB8() {
    if (auto* mgr = ksys::CameraMgr::instance())
        return mgr->sub_7100D8C4C8();
    return nullptr;
}

const sead::Viewport* sub_710092DAD0() {
    if (auto* mgr = ksys::CameraMgr::instance())
        return mgr->sub_7100D8C4C8();
    return nullptr;
}

void sub_710092DAE8(ksys::act::BaseProcAccessor* accessor) {
    if (!accessor)
        return;
    if (auto* root = uking::act::Root6::instance())
        root->sub_7100927198(accessor);
}

void getRoot6SomeActor(ksys::act::BaseProcAccessor* accessor) {
    if (!accessor)
        return;
    if (auto* root = uking::act::Root6::instance())
        root->sub_71009287CC(accessor);
}

void sub_710092DB30(ksys::act::BaseProcLink* link) {
    if (!link)
        return;
    if (auto* root = uking::act::Root6::getInstance())
        link->acquire(root->sub_71009285F0(), false);
}

void sub_710092DB74(uking::act::Camera** camera) {
    if (!camera)
        return;
    if (auto* root = uking::act::Root6::getInstance())
        *camera = root->sub_71009285F0();
}

ksys::util::Unk_7101EC6BAC sub_710092DBA4() {
    if (auto* root = uking::act::Root6::instance()) {
        if (auto* camera = root->sub_71009285F0())
            return camera->_139c;
    }
    return ksys::util::sUnk_7101EC6BAC;
}



bool sub_710092DC00() {
    auto* root = uking::act::Root6::instance();
    if (!root)
        return false;
    auto* camera = root->sub_71009285F0();
    if (!camera)
        return false;
    return camera->_860.sub_710079C120(1);
}

// 0x710092de00: complete destructor; 0x710092ded0: deleting destructor. The sb member is destroyed
// before the base sub-object that owns the state machine, so the bindings are released here after it
// in the original; see the NON_MATCHING note.
// NON_MATCHING: our flat class emits one base vtable store instead of the original's two (the
// original derives from an empty polymorphic class at +8 over the state-machine owner at +0x10), and
// the member is destroyed after the body rather than before it.
Unk_71024742f0::~Unk_71024742f0() {
    mStateMachine._0->m3(&mStateMachine.mPrevious);
    mStateMachine._0->m3(&mStateMachine.mCurrent);
}

// 0x710092e088: the state machine at +0x40 runs its current state.
void Unk_71024742f0::m5() {
    mStateMachine.run();
}

// 0x710092e090: sets the volume of the "World" sound group to 1.
void Unk_71024742f0::m6() {
    auto* group_mgr = aal::SystemAccessor::getGroupMgr();
    if (!group_mgr)
        return;
    if (auto* group = group_mgr->findGroup("World"))
        group->getParam().setVolume(1.0f);
}

// 0x710092e0e4 (slot m7): runs the title screen's open step, then the picture book screen's setup.
void Unk_71024742f0::m7() {
    if (auto* screen = sead::DynamicCast<uking::ui::ScreenTitle>(
            eui::ScreenMgr::instance()->getScreen(uking::ui::ScreenId::Title))) {
        if (screen->isClosed())
            screen->sub_7100A69670();
        else
            screen->sub_7100A69AEC();
    }
    uking::ui::sub_71009FA68C();
}

// NON_MATCHING: the inlined BitFlag8::isOnBit ANDs its operands in the other order (commutative).
// 0x710092e1a4 (slot m8): picks the next title state from the AoC version and the demo mode.
void Unk_71024742f0::m8() {
    auto* screen = sead::DynamicCast<uking::ui::ScreenTitle>(
        eui::ScreenMgr::instance()->getScreen(uking::ui::ScreenId::Title));
    if (!screen || !screen->sub_7100A69B6C())
        return;

    auto* aoc = ksys::aoc::Manager::instance();
    if (aoc && aoc->isVersionTooOld()) {
        mStateMachine.changeState(&uking::ui::sUnk_71025d25d8);
        return;
    }
    if (!aoc || u32(aoc->getVersion()) >> 8 <=
                     u32(ksys::gdt::getFlag_Option_LatestAoCVerPlayed(false)) >> 8) {
        mStateMachine.changeState(&uking::ui::sUnk_71025d26f8);
        return;
    }
    if (uking::ui::isE3DemoMode())
        mStateMachine.changeState(&uking::ui::sUnk_71025d26f8);
    else
        mStateMachine.changeState(&uking::ui::sUnk_71025d2638);
}

// 0x710092e2f8 (slot m11): opens the hard-mode screen and lets it take over.
void Unk_71024742f0::m11() {
    uking::ui::createAndLoadScreenIfNeededImpl(uking::ui::ScreenId::HardMode, nullptr);
    if (auto* screen = sead::DynamicCast<uking::ui::ScreenHardMode>(
            eui::ScreenMgr::instance()->getScreen(uking::ui::ScreenId::HardMode)))
        screen->sub_7100A0BAE4();
}

// 0x710092e838 (slot m27): tells the title screen to refresh its button state.
void Unk_71024742f0::m27() {
    if (auto* screen = sead::DynamicCast<uking::ui::ScreenTitle>(
            eui::ScreenMgr::instance()->getScreen(uking::ui::ScreenId::Title)))
        screen->sub_7100A69B28();
}

// NON_MATCHING: the original copies _3704 to the stack and reloads it for the test (a by-value state
// copy); ours compares the member directly.
// 0x710092e3b4 (slot m12): when the hard-mode screen has settled on its title state, save the
// "played hard mode" flag and move on.
void Unk_71024742f0::m12() {
    if (auto* screen = sead::DynamicCast<uking::ui::ScreenHardMode>(
            eui::ScreenMgr::instance()->getScreen(uking::ui::ScreenId::HardMode))) {
        if (screen->_3704 == 4) {
            ksys::gdt::setFlag_IsLastPlayHardMode(false, false);
            uking::SaveSystem::instance()->sub_71009145F8();
            mStateMachine.changeState(&uking::ui::sUnk_71025d2518);
        }
    }
}

// 0x710092e590 (slot m16): waits for the system window to be gone (or to leave its sub state).
void Unk_71024742f0::m16() {
    auto* screen = sead::DynamicCast<uking::ui::ScreenSystemWindow00>(
        eui::ScreenMgr::instance()->getScreen(uking::ui::ScreenId::SystemWindow00));
    if (!screen || (screen->_291 & 8))
        mStateMachine.changeState(&uking::ui::sUnk_71025d26f8);
}

// 0x710092e658 (slot m19): forgets the state index.
void Unk_71024742f0::m19() {
    _100 = 0;
}

// 0x710092e7fc (slot m24): resets the save options and moves on.
void Unk_71024742f0::m24() {
    uking::SaveSystem::instance()->sub_71009145F8();
    mStateMachine.changeState(&uking::ui::sUnk_71025d26f8);
}

// 0x710092e8e8 (slot m28): moves on once the title screen has finished its open animation.
void Unk_71024742f0::m28() {
    auto* screen = sead::DynamicCast<uking::ui::ScreenTitle>(
        eui::ScreenMgr::instance()->getScreen(uking::ui::ScreenId::Title));
    if (screen && screen->_3638)
        mStateMachine.changeState(&uking::ui::sUnk_71025d2758);
}

// 0x710092e9b4 (slot m31): tells the title screen that the stage state is done.
void Unk_71024742f0::m31() {
    if (auto* screen = sead::DynamicCast<uking::ui::ScreenTitle>(
            eui::ScreenMgr::instance()->getScreen(uking::ui::ScreenId::Title)))
        screen->sub_7100A69AE8();
}

// 0x710092e4b0 (slot m15): opens the system window in its "new hard-mode save" form.
void Unk_71024742f0::m15() {
    uking::ui::createAndLoadScreenIfNeededImpl(uking::ui::ScreenId::SystemWindow00, nullptr);
    if (auto* screen = sead::DynamicCast<uking::ui::ScreenSystemWindow00>(
            eui::ScreenMgr::instance()->getScreen(uking::ui::ScreenId::SystemWindow00))) {
        screen->m154(12, 0, nullptr);
        return;
    }
    mStateMachine.changeState(&uking::ui::sUnk_71025d26f8);
}

// 0x710092e660 (slot m20): walks the DLC window state (0x1e == opened, later == closing).
void Unk_71024742f0::m20() {
    if (_100 <= 0x1d) {
        ++_100;
        return;
    }
    if (_100 != 0x1e) {
        if (sead::DynamicCast<uking::ui::ScreenDLCWindow>(
                eui::ScreenMgr::instance()->getScreen(uking::ui::ScreenId::DLCWindow)))
            return;
        ksys::gdt::setFlag_Option_LatestAoCVerPlayed(ksys::aoc::Manager::instance()->getVersion(),
                                                    false);
        mStateMachine.changeState(&uking::ui::sUnk_71025d2698);
        return;
    }
    uking::ui::createAndLoadScreenIfNeededImpl(uking::ui::ScreenId::DLCWindow, nullptr);
    if (auto* screen = sead::DynamicCast<uking::ui::ScreenDLCWindow>(
            eui::ScreenMgr::instance()->getScreen(uking::ui::ScreenId::DLCWindow)))
        screen->sub_7100A05CB4(true);
    ++_100;
}

// NON_MATCHING: ray and projection stack slots and Boolean return scheduling differ.
bool sub_710092DC38(const sead::Vector2f& screen, sead::Vector3f* direction) {
    sead::PerspectiveProjection projection;
    if (auto* camera = sub_7100923E74())
        sub_7100D8AED0(camera, &projection);
    const sead::Viewport* viewport = nullptr;
    if (auto* mgr = ksys::CameraMgr::instance())
        viewport = mgr->sub_7100D8C4C8();
    auto* camera = sub_7100923E74();
    bool success = false;
    if (viewport && camera) {
        sead::Ray3f ray(sead::Vector3f::zero, sead::Vector3f::ex);
        viewport->unprojectRay(&ray, screen, projection, *camera);
        *direction = ray.getDir();
        success = true;
    }
    return success;
}
