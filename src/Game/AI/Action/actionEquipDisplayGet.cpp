#include "Game/AI/Action/actionEquipDisplayGet.h"
#include "Game/AI/aiActorLink.h"
#include "KingSystem/ActorSystem/actActor.h"

// Original global names retained; the source namespaces of these helpers are unknown.
bool sub_7100700A78(s32 slot);
bool sub_7100700F1C(s32 slot);
void callGetDemoHandler2(ksys::act::Actor* actor, ksys::act::Actor* item,
                         const sead::SafeString& name);

namespace uking::ui {
bool openPickUpScreen(ksys::act::Actor* actor);
}

namespace uking::action {

EquipDisplayGet::EquipDisplayGet(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EquipDisplayGet::~EquipDisplayGet() = default;

bool EquipDisplayGet::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EquipDisplayGet::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710010DCAC();
    setFinished();
}

void EquipDisplayGet::leave_() {
    ksys::act::ai::Action::leave_();
}

void EquipDisplayGet::loadParams_() {
    getMapUnitParam(&mEquipStandSlot_m, "EquipStandSlot");
    getAITreeVariable(&mEquipDisplayChild_a, "EquipDisplayChild");
}

void EquipDisplayGet::calc_() {
    ksys::act::ai::Action::calc_();
}

void EquipDisplayGet::sub_710010DCAC() {
    if (sub_7100700A78(*mEquipStandSlot_m)) {
        sub_7100700F1C(*mEquipStandSlot_m);
        auto* link = sead::DynamicCast<ActorLink>(
            *static_cast<Unk_71025afb58**>(mEquipDisplayChild_a));
        if (!link)
            return;
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(link->mLink.getProc(nullptr, nullptr))) {
            callGetDemoHandler2(mActor, actor, actor->getName());
            ui::openPickUpScreen(actor);
            actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        }
        link->mLink.reset();
    } else {
        if (auto* link = sead::DynamicCast<ActorLink>(
                *static_cast<Unk_71025afb58**>(mEquipDisplayChild_a)))
            link->mLink.reset();
    }
}

}  // namespace uking::action
