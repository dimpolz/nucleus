/**
 * (c) 2015 Nucleus project. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#include "ppu_recompiler.h"

namespace cpu {
namespace ppu {

/**
 * PPC64 Instructions:
 *  - UISA: Load and Store Instructions (Section: 4.2.3)
 *  - UISA: Memory Synchronization Instructions (Section: 4.2.6)
 *  - VEA: Memory Synchronization Instructions (Section: 4.3.2)
 */

void Recompiler::lbz(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.ds << 2);
    llvm::Value* rd;

    if (code.ra) {
        addr = builder.CreateAdd(addr, getGPR(code.ra));
    }

    rd = readMemory(addr, 8);
    rd = builder.CreateZExt(rd, builder.getInt64Ty());
    setGPR(code.rd, rd);
}

void Recompiler::lbzu(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.ds << 2);
    llvm::Value* rd;

    addr = builder.CreateAdd(addr, getGPR(code.ra));
    rd = readMemory(addr, 8);
    rd = builder.CreateZExt(rd, builder.getInt64Ty());

    setGPR(code.ra, addr);
    setGPR(code.rd, rd);
}

void Recompiler::lbzux(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    rd = readMemory(addr, 8);
    rd = builder.CreateZExt(rd, builder.getInt64Ty());

    setGPR(code.ra, addr);
    setGPR(code.rd, rd);
}

void Recompiler::lbzx(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    rd = readMemory(addr, 8);
    rd = builder.CreateZExt(rd, builder.getInt64Ty());

    setGPR(code.rd, rd);
}

void Recompiler::ld(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.ds << 2);
    llvm::Value* rd;

    if (code.ra) {
        addr = builder.CreateAdd(addr, getGPR(code.ra));
    }

    rd = readMemory(addr, 64);
    setGPR(code.rd, rd);
}

void Recompiler::ldarx(Instruction code)
{
}

void Recompiler::ldbrx(Instruction code)
{
}

void Recompiler::ldu(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.ds << 2);
    llvm::Value* rd;

    addr = builder.CreateAdd(addr, getGPR(code.ra));
    rd = readMemory(addr, 64);

    setGPR(code.ra, addr);
    setGPR(code.rd, rd);
}

void Recompiler::ldux(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    rd = readMemory(addr, 64);

    setGPR(code.ra, addr);
    setGPR(code.rd, rd);
}

void Recompiler::ldx(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    rd = readMemory(addr, 64);

    setGPR(code.rd, rd);
}

void Recompiler::lfd(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.d);
    llvm::Value* frd;

    if (code.ra) {
        addr = builder.CreateAdd(addr, getGPR(code.ra));
    }

    frd = readMemory(addr, 64);
    setGPR(code.frd, frd);
}

void Recompiler::lfdu(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.d);
    llvm::Value* frd;

    addr = builder.CreateAdd(addr, getGPR(code.ra));
    frd = readMemory(addr, 64);

    setGPR(code.ra, addr);
    setGPR(code.frd, frd);
}

void Recompiler::lfdux(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* frd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    frd = readMemory(addr, 64);

    setGPR(code.ra, addr);
    setGPR(code.frd, frd);
}

void Recompiler::lfdx(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* frd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    frd = readMemory(addr, 64);

    setFPR(code.frd, frd);
}

void Recompiler::lfs(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.d);
    llvm::Value* frd;

    if (code.ra) {
        addr = builder.CreateAdd(addr, getGPR(code.ra));
    }

    frd = readMemory(addr, 32);
    setGPR(code.frd, frd);
}

void Recompiler::lfsu(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.d);
    llvm::Value* frd;

    addr = builder.CreateAdd(addr, getGPR(code.ra));
    frd = readMemory(addr, 32);

    setGPR(code.ra, addr);
    setGPR(code.frd, frd);
}

void Recompiler::lfsux(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* frd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    frd = readMemory(addr, 32);

    setGPR(code.ra, addr);
    setGPR(code.frd, frd);
}

void Recompiler::lfsx(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* frd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    frd = readMemory(addr, 32);

    setFPR(code.frd, frd);
}

void Recompiler::lha(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.ds << 2);
    llvm::Value* rd;

    if (code.ra) {
        addr = builder.CreateAdd(addr, getGPR(code.ra));
    }

    rd = readMemory(addr, 16);
    rd = builder.CreateSExt(rd, builder.getInt64Ty());
    setGPR(code.rd, rd);
}

void Recompiler::lhau(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.ds << 2);
    llvm::Value* rd;

    addr = builder.CreateAdd(addr, getGPR(code.ra));
    rd = readMemory(addr, 16);
    rd = builder.CreateSExt(rd, builder.getInt64Ty());

    setGPR(code.ra, addr);
    setGPR(code.rd, rd);
}

void Recompiler::lhaux(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    rd = readMemory(addr, 16);
    rd = builder.CreateSExt(rd, builder.getInt64Ty());

    setGPR(code.ra, addr);
    setGPR(code.rd, rd);
}

