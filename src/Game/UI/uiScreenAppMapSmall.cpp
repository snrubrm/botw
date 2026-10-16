#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/gameSceneSubsys14.h"
#include "KingSystem/System/Patrol.h"
#include "Game/gameGearMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/euiTextSearcher.h"
#include "Game/UI/euiMessageMgr.h"
#include <gfx/nin/seadGraphicsNvn.h>
#include <nn/ui2d/BuildTypes.h>
#include "Game/UI/uiScreenControlCreators.h"
#include "Game/UI/uiScreenChildStates.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/euiAnimator.h"
#include <layer/aglLayer.h>
#include <layer/aglRenderer.h>

namespace uking::ui {

// 0x71009d9c40
void ScreenAppCamera::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_71024803b8 creator(mButtonGroup, &mControls, &_50);
    auto* messages = eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_());
    eui::TextSearcher searcher(messages, mTagProcessor);
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, sead::GraphicsNvn::instance()->getNnDevice(), accessor, &creator, &searcher,
                           nn::ui2d::Layout::BuildOption{}, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x71009e0e24
void ScreenAppMapDungeon::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_7102481078 creator(mButtonGroup, &mControls, &_50);
    auto* messages = eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_());
    eui::TextSearcher searcher(messages, mTagProcessor);
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, sead::GraphicsNvn::instance()->getNnDevice(), accessor, &creator, &searcher,
                           nn::ui2d::Layout::BuildOption{}, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x71009ea030
bool ScreenAppMap::sub_71009EA030() const {
    if (_3c98)
        return _3c98->mController.sub_71009CBFA4();
    return true;
}

// 0x71009e0df8
bool ScreenAppMapDungeon::sub_71009E0DF8() const {
    if (mSensorChild)
        return mSensorChild->mController.sub_71009CBFA4();
    return true;
}


// 0x71009ef488
// NON_MATCHING: position load and negation order.
void ScreenAppMap::sub_71009EF488(const sead::Vector3f* pos, s32 scale_level) {
    if (_3610) {
        UiSubsys1::instance()->sub_7100968AF8(0);
        _3ad4 = pos->x;
        _3ad8 = -pos->z;
        _3adc = scale_level;
    }
}

// 0x71009ef57c: the input speed is unused; the controller is always started at speed 1.
void ScreenAppMap::sub_71009EF57C(f32, s32 type) {
    if (_3c90) {
        switch (type) {
        case 0:
            _3c90->sub_71009C1474(1.0f, 0);
            break;
        case 1:
            _3c90->sub_71009C1474(1.0f, 1);
            break;
        }
    }
}

// 0x71009ef5a8
bool ScreenAppMap::sub_71009EF5A8(s32 type) {
    if (_3c90) {
        switch (type) {
        case 0:
            return _3c90->sub_71009C1814(0);
        case 1:
            return _3c90->sub_71009C1814(1);
        }
    }
    return true;
}

// 0x71009ef4ec (CSV unnamed)
void ScreenAppMap::sub_71009EF4EC(s32 a1, s32 a2) {
    if (u32(a1 - 3) > 1)
        return;
    _3ad2 = !(a2 & 1);
    UiSubsys1::instance()->sub_7100968AF8(a1);
}

// 0x71009ef51c (CSV unnamed)
void ScreenAppMap::sub_71009EF51C(s32 a1) {
    if (u32(a1) <= 0xe) {
        UiSubsys1::instance()->set128(a1);
        bool ready = UiSubsys1::instance()->sub_7100968BD8();
        if (ready)
            UiSubsys1::instance()->sub_7100968AF8(2);
        else
            UiSubsys1::instance()->sub_7100968AF8(1);
        _3ad2 = 0;
    }
}

// 0x71009eecd0
bool ScreenAppMap::sub_71009EECD0() const {
    if (!_3610 || !_3610->sub_71009AEF7C())
        return false;
    return isOpened();
}

// 0x71009eed10
s32 ScreenAppMap::sub_71009EED10() const {
    return _3610->sub_71009AEF7C();
}


