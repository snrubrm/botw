#pragma once

namespace aal {

class GroupMgr;

/// Static access to the parts of the aal system singleton.
class SystemAccessor {
public:
    /// The group manager of the system, nullptr if there is no system.
    static GroupMgr* getGroupMgr();
};

}  // namespace aal
