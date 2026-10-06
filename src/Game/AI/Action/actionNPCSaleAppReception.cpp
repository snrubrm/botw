#include "Game/AI/Action/actionNPCSaleAppReception.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtManagerInline.h"
#include "KingSystem/GameData/gdtTriggerParam.h"

namespace uking::action {

NPCSaleAppReception::NPCSaleAppReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCSaleAppReception::~NPCSaleAppReception() = default;

bool NPCSaleAppReception::init_(sead::Heap* heap) {
    _20 = heap;
    return true;
}

void NPCSaleAppReception::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* gdm = ksys::gdt::Manager::instance())
        gdm->setBool(false, "Shop_IsDecide");
    _28 = 0;
}

// NON_MATCHING: stack slot assignment only (the original keeps the screen type / decide flag in the upper frame
// area and one more SafeString temporary slot); the call sequence matches.
void NPCSaleAppReception::calc_() {
    s32 screen_type;
    bool decided;
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (_28 >= 2) {
        auto* gdm = ksys::gdt::Manager::instance();
        if (!gdm)
            return;
        screen_type = -1;
        decided = false;
        if (ksys::gdt::getS32IfCopiedByName(gdm, &screen_type, "Shop_ScreenType")) {
            setFinished();
            return;
        }
        if (!ksys::gdt::getBoolByNameNoBool2(gdm, &decided, "Shop_DecideTrig") || !decided)
            return;
        gdm->setBool(true, "Shop_IsDecide");
        const char* item_name;
        s32 item_state = 0;
        if (ksys::gdt::getS32ByName(gdm, &item_state, "Shop_ItemState"))
            gdm->setS32(item_state, "Shop_CurrentItemState");
        if (ksys::gdt::getStr64ByName(gdm, &item_name, "Shop_SelectItemName"))
            gdm->setStr64(item_name, "Shop_SelectItemNameJpn");
        setFinished();
    } else {
        ++_28;
    }
}

}  // namespace uking::action
