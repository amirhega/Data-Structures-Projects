//
// CS104 Merge Sort Runtime Tests
//
#include "comparators.h"

#include <msort.h>

#include <gtest/gtest.h>

#include <functional>

#include <runtime_evaluator.h>
#include <random_generator.h>

TEST(MergeSortRuntime, Runtime)
{
	intCompareLess comparator;

	RuntimeEvaluator evaluator("mergeSort()", 1, 21, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		std::vector<int> data = makeRandomIntVector(numElements, seed, true);

		BenchmarkTimer timer;
		mergeSort(data, comparator);
		timer.stop();

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.3);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEARITHMIC));
}

