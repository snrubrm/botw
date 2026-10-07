#pragma once

#include <prim/seadSafeString.h>
#include "resHandle.h"

namespace ksys::res {

class EntryFactoryBase;

void registerEntryFactory(EntryFactoryBase* factory, const sead::SafeString& name);
void unregisterEntryFactory(EntryFactoryBase* factory);

bool isHostPath(const sead::SafeString& path);

// In release builds, the only thing this function does is return 1.
// TODO: figure out what this is used for. Stubbed log function?
bool stubbedLogFunction();

// In release builds, the only thing this function does is return 0.
// TODO: figure out what this is used for. Stubbed log function?
bool returnFalse();

// In release builds, the only thing this function does is return 0.
// TODO: figure out what this is used for. Stubbed log function?
bool returnFalse2(const sead::SafeString&);

bool returnFalse3(const sead::SafeString& path);

// 0x71012132ac: in release builds, the only thing this function does is return 0.
bool returnFalse4();

// 0x71012132c8: in release builds, this function does nothing (called with the path of a loaded
// resource and whether it was loaded with decompression).
void sub_71012132C8(const sead::SafeString& path, bool decompressed);

s32 getDefaultAlignment();

// In release builds, this function does nothing.
// TODO: figure out what this is used for. Stubbed log function?
void registerPackExtension(bool has_extension, const sead::SafeString& extension);

// In release builds, this function does nothing.
// TODO: figure out what this is used for. Stubbed log function?
void stubbedBool(bool);

void setResourceMgrPack(Handle* pack);

bool isCompactionStopped();
void callResourceMgrTaskMethodOO();
void setCompactionStopped(bool stopped);
void texHandleMgrSetSomeFlags(bool b);

}  // namespace ksys::res
