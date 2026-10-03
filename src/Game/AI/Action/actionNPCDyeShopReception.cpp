#include "Game/AI/Action/actionNPCDyeShopReception.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

NPCDyeShopReception::NPCDyeShopReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCDyeShopReception::~NPCDyeShopReception() = default;

bool NPCDyeShopReception::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCDyeShopReception::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

// NON_MATCHING: block layout (the original places the `_20 < 2` increment and the setFailed() blocks after the
// main path, with `cmp #2; b.lt`; ours puts the increment first and compares `> 1`)
void NPCDyeShopReception::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (!_1c) {
        setFailed();
        return;
    }
    if (_20 < 2) {
        _20 = _20 + 1;
        return;
    }
    if (ksys::gdt::getFlag_Shop_DecideTrig()) {
        ksys::gdt::setFlag_Shop_IsDecide(true);
        ksys::gdt::setFlag_Shop_DecideTrig(false);
    }
    if (!ui::sub_7100A98514())
        setFinished();
}

}  // namespace uking::action
