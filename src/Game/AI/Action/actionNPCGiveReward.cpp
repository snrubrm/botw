#include "Game/AI/Action/actionNPCGiveReward.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/System/UIGlue.h"

namespace uking::action {

NPCGiveReward::NPCGiveReward(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCGiveReward::~NPCGiveReward() = default;

bool NPCGiveReward::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCGiveReward::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCGiveReward::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCGiveReward::loadParams_() {}

void NPCGiveReward::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (isFinished())
        return;
    auto* ui = ui::UI::instance();
    if (!ui || ui->sub_71010A5CAC())
        return;
    if (auto* gdm = ksys::gdt::Manager::instance()) {
        if (_1c >= 1) {
            gdm->incrementS32(_1c, "CurrentRupee");
            ksys::ui::initRupeeCounter();
        }
    }
    setFinished();
}

}  // namespace uking::action
