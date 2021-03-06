//===-- KInstruction.h ------------------------------------------*- C++ -*-===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef KLEE_KINSTRUCTION_H
#define KLEE_KINSTRUCTION_H

#include <vector>
#include "llvm/Support/DataTypes.h"

namespace llvm {
class Instruction;
}

namespace klee {
class Executor;
class KModule;
class KFunction;

/// KInstruction - Intermediate instruction representation used
/// during execution.
struct KInstruction {
    llvm::Instruction *inst;

    /// Value numbers for each operand. -1 is an invalid value,
    /// otherwise negative numbers are indices (negated and offset by
    /// 2) into the module constant table and positive numbers are
    /// register indices.
    int *operands;
    /// Destination register index.
    unsigned dest;

    /// The function that owns this instruction
    KFunction *owner;

public:
    virtual ~KInstruction();
};

struct KGEPInstruction : KInstruction {
    /// indices - The list of variable sized adjustments to add to the pointer
    /// operand to execute the instruction. The first element is the operand
    /// index into the GetElementPtr instruction, and the second element is the
    /// element size to multiple that index by.
    std::vector<std::pair<unsigned, uint64_t>> indices;

    /// offset - A constant offset to add to the pointer operand to execute the
    /// insturction.
    uint64_t offset;
};

struct KCallInstruction : KInstruction {
    static bool classof(const KInstruction *) {
        return true;
    }
};
} // namespace klee

#endif
