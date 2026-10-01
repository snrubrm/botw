#pragma once

#include <basis/seadTypes.h>

namespace ksys::res {

class ArchiveWork;

// TODO: very incomplete
class TextureHandleMgr {
public:
    virtual ~TextureHandleMgr();

    void preCalc();
    void calc();

    ArchiveWork* getArchiveWork() const;
    void clearAllCache();

private:
    // TODO
    u8 _8[0x768 - 0x8];
    ArchiveWork* mArchiveWork;
};

}  // namespace ksys::res