// ScreenAppMap creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_7102481768[] = {
    {"Pa_Map_00", sub_71009E7F60, 0},
    {"Pa_MapIcon_00", sub_71009E805C, 0},
    {"Pa_PlayerNavi_00", sub_71009E8158, 0},
    {"Pa_StampBox_00", sub_71009E8254, 0},
    {"Pa_SensorIcon_00", sub_71009DE4F0, 0},
    {"Pa_SensorBox_00", sub_71009DE3F4, 0},
    {"Pa_Sensor_00", sub_71009E8350, 0},
    {"Pa_Comp_00", sub_71009E844C, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102481758(sUnk_7102481768);
// 0x71009e7f30
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102481828::getEntries() const {
    return &sUnk_7102481758;
}

ScreenChild* sub_71009E7F60(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) ScreenAppMapWidget(layout_ex);
}

ScreenChild* sub_71009E805C(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_7102478048(layout_ex);
}

ScreenChild* sub_71009E8158(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_7102479838(layout_ex);
}

ScreenChild* sub_71009E8254(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_710247d8f8(layout_ex);
}

ScreenChild* sub_71009E8350(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_710247c368(layout_ex);
}

ScreenChild* sub_71009E844C(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_7102477c30(layout_ex);
}

// 0x71009f1e9c
void sub_71009F1E9C() {
    createAndLoadScreenIfNeededImpl(ScreenId::AppSystemWindow, nullptr);
    auto* screen = sead::DynamicCast<ScreenAppSystemWindow>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow));
    if (screen)
        screen->m154(5);
}

// 0x71009f1f64
void sub_71009F1F64() {
    createAndLoadScreenIfNeededImpl(ScreenId::AppSystemWindow, nullptr);
    auto* screen = sead::DynamicCast<ScreenAppSystemWindow>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow));
    if (screen)
        screen->m154(6);
}

// 0x71009f202c
void sub_71009F202C() {
    createAndLoadScreenIfNeededImpl(ScreenId::AppSystemWindow, nullptr);
    auto* screen = sead::DynamicCast<ScreenAppSystemWindow>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow));
    if (screen)
        screen->m154(7);
}

// 0x71009f2204
void sub_71009F2204() {
    auto* screen = sead::DynamicCast<ScreenAppSystemWindow>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow));
    if (!screen || screen->isClosed())
        return;
    if (ScreenAppSystemWindow::sub_71009FC4A0() != 0)
        return;
    sub_7100A9AC84(UiSubsys1::instance()->_3a0);
    PauseMenuDataMgr::instance()->_444fc = 2;
    Manager::instance()->sub_7100A7C8D4();
}

// 0x71009e3b84
void sub_71009E3B84() {
    auto* screen = sead::DynamicCast<ScreenAppSystemWindow>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow));
    if (!screen || screen->_3610 != 8 || !screen->isClosedOrClosing())
        return;
    if (ScreenAppSystemWindow::sub_71009FC4A0() != 0)
        return;
    Manager::instance()->setWarpDestination(sub_7100A9EEA4(), sub_7100A9EEF4());
    Manager::instance()->sub_7100A7C9C0();
}

// 0x71009e70b8
void ScreenAppMapDungeon::sub_71009E70B8() {
    Unk_71025d69f0::instance()->sub_710094E064();
    close(-1);
    if (auto* screen = sead::DynamicCast<ScreenAppMap>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppMap)))
        screen->close(-1);
}

// 0x71009f273c
void ScreenAppMap::sub_71009F273C() {
    Unk_71025d69f0::instance()->sub_710094E064();
    close(-1);
}

// 0x71009eb0e0
// NON_MATCHING: the original materialises the 0 for set6e4 as `mov x1, xzr` (ours `mov w1, wzr`); same in m98
void ScreenAppMap::sub_71009EB0E0() {
    auto* subsys = UiSubsys1::instance();
    if (subsys->is38b8And38b9Clear()) {
        UiSubsys1::instance()->clear38c8();
        UiSubsys1::instance()->set6e4(1);
        _3630->PlayFromCurrent(eui::Animator::PlayType(0), 1.0f);
    } else if (UiSubsys1::instance()->sub_7100966E64()) {
        UiSubsys1::instance()->set38c8();
        UiSubsys1::instance()->set6e4(0);
        _3630->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
    }
}

