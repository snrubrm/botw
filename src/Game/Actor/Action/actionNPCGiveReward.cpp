#include "Game/Actor/Action/actionNPCGiveReward.h"
#include <math/seadMathCalcCommon.h>
#include "Game/UI/uiUtils.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/System/UIGlue.h"

namespace uking::action {

NPCGiveReward::NPCGiveReward(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCGiveReward::~NPCGiveReward() = default;

bool NPCGiveReward::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original loads UI::instance() before testing the selected item, and compares the counts with 0
// (le) where ours compares with 1 (lt); register allocation.
// Gives the reward of the NPC's "Normal" shop table: the most expensive item cheaper than the rupee tier of the reward
// amount (NPC::_1038) if there is room for it, otherwise rupees (taken in calc_).
void NPCGiveReward::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = 0;
    auto* npc = sead::DynamicCast<act::NPC>(mActor);
    if (!npc)
        return;

    npc->_f88.giveItem(mActor->getParam()->getRes().mShopData, mActor->getName(), "Normal", false);

    const s32 amount = npc->_1038;
    sead::SafeString rupee_name = "PutRupee";
    s32 rupee_value;
    s32 max_price;
    if (amount < 10) {
        rupee_name = sead::SafeString("PutRupee");
        rupee_value = 1;
        max_price = 10;
    } else if (amount < 20) {
        rupee_name = sead::SafeString("PutRupee_Blue");
        rupee_value = 5;
        max_price = 20;
    } else {
        rupee_name = sead::SafeString("PutRupee_Red");
        rupee_value = 20;
        max_price = sead::Mathi::maxNumber();
    }

    if (amount > 0) {
        auto& items = npc->_f88.mItems;
        const s32 num_items = npc->_f88.mNumItems;
        s32 best = -1;
        s32 best_price = -1;
        for (s32 i = 0; i < num_items; ++i) {
            const auto& item = items[i];
            if (item.count > 0 && item.price < max_price && item.price > best_price) {
                best_price = item.price;
                best = i;
            }
        }
        if (best >= 0 && ui::checkWeaponFreeSlotImpl(items[best].name, 1)) {
            const sead::SafeString name = items[best].name;
            --items[best].count;
            npc->_f88.sub_710091D030(mActor->getName());
            if (auto* ui = ui::UI::instance()) {
                ksys::ui::callIncreasePouchNum(name, 1);
                ui->x(name);
            }
            return;
        }
    }

    if (auto* ui = ui::UI::instance()) {
        ui->x(rupee_name);
        _1c = rupee_value;
    }
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
