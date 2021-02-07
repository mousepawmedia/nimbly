/** Tests for FlexQueue [Nimbly]
 * Version: 1.0
 *
 * Author(s): Jason C. McDonald, Jonathan Theodore
 */

/* LICENSE (BSD-3-Clause)
 * Copyright (c) 2016-2019 MousePaw Media.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * CONTRIBUTING
 * See https://www.mousepawmedia.com/developers for information
 * on how to contribute to our projects.
 */

#ifndef NIMBLY_FLEXQUEUE_TESTS_HPP
#define NIMBLY_FLEXQUEUE_TESTS_HPP

#include <queue>

#include "goldilocks/goldilocks.hpp"
#include "goldilocks/assertions.hpp"

#include "nimbly/flexqueue.hpp"

// N-tB0201*
class TestSQueue_Push : public Test
{
private:
	unsigned int iters;

public:
	explicit TestSQueue_Push(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexQueue: Push " + stringify(iters, IOFormatBase::dec) +
			   " Integers (std::vector)";
	}

	testdoc_t get_docs() override
	{
		return "Push " + stringify(iters, IOFormatBase::dec) +
			   " integers to a std::vector.";
	}

	bool run() override
	{
		// Create instance of queue.
		// Technically we must use vector as a queue!
		////std::queue<unsigned int> sq;
		std::vector<unsigned int> sq;

		// Push each required element to the queue.
		for (unsigned int i = 0; i < iters; ++i) {
			sq.push_back(i);
			if (sq.back() != i) {
				return false;
			}
		}
		return true;
	}

	bool run_optimized() override
	{
		// Create instance of queue.
		// Technically we must use vector as a queue!
		////std::queue<unsigned int> sq;
		std::vector<unsigned int> sq;

		// Push each required element to the queue.
		for (unsigned int i = 0; i < iters; ++i) {
			sq.push_back(i);
		}
		return true;
	}

	~TestSQueue_Push() {}
};

// N-tB0201, N-tS0201
class TestFQueue_Push : public Test
{
private:
	unsigned int iters;

public:
	explicit TestFQueue_Push(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexQueue: Push " + stringify(iters, IOFormatBase::dec) +
			   " Integers (FlexQueue)";
	}

	testdoc_t get_docs() override
	{
		return "Push " + stringify(iters, IOFormatBase::dec) +
			   " integers to a FlexQueue.";
	}

	bool run() override
	{
		// Create an instance of FlexQueue.
		FlexQueue<unsigned int> fq;

		// Push each required element.
		for (unsigned int i = 0; i < iters; ++i) {
			// Attempt a push. If it fails...
			if (!fq.push(i)) {
				// Report failure.
				return false;
			}
			// If last value is not what was pushed...
			if (fq.peek() != i) {
				// Report failure.
			}
		}
		return true;
	}

	bool run_optimized() override
	{
		// Create an instance of FlexQueue.
		FlexQueue<unsigned int> fq;

		// Push each required element.
		for (unsigned int i = 0; i < iters; ++i) {
			fq.push(i);
		}
		return true;
	}

	~TestFQueue_Push() {}
};

// N-tB0202
class TestFQueue_Peek : public Test
{
private:
	FlexQueue<int> fq;

public:
	TestFQueue_Peek() {}

	testdoc_t get_title() override { return "FlexQueue: Peek"; }

	testdoc_t get_docs() override
	{
		return "Peek the first of five integers placed into a FlexQueue";
	}

	// Set up for the test.
	bool pre() override
	{
		/* We should set up only once, even if test is repeated
		 * multiple times. */
		for (int i = 1; i <= 5; ++i) {
			fq.push(i);
		}
		return true;
	}

	bool run() override
	{
		// Peek the value.
		int i = fq.peek();

		// If the peeked value is 1, return true; else, false.
		return (i == 1);
	}

	~TestFQueue_Peek() {}
};

// N-tB0203*
class TestSQueue_Pop : public Test
{
private:
	/* We must compare against a std::vector, as std::queue doesn't
	 * use contiguous memory, and cannot be based on std::vector.
	 */
	std::vector<unsigned int> sq;
	unsigned int iters;

public:
	explicit TestSQueue_Pop(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexQueue: Pop " + stringify(iters, IOFormatBase::dec) +
			   " Integers (std::vector)";
	}

	testdoc_t get_docs() override
	{
		return "Pop " + stringify(iters, IOFormatBase::dec) +
			   " integers from a std::vector.";
	}

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		// Refill the std::queue
		for (unsigned int i = 0; i < iters; ++i) {
			sq.push_back(i);
		}
		return true;
	}

	bool run() override
	{
		for (unsigned int i = 0; i < iters; ++i) {
			sq.erase(sq.begin());
		}
		return true;
	}

	bool run_optimized() override
	{
		for (unsigned int i = 0; i < iters; ++i) {
			sq.erase(sq.begin());
		}
		return true;
	}

	~TestSQueue_Pop() {}
};

// N-tB0203, N-tS0203
class TestFQueue_Pop : public Test
{
private:
	FlexQueue<unsigned int> fq;
	unsigned int iters;

public:
	explicit TestFQueue_Pop(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexQueue: Pop " + stringify(iters, IOFormatBase::dec) +
			   " Integers (FlexQueue)";
	}

	testdoc_t get_docs() override
	{
		return "Pop " + stringify(iters, IOFormatBase::dec) +
			   " integers from a FlexQueue.";
	}

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		// Refill FlexQueue.
		for (unsigned int i = 0; i < iters; ++i) {
			fq.push(i);
		}
		return true;
	}

	bool run() override
	{
		// Pop each element.
		for (unsigned int i = 0; i < iters; ++i) {
			// If the element does not equal the next expected element...
			if (fq.pop() != i) {
				// Report failure.
				return false;
			}
		}
		return true;
	}

	bool run_optimized() override
	{
		// Pop each element.
		for (unsigned int i = 0; i < iters; ++i) {
			fq.pop();
		}
		return true;
	}

	~TestFQueue_Pop() {}
};

class TestSuite_FlexQueue : public TestSuite
{
public:
	explicit TestSuite_FlexQueue() {}

	void load_tests() override;

	testdoc_t get_title() override { return "PawLIB: FlexQueue Tests"; }

	~TestSuite_FlexQueue() {}
};

#endif  // NIMBLY_FLEXQUEUE_TESTS_HPP
