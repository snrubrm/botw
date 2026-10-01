#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resResourceMgrTask.h"

namespace ksys::res {

bool isCompactionStopped() {
    auto* task = ResourceMgrTask::instance();
    return task->isCompactionStopped() || task->_9c0d3c != 0 || task->_9c0d40 != 0;
}

void callResourceMgrTaskMethodOO() {
    ResourceMgrTask::instance()->updateCompaction();
}

void setCompactionStopped(bool stopped) {
    ResourceMgrTask::instance()->setCompactionStopped(stopped);
}

void texHandleMgrSetSomeFlags(bool b) {
    ResourceMgrTask::instance()->x_1(b);
}

bool stubbedLogFunction() {
    return true;
}

void registerEntryFactory(EntryFactoryBase* factory, const sead::SafeString& name) {
    ResourceMgrTask::instance()->registerFactory(factory, name);
}

void unregisterEntryFactory(EntryFactoryBase* factory) {
    ResourceMgrTask::instance()->unregisterFactory(factory);
}

bool isHostPath(const sead::SafeString& path) {
    return ResourceMgrTask::instance()->isHostPath(path);
}

bool returnFalse() {
    return false;
}

bool returnFalse2(const sead::SafeString&) {
    return false;
}

bool returnFalse3(const sead::SafeString&) {
    return false;
}

s32 getDefaultAlignment() {
    return 8;
}

void registerPackExtension(bool has_extension, const sead::SafeString& extension) {}

void stubbedBool(bool) {}

void setResourceMgrPack(Handle* pack) {
    ResourceMgrTask::instance()->setPack(pack);
}

}  // namespace ksys::res
