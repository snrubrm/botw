#include "Game/Actor/Action/actionEventPlayUiActorName.h"
#include <container/seadBuffer.h>
#include "Game/UI/uiScreenNameTable.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/System/UIGlue.h"

namespace uking::action {

namespace {

// Placeholder: actor type -> name screen id entry (0x18 bytes).
struct ActorNameScreenEntry {
    sead::SafeString name;
    s32 id;
};

// 0x71025b20e0 (static initializer 0x710011e518)
ui::ScreenNameTableHeader sScreenNameTableHeader;
ActorNameScreenEntry sScreenNameEntries[] = {{"DemoNameEnemy_00", 16}, {"DemoName_00", 15}};
sead::Buffer<ActorNameScreenEntry> sScreenNames(sScreenNameEntries);

}  // namespace

EventPlayUiActorName::EventPlayUiActorName(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPlayUiActorName::~EventPlayUiActorName() = default;

bool EventPlayUiActorName::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiActorName::enter_(ksys::act::ai::InlineParamPack* params) {
    const auto& entry = sScreenNames[*mActorType_d];
    ksys::ui::sub_7100EDC530(entry.id, nullptr);
    auto* screen = sead::DynamicCast<ui::Screen>(eui::ScreenMgr::instance()->getScreen(entry.id));
    if (!screen) {
        setFailed();
        return;
    }

    _40 = screen;
    if (*mClipIndex_d < 0) {
        screen->open(1);
        return;
    }

    const f32 frame = ksys::evt::Manager::instance()->sub_7100DB1174(*mClipIndex_d);
    if (auto* demo_name = sead::DynamicCast<ui::ScreenDemoName>(screen))
        demo_name->m154(mActorName_d);
    if (auto* demo_name_enemy = sead::DynamicCast<ui::ScreenDemoNameEnemy>(screen))
        demo_name_enemy->m154(mActorName_d);
    screen->m73(frame);
    _48 = frame;
}

// NON_MATCHING: the original loads the table entry before ScreenMgr::instance()
void EventPlayUiActorName::leave_() {
    _40 = nullptr;
    auto* screen = sead::DynamicCast<ui::Screen>(
        eui::ScreenMgr::instance()->getScreen(sScreenNames[*mActorType_d].id));
    if (screen)
        screen->m76();
}

void EventPlayUiActorName::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
    getDynamicParam(&mActorType_d, "ActorType");
    getDynamicParam(&mActorName_d, "ActorName");
}

// NON_MATCHING: the original loads the table entry before ScreenMgr::instance()
void EventPlayUiActorName::calc_() {
    if (isFinished() || isFailed() || !_40)
        return;

    auto* screen = sead::DynamicCast<ui::Screen>(
        eui::ScreenMgr::instance()->getScreen(sScreenNames[*mActorType_d].id));
    if (screen != _40) {
        if (!(ksys::evt::Manager::instance()->_1d2f4_bytes[1] & 8))
            setFailed();
        return;
    }

    if (*mClipIndex_d >= 0 && _48 > 0.0f) {
        const f32 frame =
            sead::Mathf::clampMin(ksys::evt::Manager::instance()->sub_7100DB1138(*mClipIndex_d), 0.0f);
        _40->m74(frame);
        return;
    }

    if (_40->isOpened())
        setFinished();
}

}  // namespace uking::action