void Recompiler::lhax(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    rd = readMemory(addr, 16);
    rd = builder.CreateSExt(rd, builder.getInt64Ty());

    setGPR(code.rd, rd);
}

void Recompiler::lhbrx(Instruction code)
{
}

void Recompiler::lhz(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.ds << 2);
    llvm::Value* rd;

    if (code.ra) {
        addr = builder.CreateAdd(addr, getGPR(code.ra));
    }

    rd = readMemory(addr, 16);
    rd = builder.CreateZExt(rd, builder.getInt64Ty());
    setGPR(code.rd, rd);
}

void Recompiler::lhzu(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.ds << 2);
    llvm::Value* rd;

    addr = builder.CreateAdd(addr, getGPR(code.ra));
    rd = readMemory(addr, 16);
    rd = builder.CreateZExt(rd, builder.getInt64Ty());

    setGPR(code.ra, addr);
    setGPR(code.rd, rd);
}

void Recompiler::lhzux(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    rd = readMemory(addr, 16);
    rd = builder.CreateZExt(rd, builder.getInt64Ty());

    setGPR(code.ra, addr);
    setGPR(code.rd, rd);
}

void Recompiler::lhzx(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    rd = readMemory(addr, 16);
    rd = builder.CreateZExt(rd, builder.getInt64Ty());

    setGPR(code.rd, rd);
}

void Recompiler::lmw(Instruction code)
{
}

void Recompiler::lswi(Instruction code)
{
}

void Recompiler::lswx(Instruction code)
{
}

void Recompiler::lwa(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.ds << 2);
    llvm::Value* rd;

    if (code.ra) {
        addr = builder.CreateAdd(addr, getGPR(code.ra));
    }

    rd = readMemory(addr, 32);
    rd = builder.CreateSExt(rd, builder.getInt64Ty());
    setGPR(code.rd, rd);
}

void Recompiler::lwarx(Instruction code)
{
}

void Recompiler::lwaux(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    rd = readMemory(addr, 32);
    rd = builder.CreateSExt(rd, builder.getInt64Ty());

    setGPR(code.ra, addr);
    setGPR(code.rd, rd);
}

void Recompiler::lwax(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    rd = readMemory(addr, 32);
    rd = builder.CreateSExt(rd, builder.getInt64Ty());

    setGPR(code.rd, rd);
}

void Recompiler::lwbrx(Instruction code)
{
}

void Recompiler::lwz(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.ds << 2);
    llvm::Value* rd;

    if (code.ra) {
        addr = builder.CreateAdd(addr, getGPR(code.ra));
    }

    rd = readMemory(addr, 32);
    rd = builder.CreateZExt(rd, builder.getInt64Ty());
    setGPR(code.rd, rd);
}

void Recompiler::lwzu(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.ds << 2);
    llvm::Value* rd;

    addr = builder.CreateAdd(addr, getGPR(code.ra));
    rd = readMemory(addr, 32);
    rd = builder.CreateZExt(rd, builder.getInt64Ty());

    setGPR(code.ra, addr);
    setGPR(code.rd, rd);
}

void Recompiler::lwzux(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    rd = readMemory(addr, 32);
    rd = builder.CreateZExt(rd, builder.getInt64Ty());

    setGPR(code.ra, addr);
    setGPR(code.rd, rd);
}

void Recompiler::lwzx(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rd;

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    rd = readMemory(addr, 32);
    rd = builder.CreateZExt(rd, builder.getInt64Ty());

    setGPR(code.rd, rd);
}

void Recompiler::stb(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.d);
    llvm::Value* rs = getGPR(code.rs);

    if (code.ra) {
        addr = builder.CreateAdd(addr, getGPR(code.ra));
    }

    writeMemory(addr, rs);
}

void Recompiler::stbu(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.ds << 2);
    llvm::Value* rs = getGPR(code.rs);

    addr = builder.CreateAdd(addr, getGPR(code.ra));
    writeMemory(addr, rs);

    setGPR(code.ra, addr);
}

void Recompiler::stbux(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rs = getGPR(code.rs);

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    writeMemory(addr, rs);

    setGPR(code.ra, addr);
}

void Recompiler::stbx(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rs = getGPR(code.rs);

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    writeMemory(addr, rs);
}

void Recompiler::std(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.d);
    llvm::Value* rs = getGPR(code.rs);

    if (code.ra) {
        addr = builder.CreateAdd(addr, getGPR(code.ra));
    }

    writeMemory(addr, rs);
}

void Recompiler::stdcx_(Instruction code)
{
}

void Recompiler::stdu(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.ds << 2);
    llvm::Value* rs = getGPR(code.rs);

    addr = builder.CreateAdd(addr, getGPR(code.ra));
    writeMemory(addr, rs);

    setGPR(code.ra, addr);
}

void Recompiler::stdux(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rs = getGPR(code.rs);

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    writeMemory(addr, rs);

    setGPR(code.ra, addr);
}

