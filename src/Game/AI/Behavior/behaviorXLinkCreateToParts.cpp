#include "Game/AI/Behavior/behaviorXLinkCreateToParts.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

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

// NON_MATCHING: the original keeps the translation in registers (loaded once, interleaved with the
// copy to *out) and adds it last: `((x*m00 + y*m01) + z*m02) + t`; ours rebuilds the sum differently
void XLinkCreateToParts::m15(sead::Vector3f* out) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    *out = pos;
    if (*mOffset_s != sead::Vector3f(0, 0, 0)) {
        sead::Vector3f v;
        v.setRotated(mActor->getMtx(), *mOffset_s);
        *out = v + pos;
    }
}

void XLinkCreateToParts::m16(sead::Vector3f* out) {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        auto& link = enemy->getActorPartsActor(mPartsName_s);
        if (link.hasProcInCalcState()) {
            ksys::act::ActorConstDataAccess accessor;
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
