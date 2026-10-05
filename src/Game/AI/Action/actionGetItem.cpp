#include "Game/AI/Action/actionGetItem.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

// Existing get-demo utility interface; source namespace is unknown.
void callGetDemoHandler(ksys::act::Actor* actor, const sead::SafeString& name);

namespace uking::action {

GetItem::GetItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool GetItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GetItem::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    u32* handle = nullptr;
    if (actor->getRootAi()->getAITreeVariable(&handle,
                                           ksys::act::getStr_AtvKeyActorSaveDataIndex()) && handle) {
        ksys::gdt::Manager::instance()->setBool(true, ksys::gdt::FlagHandle(*handle));
        ui::uiManagerUpdateIsDungeon();
    }
    if (auto* body = actor->getMainBody())
        body->removeFromWorld();
    if (auto* controller = actor->getCharacterController())
        controller->sub_7100F5EC44();
    callGetDemoHandler(actor, actor->getName());
    ui::openPickUpScreen(actor);
}

void GetItem::leave_() {
    ksys::act::ai::Action::leave_();
}

void GetItem::loadParams_() {}

void GetItem::calc_() {
    m32();
}

void GetItem::m32() {
    sub_71005D6D48(mActor);
}

}  // namespace uking::action
