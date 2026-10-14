#include "Game/AI/Behavior/behaviorXLinkCreateToParts.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::behavior {

XLinkCreateToParts::XLinkCreateToParts(const InitArg& arg) : XLinkCreate(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
XLinkCreateToParts::~XLinkCreateToParts() {
    ;
}

bool XLinkCreateToParts::m6(sead::Heap* heap) {
    return XLinkCreate::m6(heap);
}

void XLinkCreateToParts::m7() {
    XLinkCreate::m7();
}

void XLinkCreateToParts::m8() {
    XLinkCreate::m8();
}

void XLinkCreateToParts::m9() {
    XLinkCreate::m9();
}

void XLinkCreateToParts::m15(sead::Vector3f* out) {
    mActor->getMtx().getTranslation(*out);
    const sead::Vector3f offset = *mOffset_s;
    if (offset != sead::Vector3f(0, 0, 0)) {
        sead::Vector3f pos = offset;
        pos.rotate(mActor->getMtx());
        out->setAdd(pos, *out);
    }
}

void XLinkCreateToParts::m16(sead::Vector3f* out) {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        auto& link = enemy->getActorPartsActor(mPartsName_s);
        if (link.hasProcInCalcState()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            accessor.getActorMtx().getTranslation(*out);
        }
    }
}

void XLinkCreateToParts::loadParams() {
    XLinkCreate::loadParams();
    getStaticParam(&mPartsName_s, "PartsName");
    getStaticParam(&mOffset_s, "Offset");
}

}  // namespace uking::behavior
