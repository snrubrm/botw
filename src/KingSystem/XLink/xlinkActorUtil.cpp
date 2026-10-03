#include "KingSystem/XLink/xlinkActorUtil.h"
#include <xlink2/xlink2UserInstanceELink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkXLink.h"

int sub_7101240FE8(ksys::act::Actor* actor) {
    if (actor && actor->getXLink()) {
        auto* elink = actor->getXLink()->_48;
        auto* slink = actor->getXLink()->_50;
        if (elink && slink)
            return 2;
        if (elink)
            return 0;
        if (slink)
            return 1;
    }
    return 3;

}

void sub_71012410C8(ksys::xlink::XLink* xlink, const char* name, int kind,
                    Unk_71012419b4* handle) {
    if ((kind == 0 || kind == 2) && xlink->_48) {
        if (handle)
            xlink->_48->searchAndEmit(name, &handle->mELink);
        else
            xlink->_48->searchAndEmit(name);
    }
    if ((kind == 1 || kind == 2) && xlink->_50) {
        if (handle)
            xlink->_50->searchAndEmit(name, &handle->mSLink);
        else
            xlink->_50->searchAndEmit(name);
    }

}

void xlinkSearchAndEmit(ksys::act::Actor* actor, const char* name, int kind,
                        Unk_71012419b4* handle) {
    if (!actor || !actor->getXLink())
        return;
    sub_71012410C8(actor->getXLink(), name, kind, handle);
}

void flyingObjectEmitXlink(ksys::act::Actor* actor, const char* name, int kind,
                           Unk_71012419b4* handle) {
    auto* xlink = actor->getXLink();
    if (!xlink)
        return;
    if ((kind == 0 || kind == 2) && xlink->_48) {
        if (handle)
            xlink->_48->searchAndHold(name, &handle->mELink);
        else
            xlink->_48->searchAndHold(name);
    }
    if ((kind == 1 || kind == 2) && xlink->_50) {
        if (handle)
            xlink->_50->searchAndHold(name, &handle->mSLink);
        else
            xlink->_50->searchAndHold(name);
    }
}

void sub_710124127C(ksys::act::Actor* actor, int kind) {
    if (!actor->getXLink())
        return;
    if ((kind == 0 || kind == 2) && actor->getXLink()->_48)
        actor->getXLink()->_48->killAll();
    if ((kind == 1 || kind == 2) && actor->getXLink()->_50)
        actor->getXLink()->_50->stopAllEvent(-1);
}

void sub_71012412E4(ksys::act::Actor* actor, u32 idx, f32 value, bool force) {
    if (!actor->getXLink())
        return;
    if (auto* elink = actor->getXLink()->_48) {
        if (force || elink->isPropertyAssigned(idx))
            elink->setPropertyValue(idx, value);
    }
    if (auto* slink = actor->getXLink()->_50) {
        if (force || slink->isPropertyAssigned(idx))
            slink->setPropertyValue(idx, value);
    }
}

void xlinkEventOn(ksys::act::Actor* actor, u32 idx, s32 value, bool force) {
    if (!actor->getXLink())
        return;
    if (auto* elink = actor->getXLink()->_48) {
        if (force || elink->isPropertyAssigned(idx))
            elink->setPropertyValue(idx, value);
    }
    if (auto* slink = actor->getXLink()->_50) {
        if (force || slink->isPropertyAssigned(idx))
            slink->setPropertyValue(idx, value);
    }
}

// NON_MATCHING: the original stores the ELink event's scale (1, 1, 1) with two `stp` pairs interleaved with the
// position's z; ours merges the constants into one 64-bit store (HandleELink::setPosition, lib/xlink2)
void Unk_71012419b4::sub_71012419B4(const sead::Vector3f& pos) {
    mELink.setPosition(pos);
    mSLink.setPosition(pos);
}

void Unk_71012419b4::sub_7101241A44(const sead::Matrix34f& mtx) {
    mELink.setMatrix(mtx);
    mSLink.setMatrix(mtx);
}

void Unk_71012419b4::fadeXLink() {
    mELink.fade();
    mSLink.fade();
}
