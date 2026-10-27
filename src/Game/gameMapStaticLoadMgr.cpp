#include "Game/gameMapStaticLoadMgr.h"

namespace ksys::map {

s32 sNumMubins;
MapStaticMubin* sMubins;

}  // namespace ksys::map

ksys::res::Handle* getMapStaticMubin(const sead::SafeString& name) {
    for (s32 i = 0; i < ksys::map::sNumMubins; ++i) {
        if (ksys::map::sMubins[i].name == name)
            return &ksys::map::sMubins[i].handle;
    }
    return nullptr;
}
