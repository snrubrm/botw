#include "Game/AI/Action/actionNPCNameHorse.h"
#include <math/seadVector.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/UI/uiSwkbdMgr.h"
#include "KingSystem/System/SeadController.h"

namespace uking::action {

NPCNameHorse::NPCNameHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCNameHorse::~NPCNameHorse() = default;

void NPCNameHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = false;
    _1d = false;
    _20 = -1;
}

void NPCNameHorse::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    auto* keyboard = ui::SwkbdMgr::instance();
    if (!keyboard)
        return;
    if (!_1c) {
        if (!ksys::SeadController::getInstance()->isTrig(3))
            return;
        keyboard->show(1, true);
        if (keyboard->x()) {
            keyboard->x_0();
            _1d = true;
        } else if (keyboard->x_1()) {
            _1d = false;
        }
        _1c = true;
    }
    if (_1d)
        setFinished();
    else
        setFailed();
}

}  // namespace uking::action
