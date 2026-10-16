#include "gsys/gsysIModelProcedural.h"

namespace gsys {

// NON_MATCHING: the original (0x7100c7fc2c) also frees the 0x38-byte pass array at +0xd0/+0xd8,
// which is not modelled yet.
IModelProcedural::~IModelProcedural() = default;

}  // namespace gsys
