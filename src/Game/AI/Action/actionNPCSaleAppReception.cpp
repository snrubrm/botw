#include "Game/AI/Action/actionNPCSaleAppReception.h"
#include "KingSystem/GameData/gdtManager.h"

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

void NPCSaleAppReception::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
