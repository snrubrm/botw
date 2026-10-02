#include "Game/AI/Action/actionBowChildCreate.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BowChildCreate::BowChildCreate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BowChildCreate::~BowChildCreate() = default;

bool BowChildCreate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BowChildCreate::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71000CEC68();
    playAS("InitClose", false, 0, 0, -1.0f);
}

void BowChildCreate::sub_71000CEC68() {
    auto* parent = sead::DynamicCast<ksys::act::Actor>(
        sead::DynamicCast<ksys::act::Actor>(mParentActor_d->getProc(nullptr, nullptr)));
    if (!parent)
        return;

    _30.x(parent);
    switch (*mID_d) {
    case 0:
        _30._28 = "Unit_A";
        break;
    case 1:
        _30._28 = "Unit_B";
        break;
    case 2:
        _30._28 = "Unit_C";
        break;
    case 3:
        _30._28 = "Unit_D";
        break;
    default:
        _30._28 = "";
        break;
    }
    _30._30.getKey().reset();
    _30._68 = sead::Matrix34f::ident;
    _30._98 = 0;
    _30._18 = true;
    mActor->sub_71011DA824(&_30);
}

void BowChildCreate::leave_() {
    mActor->sub_71011DA834(&_30);
}

void BowChildCreate::loadParams_() {
    getDynamicParam(&mID_d, "ID");
    getDynamicParam(&mParentActor_d, "ParentActor");
}

void BowChildCreate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
