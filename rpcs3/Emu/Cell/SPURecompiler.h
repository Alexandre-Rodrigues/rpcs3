#pragma once

#include "SPUThread.h"

// SPU Recompiler instance base class
class spu_recompiler_base
{
protected:
	SPUThread& m_spu;

	u32 m_pos;

public:
	spu_recompiler_base(SPUThread& spu);

	virtual ~spu_recompiler_base();

	// Compile function
	virtual spu_function_t compile(const std::vector<u32>& func) = 0;

	// Default dispatch function fallback (second pointer is unused)
	static void dispatch(SPUThread&, void*, u8*);

	// Direct branch fallback for non-compiled destination
	static void branch(SPUThread&, std::pair<const std::vector<u32>, spu_function_t>*, u8* rip);

	// Get the block at specified address
	static std::vector<u32> block(SPUThread&, u32 lsa);

	// Create recompiler instance (ASMJIT)
	static std::unique_ptr<spu_recompiler_base> make_asmjit_recompiler(SPUThread& spu);
};
