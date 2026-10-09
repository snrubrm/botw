#include "Game/AI/Action/actionCameraEventLook.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"

bool sub_7100EE7168(const ksys::map::Object* obj, sead::Matrix34f* out);

namespace uking::action {

CameraEventLook::CameraEventLook(const InitArg& arg) : CameraEventLookBase(arg) {}

CameraEventLook::~CameraEventLook() = default;

void CameraEventLook::m46() {
    CameraEventLookBase::m46();
    getDynamicParam(&mTargetUniqueName_d, "TargetUniqueName");
}

// NON_MATCHING: event/string and accessor lifetime scheduling differ.
void CameraEventLook::m47() {
    _120.reset();
    _120 = ksys::evt::sub_7100DC85D4(mActor);
    auto* manager = ksys::evt::Manager::instance();
    if (manager->checkActiveContextEventName("Demo014_0", "Notice_copy")) {
        if (auto* link = manager->getBaseProcLinkFromActiveEvent("EventTag", "OpenDoor"))
            _120 = *link;
    }
    if (!_120.hasProc())
        return;
    _140 = 0;
    if (!ksys::act::findLinkReferenceObj(&_120, sead::SafeString::cEmptyString,
                                       mTargetUniqueName_d, &_140)) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_120, &accessor);
        sead::FixedSafeString<64> name;
        sead::FixedSafeString<64> unique_name;
        ksys::act::sub_7100EE7854(accessor, &name, &unique_name);
        sead::FixedSafeString<128> message;
        if (!mTargetUniqueName_d.isEmpty())
            message.appendWithFormat("(ユニーク名：%s)", mTargetUniqueName_d.cstr());
    }
}

// NON_MATCHING: reference lookup and argument scheduling differ.
void CameraEventLook::m48(sead::Matrix34f* out) {
    s32 index = _140;
    if (auto* object = ksys::act::findLinkReferenceObj(
            &_120, sead::SafeString::cEmptyString, mTargetUniqueName_d, &index)) {
        if (auto* actor = object->tryGetActor(false))
            sub_71009258B0(actor, out);
        else
            sub_7100EE7168(object, out);
    }
}

}  // namespace uking::action