void Recompiler::stdx(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rs = getGPR(code.rs);

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    writeMemory(addr, rs);
}

void Recompiler::stfd(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.d);
    llvm::Value* frs = getFPR(code.frs);

    if (code.ra) {
        addr = builder.CreateAdd(addr, getGPR(code.ra));
    }

    frs = builder.CreateBitCast(frs, builder.getInt64Ty());
    writeMemory(addr, frs);
}

void Recompiler::stfdu(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.d);
    llvm::Value* frs = getFPR(code.frs);

    addr = builder.CreateAdd(addr, getGPR(code.ra));
    frs = builder.CreateBitCast(frs, builder.getInt64Ty());
    writeMemory(addr, frs);

    setGPR(code.ra, addr);
}

void Recompiler::stfdux(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* frs = getFPR(code.frs);

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    frs = builder.CreateBitCast(frs, builder.getInt64Ty());
    writeMemory(addr, frs);

    setGPR(code.ra, addr);
}

void Recompiler::stfdx(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* frs = getFPR(code.frs);

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    frs = builder.CreateBitCast(frs, builder.getInt64Ty());
    writeMemory(addr, frs);
}

void Recompiler::stfiwx(Instruction code)
{
}

void Recompiler::stfs(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.d);
    llvm::Value* frs = getFPR(code.frs);

    if (code.ra) {
        addr = builder.CreateAdd(addr, getGPR(code.ra));
    }

    frs = builder.CreateFPTrunc(frs, builder.getFloatTy());
    frs = builder.CreateBitCast(frs, builder.getInt32Ty());
    writeMemory(addr, frs);
}

void Recompiler::stfsu(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.d);
    llvm::Value* frs = getFPR(code.frs);

    addr = builder.CreateAdd(addr, getGPR(code.ra));
    frs = builder.CreateFPTrunc(frs, builder.getFloatTy());
    frs = builder.CreateBitCast(frs, builder.getInt32Ty());
    writeMemory(addr, frs);

    setGPR(code.ra, addr);
}

void Recompiler::stfsux(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* frs = getFPR(code.frs);

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    frs = builder.CreateFPTrunc(frs, builder.getFloatTy());
    frs = builder.CreateBitCast(frs, builder.getInt32Ty());
    writeMemory(addr, frs);

    setGPR(code.ra, addr);
}

void Recompiler::stfsx(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* frs = getFPR(code.frs);

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    frs = builder.CreateFPTrunc(frs, builder.getFloatTy());
    frs = builder.CreateBitCast(frs, builder.getInt32Ty());
    writeMemory(addr, frs);
}

void Recompiler::sth(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.d);
    llvm::Value* rs = getGPR(code.rs);

    if (code.ra) {
        addr = builder.CreateAdd(addr, getGPR(code.ra));
    }

    writeMemory(addr, rs);
}

void Recompiler::sthbrx(Instruction code)
{
}

void Recompiler::sthu(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.ds << 2);
    llvm::Value* rs = getGPR(code.rs);

    addr = builder.CreateAdd(addr, getGPR(code.ra));
    writeMemory(addr, rs);

    setGPR(code.ra, addr);
}

void Recompiler::sthux(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rs = getGPR(code.rs);

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    writeMemory(addr, rs);

    setGPR(code.ra, addr);
}

void Recompiler::sthx(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rs = getGPR(code.rs);

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    writeMemory(addr, rs);
}

void Recompiler::stmw(Instruction code)
{
}

void Recompiler::stswi(Instruction code)
{
}

void Recompiler::stswx(Instruction code)
{
}

void Recompiler::stw(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.d);
    llvm::Value* rs = getGPR(code.rs);

    if (code.ra) {
        addr = builder.CreateAdd(addr, getGPR(code.ra));
    }

    writeMemory(addr, rs);
}

void Recompiler::stwbrx(Instruction code)
{
}

void Recompiler::stwcx_(Instruction code)
{
}

void Recompiler::stwu(Instruction code)
{
    llvm::Value* addr = builder.getInt64(code.ds << 2);
    llvm::Value* rs = getGPR(code.rs);

    addr = builder.CreateAdd(addr, getGPR(code.ra));
    writeMemory(addr, rs);

    setGPR(code.ra, addr);
}

void Recompiler::stwux(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rs = getGPR(code.rs);

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    writeMemory(addr, rs);

    setGPR(code.ra, addr);
}

void Recompiler::stwx(Instruction code)
{
    llvm::Value* addr;
    llvm::Value* rs = getGPR(code.rs);

    addr = builder.CreateAdd(getGPR(code.ra), getGPR(code.rb));
    writeMemory(addr, rs);
}

void Recompiler::eieio(Instruction code)
{
}

void Recompiler::sync(Instruction code)
{
}

void Recompiler::isync(Instruction code)
{
}

}  // namespace ppu
}  // namespace cpu
