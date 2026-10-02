#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtInfoData.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::evt {

BaseProcLinkForEvent::BaseProcLinkForEvent() {
    reset();
}

BaseProcLinkForEvent::BaseProcLinkForEvent(const Metadata* metadata, act::BaseProc* proc) {
    CallArg arg;
    arg.metadata = metadata;
    arg.proc = proc;
    init(arg);
}

BaseProcLinkForEvent::BaseProcLinkForEvent(const CallArg& arg) {
    init(arg);
}

void BaseProcLinkForEvent::init(const CallArg& arg) {
    _18c = arg._0;
    _1bc = arg._30;
    _188 = arg._31;
    _178 = arg._32;
    _179 = arg._33;
    mMetadata = *arg.metadata;
    _180 = arg._40;
    _8 = arg.proc ? mLink.acquire(arg.proc, false) : true;

    constexpr auto async_flags = Metadata::Flag::_100 | Metadata::Flag::_80 | Metadata::Flag::_40 |
                                 Metadata::Flag::_20 | Metadata::Flag::_10 | Metadata::Flag::_4;

    al::ByamlIter iter;
    if (!InfoData::instance()->getEntry(&iter, arg.metadata->getEventName(),
                                        arg.metadata->getEntryPointName())) {
        return;
    }

    const char* mode = nullptr;
    if (iter.tryGetStringByKey(&mode, "mode") && sead::SafeString(mode) == "Async") {
        mMetadata.mFlags = async_flags;
        mMetadata.mIsAsync = true;
    }

    if (arg.metadata->getEventName() == "SDemo_D-6")
        return;
    if (mMetadata.mFlags.getDirect() == u32(async_flags))
        return;
    if (arg.metadata->getEventName().startsWith("Demo"))
        return;

    bool is_pause_non_demo_member = true;
    iter.tryGetBoolByKey(&is_pause_non_demo_member, "is_pause_non_demo_member");
    if (!is_pause_non_demo_member)
        mMetadata.mFlags = async_flags;
}

void BaseProcLinkForEvent::assign(const BaseProcLinkForEvent& other) {
    CallArg arg;
    arg._0 = other._18c;
    arg._30 = other._1bc;
    arg._31 = other._188;
    arg._32 = other._178;
    arg._33 = other._179;
    arg.metadata = &other.mMetadata;
    arg._40 = other._180;
    auto* actor = sead::DynamicCast<act::Actor>(other.mLink.getProc(nullptr, nullptr));
    arg.proc = sead::DynamicCast<act::Actor>(actor);
    init(arg);
}

act::Actor* BaseProcLinkForEvent::acquireActor() const {
    auto* actor = sead::DynamicCast<act::Actor>(mLink.getProc(nullptr, nullptr));
    return sead::DynamicCast<act::Actor>(actor);
}

void BaseProcLinkForEvent::reset() {
    _188 = false;
    _178 = false;
    _179 = false;
    _18c.makeZero();
    _1bc = false;
    mMetadata.reset();
    _180 = nullptr;
    mLink.reset();
    _8 = false;
}

void BaseProcLinkForEvent::initWithEvent(act::BaseProc* proc, const Metadata* metadata) {
    CallArg arg;
    arg.metadata = metadata;
    arg.proc = proc;
    init(arg);
}

}  // namespace ksys::evt
