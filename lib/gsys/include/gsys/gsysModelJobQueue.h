#pragma once

#include <basis/seadTypes.h>

namespace sead {
class WorkerMgr;
}

namespace gsys {

// The job queue embedded in ModelScene at +0x5550 (the next modelled field is at +0x5630,
// so the extent is 0xe0). Only the two methods ModelScene calls directly are declared;
// the rest of the class (ctor 0x7100c7e634, initialize 0x7100c7e82c, ...) stays unmodelled.
class ModelJobQueue {
public:
    void updateModelUnit(sead::WorkerMgr* wm);
    void changeRequestFlag(bool, bool, bool);

private:
    u8 _0[0xe0];
};
static_assert(sizeof(ModelJobQueue) == 0xe0);

}  // namespace gsys