// 0x71009eb72c: picks the map scale level (forced by a flag, else from the horse / patrol / scene state)
void ScreenAppMap::sub_71009EB72C() {
    s32 level = ksys::gdt::getFlag_App_Map_ForceSetScaleLevelWhenMiniMap(false);
    if (level == -1) {
        _3c55 = _3c54;
        if (auto* player = act::PlayerInfo::instance()->getPlayer())
            _3c54 = player->isRidingHorse();
        s32 mode;
        if (ksys::Patrol::instance() && ksys::Patrol::instance()->mField0)
            mode = 1;
        else if (GameSceneSubsys14::instance() && GameSceneSubsys14::instance()->sub_7100904ED4())
            mode = 1;
        else if (_3c54)
            mode = 2;
        else
            mode = 0;
        level = sub_71009661BC(mode);
    }
    if (level != _3c50) {
        _3610->sub_71009A99F0(level);
        _3c50 = level;
    }
    sub_71009F1DBC();
}

// 0x71009f1b18
void ScreenAppMap::sub_71009F1B18(sead::Vector2f* v) const {
    v->normalize();
    *v *= _3c48 / _3c4c;
}

// 0x71009f1b9c
void ScreenAppMap::sub_71009F1B9C() {
    if (wm::sub_7100A9D800())
        _3c88->StopAtMax();
    else
        _3c88->StopAtMin();
    if (!_3c66)
        return;
    const s32 temperature = sead::Mathf::floor(_3c60);
    sead::FixedSafeString<16> text;
    text.format("%+d", temperature);
    setWidgetString(_3c80, "T_Temp_00", text);
}

// 0x71009f1ca4
void ScreenAppMap::sub_71009F1CA4(eui::LayoutEx* layout) {
    if (!layout)
        return;
    const s32 found = _3610->sub_71009AEF7C();
    if (wm::isFindDungeonActivated()) {
        if (!found)
            _3638->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
    } else if (!found) {
        _3638->PlayFromCurrent(eui::Animator::PlayType(0), 1.0f);
    }
    if (_3c65 || _3c64) {
        sead::FixedSafeString<128> text;
        wm::formatTimeString(&text);
        setWidgetString(layout, "T_Time_00", text);
    }
}

// 0x71009e5530
bool sub_71009E5530() {
    if (sUnk_71025de180 & 1)
        return false;
    auto* manager = Manager::instance();
    if (!manager)
        return true;
    if (u32(manager->_64c38) <= 3 && ksys::gdt::getFlag_IsBattle_CurseR())
        return false;
    switch (manager->_64c38) {
    case 0:
        if (!ksys::gdt::getFlag_Appear_PGanonWind())
            return true;
        return ksys::gdt::getFlag_Die_PGanonWind();
    case 1:
        if (!ksys::gdt::getFlag_Appear_PGanonFire())
            return true;
        return ksys::gdt::getFlag_Die_PGanonFire();
    case 2:
        if (!ksys::gdt::getFlag_Appear_PGanonWater())
            return true;
        return ksys::gdt::getFlag_Die_PGanonWater();
    case 3:
        if (!ksys::gdt::getFlag_Appear_PGanonElectric())
            return true;
        return ksys::gdt::getFlag_Die_PGanonElectric();
    case 4:
        if (Manager::instance()->_64c30 & 0x800000000000)
            return true;
        return GearMgr::instance()->_10d0.value <= sead::Mathf::epsilon();
    case 5:
        return false;
    default:
        return true;
    }
}

// 0x71009e5868
void ScreenAppMapDungeon::sub_71009E5868(s32 index) {
    const s32 prev = _118ac;
    if (prev != -1) {
        _118ac = -1;
        if (auto* animator = _11530[prev].animators[2])
            animator->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
        if (auto* animator = _11818[prev].animator)
            animator->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
    }
    _118ac = index;
    if (index == -1) {
        if (_11918)
            _11918->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
        return;
    }
    _118d0 = index;
    if (auto* animator = _11818[index].animator)
        animator->PlayAuto(1.0f);
    if (auto* animator = _11530[index].animators[2])
        animator->PlayAuto(1.0f);
}

