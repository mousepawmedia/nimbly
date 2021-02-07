/** Tests for FlexStack [Nimbly]
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

#ifndef NIMBLY_FLEXSTACK_TESTS_HPP
#define NIMBLY_FLEXSTACK_TESTS_HPP

#include <stack>

#include "goldilocks/goldilocks.hpp"
#include "goldilocks/assertions.hpp"

#include "nimbly/flexstack.hpp"

// SStack classes test the standard library version of Stack
// FStack classes test the Nimbly FlexStack

// N-tB0301*
class TestSStack_Push : public Test
{
private:
	unsigned int iters;
	std::stack<unsigned int, std::vector<unsigned int>> stk;

public:
	// TestSStack_PushU with iterators
	explicit TestSStack_Push(unsigned int iterations) : iters(iterations) {}

	// Test title
	testdoc_t get_title() override
	{
		return "FlexStack: Push " + stringify(iters, IOFormatBase::dec) +
			   " Integers (std::stack)";
	}
	// get documentation section
	testdoc_t get_docs() override
	{
		return "Push " + stringify(iters, IOFormatBase::dec) +
			   " integers to a std:;stack.";
	}

	// Run the test
	bool run() override
	{
		for (unsigned int i = 0; i < iters; ++i) {
			stk.push(i);
			if (stk.top() != i) {
				return false;
			}
		}
		return true;
	}

	bool run_optimized() override
	{
		for (unsigned int i = 0; i < iters; ++i) {
			stk.push(i);
		}
		return true;
	}

	~TestSStack_Push() {}
};

// N-tB0301, N-tS0301
class TestFStack_Push : public Test
{
private:
	unsigned int iters;
	FlexStack<unsigned int> fstk;

public:
	explicit TestFStack_Push(unsigned int iterations) : iters(iterations) {}

	// Test title
	testdoc_t get_title() override
	{
		return "FlexStack: Push " + stringify(iters, IOFormatBase::dec) +
			   " Integers (FlexStack)";
	}
	// Test documentation
	testdoc_t get_docs() override
	{
		return "Push " + stringify(iters, IOFormatBase::dec) +
			   " integers to a FlexStack.";
	}
	// Run the test
	bool run() override
	{
		// Insert each required element via a push.
		for (unsigned int i = 0; i < iters; ++i) {
			// Attempt a push. If it fails...
			if (!fstk.push(i)) {
				// Report failure.
				return false;
			}
			// If last value is not what was pushed...
			if (fstk.peek() != i) {
				// Report failure.
			}
		}
		// Report success.
		return true;
	}

	bool run_optimized() override
	{
		// Insert each required element via a push.
		for (unsigned int i = 0; i < iters; ++i) {
			fstk.push(i);
		}
		// Report success.
		return true;
	}

	~TestFStack_Push() {}
};

// N-tB0302
class TestFStack_Peek : public Test
{
private:
	FlexStack<int> fq;

public:
	TestFStack_Peek() {}

	testdoc_t get_title() override { return "FlexStack: Peek"; }

	testdoc_t get_docs() override
	{
		return "FlexStack: Peek the last of five integers placed into a "
			   "FlexStack";
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

		// If the peeked value is 5, return true; else, false.
		return (i == 5);
	}

	~TestFStack_Peek() {}
};

// N-tB0303*
class TestSStack_Pop : public Test
{
private:
	std::stack<unsigned int, std::vector<unsigned int>> stk;
	unsigned int iters;

public:
	explicit TestSStack_Pop(unsigned int iterations) : iters(iterations) {}

	// Test title
	testdoc_t get_title() override
	{
		return "FlexStack: Pop " + stringify(iters, IOFormatBase::dec) +
			   " integers from a std::stack.";
	}
	// test documentation
	testdoc_t get_docs() override
	{
		return "Pop " + stringify(iters, IOFormatBase::dec) +
			   " integers from a std::stack.";
	}

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		// Refill the std::stack.
		for (unsigned int i = 0; i < iters; ++i) {
			stk.push(i);
		}
		return true;
	}

	bool run() override
	{
		for (unsigned int i = 0; i < iters; ++i) {
			unsigned int temp = stk.top();

			// Can't happen, so if it does, things went weird.
			if (stk.top() != temp) {
				return false;
			}

			stk.pop();
		}
		return true;
	}

	bool run_optimized() override
	{
		for (unsigned int i = 0; i < iters; ++i) {
			stk.pop();
		}
		return true;
	}

	~TestSStack_Pop() {}
};

// N-tB0303, N-tS0303
class TestFStack_Pop : public Test
{
private:
	FlexStack<unsigned int> fstk;
	unsigned int iters;

public:
	explicit TestFStack_Pop(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexStack: Pop " + stringify(iters, IOFormatBase::dec) +
			   " integers from a FlexStack.";
	}

	testdoc_t get_docs() override
	{
		return "Pop " + stringify(iters, IOFormatBase::dec) +
			   " integers from a FlexStack.";
	}

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		// Refill the FlexStack.
		for (unsigned int i = 0; i < iters; ++i) {
			fstk.push(i);
		}
		return true;
	}

	bool run() override
	{
		// Pop each element.
		for (unsigned int i = (iters - 1); i; --i) {
			// If the element does not equal the next expected element...
			if (fstk.pop() != i) {
				// Report failure.
				return false;
			}
		}
		return true;
	}

	bool run_optimized() override
	{
		// Pop each element.
		for (unsigned int i = (iters - 1); i; --i) {
			fstk.pop();
		}
		return true;
	}

	~TestFStack_Pop() {}
};

class TestSuite_FlexStack : public TestSuite
{
public:
	explicit TestSuite_FlexStack() {}

	void load_tests() override;

	testdoc_t get_title() override { return "PawLIB: FlexStack Tests"; }

private:
};

#endif  // NIMBLY_FLEXSTACK_TESTS_HPP
