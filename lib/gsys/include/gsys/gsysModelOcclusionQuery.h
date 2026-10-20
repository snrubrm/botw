#pragma once

#include <cull/aglOcclusionQuery.h>

namespace gsys {

// Embedded in ModelDrawObj at +0x28: ModelDrawObj's constructor 0x7100c00b04 runs the
// agl::cull::OcclusionQuery constructor there and then stores this class's vtable. No extra
// fields (ModelDrawObj's next field is at +0xa0).
class ModelOcclusionQuery : public agl::cull::OcclusionQuery {
public:
    ModelOcclusionQuery() = default;
};
static_assert(sizeof(ModelOcclusionQuery) == 0x78);

}  // namespace gsys