// inline-only in the original; name is a guess: the same switch on Manager::_64c38 (lookup table 0x7101e7e640)
// repeats in 0x71009e62fc and twice in 0x71009e5ca8
static s32 getDungeonTableIndex() {
    auto* manager = Manager::instance();
    if (!manager)
        return 6;
    switch (manager->_64c38) {
    case 0:
        return 2;
    case 1:
        return 1;
    case 2:
        return 3;
    case 3:
        return 0;
    case 4:
        return 5;
    case 5:
        return 4;
    default:
        return 6;
    }
}

// 0x71009e5ca8
// NON_MATCHING: the original loads _118ac once before the loop (reloading it only after the StopAtMin call) and
// reuses that value after the loop; ours reloads it every iteration
void ScreenAppMapDungeon::sub_71009E5CA8(s32 index) {
    for (s32 i = 0; i < 11; ++i) {
        if (i == index || i == _118ac)
            continue;
        if (auto* animator = _11530[i].animators[2])
            animator->StopAtMin();
    }
    const s32 prev = _118ac;
    if (prev != -1) {
        _118ac = -1;
        if (auto* animator = _11530[prev].animators[2])
            animator->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
        const s32 base = _117b0[getDungeonTableIndex()];
        if (base != -1) {
            if (auto* animator = _11798[base + prev]->animator)
                animator->PlayAuto(-1.0f);
        }
    }
    _118ac = index;
    if (index == -1) {
        if (_11918)
            _11918->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
        return;
    }
    _118d0 = index;
    if (auto* animator = _11530[index].animators[2])
        animator->PlayAuto(1.0f);
    const s32 base = _117b0[getDungeonTableIndex()];
    if (base != -1) {
        if (auto* animator = _11798[base + index]->animator)
            animator->PlayAuto(1.0f);
    }
}

// 0x71009e62fc
bool ScreenAppMapDungeon::sub_71009E62FC() const {
    const s32 index = getDungeonTableIndex();
    auto* camera = agl::lyr::Renderer::instance()->mLayers[1]->sub_7100B60CE0();
    if (!camera)
        return true;
    sead::Vector3f dir = _3680.getAt() - _3668;
    camera->getLookVectorByMatrix(&dir);
    switch (index) {
    case 0:
        return dir.x > 0.0f;
    case 1:
        return dir.z < 0.0f;
    case 2:
        return dir.z > 0.0f;
    case 3:
        return dir.x > 0.0f;
    case 4:
        return dir.z > 0.0f;
    case 5:
        return dir.z < 0.0f;
    default:
        return true;
    }
}

// 0x71009e65d4
void ScreenAppMapDungeon::sub_71009E65D4() {
    auto* layer_camera = agl::lyr::Renderer::instance()->mLayers[1]->sub_7100B60CE0();
    if (!layer_camera)
        return;

    sead::Vector3f pos;
    sead::Vector3f up;
    _3680.getUpVectorByMatrix(&up);
    _3680.getWorldPosByMatrix(&pos);
    sead::Vector3f look = _3680.getAt() - pos;
    const f32 distance = look.normalize();
    layer_camera->getLookVectorByMatrix(&look);
    pos = _3680.getAt() + look * distance;
    _3680.setPos(pos);
    _3680.setUp(sead::Vector3f::ey);
    _3680.normalizeUp();
    _3680.updateViewMatrix();

    const f32 horizontal =
        sead::Mathf::clamp(sead::Mathf::sqrt(look.x * look.x + look.z * look.z), -1.0f, 1.0f);
    const f32 pitch = std::acos(sead::Mathf::abs(horizontal));
    _3658 = -pitch;
    if (look.y < 0.0f)
        _3658 = pitch;
    const f32 yaw = std::acos(sead::Mathf::clamp(look.z / horizontal, -1.0f, 1.0f));
    _365c = yaw;
    if (look.x < 0.0f)
        _365c = -yaw;
}

}  // namespace uking::ui

namespace eui {

// 0x71009e719c (placeholder name): the out-of-line DynamicCast of an animation to eui::Animator (used by
// LayoutEx::sub_7100BDDDF8)
Animator* sub_71009E719C(nn::ui2d::AnimTransform* anim) {
    return nn::font::DynamicCast<Animator>(anim);
}

}  // namespace eui
