#pragma once

// #include "GPCS4Common.h"
#include "PsslProgramInfo.h"
#include "GCNCompiler.h"
#include "GCNDecoder.h"

#include "rend/starsha/orbital/gca/gcn_parser.h"
#include "rend/starsha/orbital/gca/gcn_analyzer.h"

namespace pssl
{;

class SpirvCodeBuffer;

class PsslShaderModule
{
public:
	PsslShaderModule(const uint32_t* code);
	PsslShaderModule(const uint32_t* code, const uint32_t* fsCode);
	~PsslShaderModule();

	std::vector<VertexInputSemantic> vsInputSemantic();

	std::vector<InputUsageSlot> inputUsageSlots();

	const PsslProgramInfo &programInfo();

	PsslKey key();

	SpirvCodeBuffer compile();

private:

	void analyzeCode();

	SpirvCodeBuffer compileWithFS();
	SpirvCodeBuffer compileNoFS();

	void runCompiler(GCNCompiler& compiler, GCNCodeSlice slice);

	// Fetch Shader parsing functions
	void parseFetchShader(const uint32_t* fsCode);
	void decodeFetchShader(GCNCodeSlice slice, PsslFetchShader& fsShader);
	void extractInputSemantic(PsslFetchShader& fsShader);

	// Debug only
	void dumpShader(PsslProgramType type, const uint8_t* code, uint32_t size);
private:
	const uint32_t* m_code;

	PsslProgramInfo m_progInfo;

	std::vector<VertexInputSemantic> m_vsInputSemantic;

	gcn_parser_t m_parser{};
	gcn_analyzer_t m_analyzer{};
};



}
