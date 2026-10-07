#include "Game/AI/Action/actionDemoForceSetPlayerSavePosAngle.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Map/mapObject.h"

ksys::map::Object* sub_7100EE5240(ksys::act::Actor* actor, const sead::SafeString& anchor,
                               const sead::SafeString& unique);

namespace uking::action {

DemoForceSetPlayerSavePosAngle::DemoForceSetPlayerSavePosAngle(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DemoForceSetPlayerSavePosAngle::~DemoForceSetPlayerSavePosAngle() = default;

bool DemoForceSetPlayerSavePosAngle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoForceSetPlayerSavePosAngle::loadParams_() {
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mAnchorName_d, "AnchorName");
}

bool DemoForceSetPlayerSavePosAngle::oneShot_() {
    m32();
    return true;
}

void DemoForceSetPlayerSavePosAngle::m32() {
    auto* actor = mActor;
    auto& link = ksys::evt::sub_7100DC85D4(actor);
    if (!link.hasProcInCalcState())
        return;
    auto* object = sub_7100EE5240(actor, mAnchorName_d, mUniqueName_d);
    if (object) {
        const sead::Vector3f position = object->getTranslate();
        ksys::gdt::setFlag_PlayerSavePos(position, false);
        ksys::gdt::setFlag_PlayerSavePosAngleYDegree(object->getRotate().y * 57.295776f, false);
    } else {
        sead::FixedSafeString<128> name;
        name.appendWithFormat("%s", mAnchorName_d.cstr());
        if (!mUniqueName_d.isEmpty())
            name.appendWithFormat("(ユニーク名：%s)", mUniqueName_d.cstr());
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
    }
}

}  // namespace uking::action
