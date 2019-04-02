/**
* @file src/llvmir2hll/var_name_gen/var_name_gens/word_var_name_gen.cpp
* @brief Implementation of WordVarNameGen.
* @copyright (c) 2017 Avast Software, licensed under the MIT license
*/

#include <llvm/ADT/StringExtras.h>

#include "retdec/llvmir2hll/support/debug.h"
#include "retdec/llvmir2hll/var_name_gen/var_name_gen_factory.h"
#include "retdec/llvmir2hll/var_name_gen/var_name_gens/word_var_name_gen.h"
#include "retdec/utils/array.h"

using retdec::utils::arraySize;

namespace retdec {
namespace llvmir2hll {

REGISTER_AT_FACTORY("word", WORD_VAR_NAME_GEN_ID, VarNameGenFactory,
	WordVarNameGen::create);

namespace {

// A list of all available words.
const char *AVAIL_WORDS[] = {
};

// Index of the last available word.
const std::size_t LAST_WORD_INDEX = arraySize(AVAIL_WORDS) - 1;

} // anonymous namespace

/**
* @brief Constructs a new WordVarNameGen object.
*
* For more details, see create().
*/
WordVarNameGen::WordVarNameGen(std::string prefix):
		VarNameGen(prefix), nextWordIndex(0) {}

/**
* @brief Creates a new WordVarNameGen object.
*
* @param[in] prefix Prefix of all returned variable names.
*/
UPtr<VarNameGen> WordVarNameGen::create(std::string prefix) {
	return UPtr<VarNameGen>(new WordVarNameGen(prefix));
}

std::string WordVarNameGen::getId() const {
	return WORD_VAR_NAME_GEN_ID;
}

void WordVarNameGen::restart() {
	nextWordIndex = 0;
}

std::string WordVarNameGen::getNextVarName() {
	if (nextWordIndex == LAST_WORD_INDEX) {
		// No more available words, so start from the beginning.
		restart();
		return getNextVarName();
	} else {
		return prefix + AVAIL_WORDS[nextWordIndex++];
	}
}

} // namespace llvmir2hll
} // namespace retdec