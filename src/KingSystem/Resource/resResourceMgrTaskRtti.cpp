#include "KingSystem/Resource/resResourceMgrTask.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::res {

bool ResourceMgrTask::checkDerivedRuntimeTypeInfo(
    const sead::RuntimeTypeInfo::Interface* typeInfo) const {
    return checkDerivedRuntimeTypeInfoStatic(typeInfo);
}

const sead::RuntimeTypeInfo::Interface* ResourceMgrTask::getRuntimeTypeInfo() const {
    return getRuntimeTypeInfoStatic();
}

}  // namespace ksys::res

namespace sead {

template TaskBase* TTaskFactory<ksys::res::ResourceMgrTask>(const TaskConstructArg&);

}  // namespace sead

Unk_7102515058::~Unk_7102515058() = default;
