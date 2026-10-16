#include "Game/Actor/Action/actionWarpPlayerToAnchor.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"
#include "KingSystem/Map/mapObject.h"

// Declaration only (defined in actActorUtil.cpp).
ksys::map::Object* sub_7100EE5240(ksys::act::Actor* actor, const sead::SafeString& anchor,
                                  const sead::SafeString& unique);

namespace uking::action {

WarpPlayerToAnchor::WarpPlayerToAnchor(const InitArg& arg) : DestPlayerWarpBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
WarpPlayerToAnchor::~WarpPlayerToAnchor() {
    ;
}

bool WarpPlayerToAnchor::init_(sead::Heap* heap) {
    return DestPlayerWarpBase::init_(heap);
}

void WarpPlayerToAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    DestPlayerWarpBase::enter_(params);
}

void WarpPlayerToAnchor::leave_() {
    DestPlayerWarpBase::leave_();
}

void WarpPlayerToAnchor::loadParams_() {
    DestPlayerWarpBase::loadParams_();
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mAnchorName_d, "AnchorName");
}

void WarpPlayerToAnchor::calc_() {
    DestPlayerWarpBase::calc_();
}

bool WarpPlayerToAnchor::m33() {
    return true;
}

void WarpPlayerToAnchor::m32() {
    auto& link = ksys::evt::sub_7100DC85D4(mActor);
    if (!link.hasProcInCalcState())
        return;
    auto* object = sub_7100EE5240(mActor, mAnchorName_d, mUniqueName_d);
    if (object) {
        sead::Matrix34f mtx;
        mtx.makeSRT(_4c, object->getRotate(), object->getTranslate());
        _1c = mtx;
        if (m34(object->getTranslate()))
            m35(object->getTranslate(), object->getRotate().y);
    } else {
        sead::FixedSafeString<128> name;
        name.appendWithFormat("%s", mAnchorName_d.cstr());
        if (!mUniqueName_d.isEmpty())
            name.appendWithFormat("(ユニーク名：%s)", mUniqueName_d.cstr());
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        _1c = accessor.getActorMtx();
    }
}

}  // namespace uking::action
