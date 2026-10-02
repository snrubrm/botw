#include "Game/AI/aiMessage3DText.h"
#include "Game/UI/euiMessageString.h"
#include "Game/UI/uiUI.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking {

Message3DText::Message3DText() = default;

Message3DText::~Message3DText() {}

void Message3DText::sub_7100721830(ksys::act::Actor* actor, bool shout) {
    mActor = actor;
    if (actor) {
        sead::SafeString name;
        if (actor->getName() == "Npc_HiddenKorokGround" ||
            actor->getName() == "Npc_HiddenKorokFly") {
            name = "Npc_HiddenKorok";
        } else {
            ksys::act::getSameGroupActorName(&name, actor);
        }
        if (shout)
            _8.format("ShoutMsg/Shout_%s", name.cstr());
        else
            _8.format("EventFlowMsg/%s", name.cstr());
    } else if (shout) {
        _8.format("ShoutMsg/Shout_");
    } else {
        _8.format("EventFlowMsg/");
    }
    _c9 = true;
}

void Message3DText::set(f32 time, const sead::SafeString& label) {
    if (!mActor || !_c9)
        return;
    eui::MessageString message;
    if (ui::getMessage(_8, label, &message) != 0)
        return;
    _c9 = false;
    _cc.reset(time);
    _70.copy(label);
}

void Message3DText::sub_7100721B1C(f32 time, const sead::SafeString& label) {
    if (!mActor)
        return;
    eui::MessageString message;
    if (ui::getMessage(_8, label, &message) != 0)
        return;
    _c9 = false;
    _cc.reset(time);
    _70.copy(label);
}

void Message3DText::sub_7100721C48() {
    if (!mActor || _c9)
        return;
    if (!(_cc.value <= sead::Mathf::epsilon())) {
        _cc.update();
        return;
    }
    if (auto* ui = ui::UI::instance()) {
        if (_c8)
            ui->x_0(false);
        ui->sub_71010A6BEC(mActor, false);
        ui->sub_71010A6454(_8, _70, mActor, 30.0f, false);
    }
    _c9 = true;
}

}  // namespace uking
