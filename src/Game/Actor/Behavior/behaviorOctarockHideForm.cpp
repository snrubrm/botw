#include "Game/Actor/Behavior/behaviorOctarockHideForm.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_7102450d10.h"

namespace uking::behavior {

OctarockHideForm::OctarockHideForm(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

OctarockHideForm::~OctarockHideForm() = default;

bool OctarockHideForm::init_(sead::Heap* heap) {
    return true;
}

void OctarockHideForm::enter() {}

void OctarockHideForm::calc() {
    if (sub_71005DD5B0(mActor, 19, nullptr, 0, 0)) {
        if (auto* unit = sead::DynamicCast<Unk_7102450d10>(
                *static_cast<Unk_71025afb58**>(mOctarockFormChangeUnit_a)))
            unit->aiOctarockHide();
    } else if (sub_71005DD734(mActor, 19, nullptr, 0, 0)) {
        if (auto* unit = sead::DynamicCast<Unk_7102450d10>(
                *static_cast<Unk_71025afb58**>(mOctarockFormChangeUnit_a)))
            unit->sub_7100714918();
    }
}

void OctarockHideForm::leave() {
    if (auto* unit = sead::DynamicCast<Unk_7102450d10>(
            *static_cast<Unk_71025afb58**>(mOctarockFormChangeUnit_a)))
        unit->sub_7100714918();
}

void OctarockHideForm::loadParams() {
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

}  // namespace uking::behavior
