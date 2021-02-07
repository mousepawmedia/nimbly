/** Tests for FlexArray [Nimbly]
 * Version: 1.1
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

#ifndef NIMBLY_FLEXARRAY_TESTS_HPP
#define NIMBLY_FLEXARRAY_TESTS_HPP

#include <vector>

#include "goldilocks/goldilocks.hpp"
#include "goldilocks/assertions.hpp"

#include "nimbly/flexarray.hpp"

// N-tB0101*
class TestVector_Push : public Test
{
private:
	unsigned int iters;

	// Create instance of vector.
	std::vector<unsigned int> vec;

public:
	explicit TestVector_Push(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexArray: Push " + stringify(iters, IOFormatBase::dec) +
			   " Integers (std::vector)";
	}

	testdoc_t get_docs() override
	{
		return "Insert " + stringify(iters, IOFormatBase::dec) +
			   " integers at the back of a vector (push).";
	}

	bool run() override
	{
		// Insert each required element via a push.
		for (unsigned int i = 0; i < iters; ++i) {
			vec.push_back(i);
		}
		return true;
	}

	bool verify() override
	{
		for (unsigned int i = 0; i < iters; ++i) {
			if (vec[i] != i) {
				return false;
			}
		}
		return true;
	}

	bool janitor() override
	{
		vec.clear();
		return true;
	}

	~TestVector_Push() {}
};

// N-tB0101, N-tS0101
class TestFArray_Push : public Test
{
private:
	unsigned int iters;
	// Create instance of FlexArray.
	FlexArray<unsigned int> flex;

public:
	explicit TestFArray_Push(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexArray: Push " + stringify(iters, IOFormatBase::dec) +
			   " Integers (FlexArray)";
	}
	testdoc_t get_docs() override
	{
		return "Insert " + stringify(iters, IOFormatBase::dec) +
			   " integers at the back of a FlexArray (push).";
	}

	bool run() override
	{
		// Insert each required element via a push.
		for (unsigned int i = 0; i < iters; ++i) {
			// Attempt a push. If it fails...
			if (!flex.push(i)) {
				// Report failure.
				return false;
			}
		}
		// Report success.
		return true;
	}

	bool run_optimized() override
	{
		// Insert each required element via a push.
		for (unsigned int i = 0; i < iters; ++i) {
			flex.push(i);
		}
		// Report success.
		return true;
	}

	bool verify() override
	{
		for (unsigned int i = 0; i < iters; ++i) {
			// if the value pushed isn't found at the end...
			// if(flex[i] != i)
			if (flex[i] != i) {
				// Report failure.
				channel << "Incorrect push." << IOCtrl::n
						<< "    expected = " << i << IOCtrl::n
						<< "         got = " << flex.peek() << IOCtrl::endl;
				return false;
			}
		}
		return true;
	}

	bool janitor() override { return flex.clear(); }

	~TestFArray_Push() {}
};

// N-tB0102*
class TestVector_Shift : public Test
{
public:
	explicit TestVector_Shift(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexArray: Shift " + stringify(iters, IOFormatBase::dec) +
			   " Integers to Front (std::vector)";
	}

	testdoc_t get_docs() override
	{
		return "Insert " + stringify(iters, IOFormatBase::dec) +
			   " integers at the front of a vector (shift).";
	}

	bool run() override
	{
		// Create instance of vector.
		std::vector<unsigned int> vec;

		// Insert each required element via a shift.
		for (unsigned int i = 0; i < iters; ++i) {
			vec.insert(vec.begin(), i);
			if (vec[0] != i || (i > 0 && vec[1] != i - 1)) {
				return false;
			}
		}
		return true;
	}

	bool run_optimized() override
	{
		// Create instance of vector.
		std::vector<unsigned int> vec;

		// Insert each required element via a shift.
		for (unsigned int i = 0; i < iters; ++i) {
			vec.insert(vec.begin(), i);
		}
		return true;
	}

	~TestVector_Shift() {}

private:
	unsigned int iters;
};

// N-tB0102, N-tS0102
class TestFArray_Shift : public Test
{
private:
	unsigned int iters;

public:
	explicit TestFArray_Shift(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexArray: Shift " + stringify(iters, IOFormatBase::dec) +
			   " Integers to Front (FlexArray)";
	}

	testdoc_t get_docs() override
	{
		return "Insert " + stringify(iters, IOFormatBase::dec) +
			   " integers at the front of a FlexArray (shift).";
	}

	bool run() override
	{
		// Create instance of FlexArray.
		FlexArray<unsigned int> flex;

		// Insert each required element via a shift.
		for (unsigned int i = 0; i < iters; ++i) {
			// Attempt a shift. If it fails...
			if (!flex.shift(i)) {
				// Report failure.
				return false;
			}
			// If things didn't shift correctly...
			if (flex[0] != i || (i > 0 && flex[1] != i - 1)) {
				// Report failure
				channel << "Incorrect shift." << IOCtrl::n
						<< "      expected = " << i << IOCtrl::n
						<< "           got = " << flex[0] << IOCtrl::n
						<< " f[1] expected = " << i - 1 << IOCtrl::n
						<< "      f[1] got = " << flex[1] << IOCtrl::endl;
				return false;
			}
		}
		return true;
	}

	bool run_optimized() override
	{
		// Create instance of FlexArray.
		FlexArray<unsigned int> flex;

		// Insert each required element via a shift.
		for (unsigned int i = 0; i < iters; ++i) {
			flex.shift(i);
		}
		return true;
	}

	~TestFArray_Shift() {}
};

// N-tB0103*
class TestVector_Insert : public Test
{
private:
	unsigned int iters;
	std::vector<unsigned int> vec;

public:
	explicit TestVector_Insert(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexArray: Insert " + stringify(iters, IOFormatBase::dec) +
			   " Integers At Middle (std::vector)";
	}

	testdoc_t get_docs() override
	{
		return "Insert " + stringify(iters, IOFormatBase::dec) +
			   " integers at the middle of a vector. Middle \
is calculated as size()/2.";
	}

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		vec.clear();
		// We initially push two values, to make the
		// math calculating the insert index a bit safer.
		vec.push_back(0);
		vec.push_back(1);
		return true;
	}

	bool run() override
	{
		// Insert each required element.
		for (unsigned int val = 1; val < 1000; ++val) {
			unsigned int at = vec.size() / 2;
			vec.insert(vec.begin() + at, val);
			if (vec[at] != val || vec.back() != 1) {
				return false;
			}
		}
		return true;
	}

	bool run_optimized() override
	{
		// Insert each required element.
		for (unsigned int val = 1; val < 1000; ++val) {
			unsigned int at = vec.size() / 2;
			vec.insert(vec.begin() + at, val);
		}
		return true;
	}

	~TestVector_Insert() {}
};

// N-tB0103, N-tS0103
class TestFArray_Insert : public Test
{
private:
	unsigned int iters;
	// Create instance of FlexArray.
	FlexArray<unsigned int> flex;

public:
	explicit TestFArray_Insert(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexArray: Insert " + stringify(iters, IOFormatBase::dec) +
			   " Integers At Middle (FlexArray)";
	}

	testdoc_t get_docs() override
	{
		return "Insert " + stringify(iters, IOFormatBase::dec) +
			   " integers at the middle of a FlexArray. \
Middle is calculated as size()/2.";
	}

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		flex.clear();
		/* We initially push two values, to make the
		 * math calculating the insert index a bit safer.*/
		flex.push(0);
		flex.push(1);
		return true;
	}

	bool run() override
	{
		// Insert each required element.
		for (unsigned int val = 1; val < iters; ++val) {
			int at = flex.length() / 2;

			// Attempt an insert shift. If it fails...
			if (!flex.insert(val, at)) {
				// Report failure.
				return false;
			}
			// If values did not shift/insert correctly.
			if (flex[at] != val || flex.peek() != 1) {
				// Report failure.
				channel << "Incorrect insert." << IOCtrl::n
						<< "      expected = " << val << IOCtrl::n
						<< "           got = " << flex[at] << IOCtrl::n
						<< " expected peek = 1" << IOCtrl::n
						<< "      got peek = " << flex.peek() << IOCtrl::endl;
				return false;
			}
		}

		// Report success.
		return true;
	}

	bool run_optimized() override
	{
		// Insert each required element.
		for (unsigned int val = 1; val < iters; ++val) {
			int at = flex.length() / 2;
			flex.insert(val, at);
		}

		// Report success.
		return true;
	}

	~TestFArray_Insert() {}
};

// N-tB0104*
class TestVector_Yank : public Test
{
private:
	std::vector<unsigned int> vec;

	unsigned int iters;

public:
	explicit TestVector_Yank(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexArray: Erase " + stringify(iters, IOFormatBase::dec) +
			   " Integers Individually (std::vector)";
	}

	testdoc_t get_docs() override
	{
		return "Erase " + stringify(iters, IOFormatBase::dec) +
			   " integers individually at the front of a Vector (pop).";
	}

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		// Fill up the vector.
		for (unsigned int i = 0; i < iters; ++i) {
			vec.push_back(i);
		}
		return true;
	}

	bool run() override
	{
		// Remove and return each element.
		for (unsigned int i = 0; i < iters; ++i) {
			// Store the back element.
			unsigned int temp = vec.back();

			if (temp != vec.back()) {
				// Can't happen. If it does, everything is weird.
				return false;
			}

			// Remove the element.
			vec.pop_back();
		}
		return true;
	}

	bool run_optimized() override
	{
		// Remove and return each element.
		for (unsigned int i = 0; i < iters; ++i) {
			// Access the back element.
			(void)vec.back();

			// Remove the element.
			vec.pop_back();
		}
		return true;
	}

	~TestVector_Yank() {}
};

// N-tB0104, N-tS0104
class TestFArray_Yank : public Test
{
private:
	FlexArray<unsigned int> flex;

	unsigned int iters;

public:
	explicit TestFArray_Yank(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexArray: Yank " + stringify(iters, IOFormatBase::dec) +
			   " Integers (flexarray)";
	}

	testdoc_t get_docs() override
	{
		return "Erase " + stringify(iters, IOFormatBase::dec) +
			   " integers at any given index (yank).";
	}

	bool janitor() override
	{
		flex.clear();

		// Refill the FlexArray.
		for (unsigned int i = 0; i < iters; ++i) {
			if (!flex.push(i)) {
				return false;
			}
		}
		return true;
	}

	bool run() override
	{
		// For each element...
		for (int i = (iters - 1); i >= 0; --i) {
			// Store the element at i.
			unsigned int temp = flex.at(i);
			// If the yanked element isn't what it should be...
			if (flex.yank(i) != temp) {
				// Report failure.
				return false;
			}
		}
		return true;
	}

	bool run_optimized() override
	{
		// For each element...
		for (int i = (iters - 1); i >= 0; --i) {
			// If the yanked element isn't what it should be...
			(void)flex.yank(i);
		}
		return true;
	}

	~TestFArray_Yank() {}
};

// N-tB0105*
class TestVector_Unshift : public Test
{
private:
	std::vector<unsigned int> vec;
	unsigned int iters;

public:
	explicit TestVector_Unshift(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexArray: Unshift " + stringify(iters, IOFormatBase::dec) +
			   " Integers (std::vector)";
	}

	testdoc_t get_docs() override
	{
		return "Unshift " + stringify(iters, IOFormatBase::dec) +
			   " integers from a std::vector.";
	}

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		// Refill the std::queue
		for (unsigned int i = 0; i < iters; ++i) {
			vec.push_back(i);
		}
		return true;
	}

	bool run() override
	{
		for (unsigned int i = 0; i < iters; ++i) {
			unsigned int temp = vec.front();

			// Can't happen, so if it does, things went weird.
			if (vec.front() != temp) {
				return false;
			}

			vec.erase(vec.begin());
		}
		return true;
	}

	bool run_optimized() override
	{
		for (unsigned int i = 0; i < iters; ++i) {
			(void)vec.front();
			vec.erase(vec.begin());
		}
		return true;
	}

	~TestVector_Unshift() {}
};

// N-tB0105, N-tS0105
class TestFArray_Unshift : public Test
{
private:
	FlexArray<unsigned int> flex;
	unsigned int iters;

public:
	explicit TestFArray_Unshift(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexArray: Unshift " + stringify(iters, IOFormatBase::dec) +
			   " Integers (FlexArray)";
	}

	testdoc_t get_docs() override
	{
		return "Unshift " + stringify(iters, IOFormatBase::dec) +
			   " integers from a FlexArray.";
	}

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		// Refill FlexQueue.
		for (unsigned int i = 0; i < iters; ++i) {
			flex.push(i);
		}
		return true;
	}

	bool run() override
	{
		// Pop each element.
		for (unsigned int i = 0; i < iters; ++i) {
			// If the element does not equal the next expected element...
			if (flex.unshift() != i) {
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
			(void)flex.unshift();
		}
		return true;
	}

	~TestFArray_Unshift() {}
};

// N-tB0106*
class TestVector_Pop : public Test
{
private:
	std::vector<unsigned int> vec;
	unsigned int iters;

public:
	explicit TestVector_Pop(unsigned int iterations) : iters(iterations) {}

	// Test title
	testdoc_t get_title() override
	{
		return "FlexArray: Pop " + stringify(iters, IOFormatBase::dec) +
			   " integers from a std::vector.";
	}
	// test documentation
	testdoc_t get_docs() override
	{
		return "Pop " + stringify(iters, IOFormatBase::dec) +
			   " integers from a std::vector.";
	}

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		// Refill the std::vector.
		for (unsigned int i = 0; i < iters; ++i) {
			vec.push_back(i);
		}
		return true;
	}

	bool run() override
	{
		for (unsigned int i = 0; i < iters; ++i) {
			unsigned int temp = vec.back();

			// Can't happen, so if it does, things went weird.
			if (vec.back() != temp) {
				return false;
			}

			vec.pop_back();
		}
		return true;
	}

	bool run_optimized() override
	{
		for (unsigned int i = 0; i < iters; ++i) {
			(void)vec.back();
			vec.pop_back();
		}
		return true;
	}

	~TestVector_Pop() {}
};

// N-tB0106, N-tS0106
class TestFArray_Pop : public Test
{
private:
	FlexArray<unsigned int> flex;
	unsigned int iters;

public:
	explicit TestFArray_Pop(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexArray: Pop " + stringify(iters, IOFormatBase::dec) +
			   " integers from a FlexArray.";
	}

	testdoc_t get_docs() override
	{
		return "Pop " + stringify(iters, IOFormatBase::dec) +
			   " integers from a FlexArray.";
	}

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		// Refill the FlexArray.
		for (unsigned int i = 0; i < iters; ++i) {
			flex.push(i);
		}
		return true;
	}
	bool run() override
	{
		// Pop each element.
		for (unsigned int i = (iters - 1); i; --i) {
			// If the element does not equal the next expected element...
			if (flex.pop() != i) {
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
			(void)flex.pop();
		}
		return true;
	}

	~TestFArray_Pop() {}
};

// N-tB0107, N-tS0107
class TestFArray_Erase : public Test
{
private:
	FlexArray<unsigned int> flex;
	unsigned int iters;

public:
	explicit TestFArray_Erase(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexArray: Erase half of " +
			   stringify(iters, IOFormatBase::dec) +
			   " integers from a FlexArray.";
	}

	testdoc_t get_docs() override
	{
		return "Erase the center half of elements in a " +
			   stringify(iters, IOFormatBase::dec) + " integer-wide FlexArray.";
	}

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		flex.clear();
		// Refill the FlexArray.
		for (unsigned int i = 0; i < iters; ++i) {
			flex.push(i);
		}
		return true;
	}
	bool run() override
	{
		// Calculate erase size as the center half of the elements.
		int first = iters / 4;
		int last = first * 3;
		// Erase in one step.
		return flex.erase(first, last);
	}

	~TestFArray_Erase() {}
};

// N-tB0107*
class TestVector_Erase : public Test
{
private:
	std::vector<unsigned int> vec;
	unsigned int iters;

public:
	explicit TestVector_Erase(unsigned int iterations) : iters(iterations) {}

	testdoc_t get_title() override
	{
		return "FlexArray: Erase half of " +
			   stringify(iters, IOFormatBase::dec) +
			   " integers from a std::vector.";
	}

	testdoc_t get_docs() override
	{
		return "Erase the center half of elements in a " +
			   stringify(iters, IOFormatBase::dec) +
			   " integer-wide std::vector.";
	}

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		// Refill the FlexArray.
		for (unsigned int i = 0; i < iters; ++i) {
			vec.push_back(i);
		}
		return true;
	}
	bool run() override
	{
		// Calculate erase size as the center half of the elements.
		int first = iters / 4;
		int last = first * 3;
		// Erase in one step.
		std::vector<unsigned int>::iterator result =
			vec.erase(vec.begin() + first, vec.begin() + last);
		// If the iterator points to the vector end, there was a problem.
		return (result != vec.end());
	}

	~TestVector_Erase() {}
};

class TestVector_Peek : public Test
{
protected:
	// Create instance of FlexArray.
	std::vector<unsigned int> vec;

	unsigned int expected = 42;
	unsigned int other = 9;

public:
	TestVector_Peek() {}

	testdoc_t get_title() override { return "FlexArray: Peek (std::vector)"; }

	testdoc_t get_docs() override
	{
		return "Access the last element in the vector.";
	}

	bool pre() override
	{
		/* We initially push three values, to make the
		 * math calculating the insert index a bit safer.*/
		vec.push_back(other);
		vec.push_back(other);
		vec.push_back(other);
		vec.push_back(expected);
		return true;
	}

	bool run() override
	{
		(void)vec.back();
		return true;
	}
};

// N-tB0108
class TestFArray_Peek : public Test
{
protected:
	// Create instance of FlexArray.
	FlexArray<unsigned int> flex;

	unsigned int expected = 42;
	unsigned int other = 9;

public:
	TestFArray_Peek() {}

	testdoc_t get_title() override { return "FlexArray: Peek (FlexArray)"; }

	testdoc_t get_docs() override
	{
		return "Ensure the last element is being peeked correctly.";
	}

	bool pre() override
	{
		/* We initially push three values, to make the
		 * math calculating the insert index a bit safer.*/
		flex.push(other);
		flex.push(other);
		flex.push(other);
		flex.push(expected);
		return true;
	}

	bool run() override
	{
		unsigned int peeked = flex.peek();
		if (peeked == expected) {
			// Report success.
			return true;
		} else {
			return false;
		}
	}

	bool run_optimized() override
	{
		(void)flex.peek();
		return true;
	}

	~TestFArray_Peek() {}
};

// N-tB0109
class TestFArray_Contained : public Test
{
protected:
	FlexArray<int> inner;
	FlexArray<FlexArray<int>> outer;

public:
	TestFArray_Contained() {}

	testdoc_t get_title() override { return "FlexArray: Contained"; }

	testdoc_t get_docs() override
	{
		return "Ensure FlexArray handles its memory correctly when contained.";
	}

	bool run() override
	{
		PL_ASSERT_TRUE(outer.push(inner));
		return true;
	}
};

// N-tB0110
class TestFArray_SharedPtr : public Test
{
protected:
	FlexArray<std::shared_ptr<int>> arr;

public:
	TestFArray_SharedPtr() {}

	testdoc_t get_title() override { return "FlexArray: Shared Ptr"; }

	testdoc_t get_docs() override
	{
		return "Ensure FlexArray works correctly with std::shared_ptr.";
	}

	bool run() override
	{
		for (size_t i = 0; i < 10; ++i) {
			PL_ASSERT_TRUE(arr.push(std::make_shared<int>(i)));
		}
		return true;
	}
};

// N-tB0111
class TestFArray_UniquePtr : public Test
{
protected:
	FlexArray<std::unique_ptr<int>> arr;

public:
	TestFArray_UniquePtr() {}

	testdoc_t get_title() override { return "FlexArray: Unique Ptr"; }

	testdoc_t get_docs() override
	{
		return "Ensure FlexArray works correctly with std::unique_ptr.";
	}

	bool run() override
	{
		for (size_t i = 0; i < 10; ++i) {
			PL_ASSERT_TRUE(arr.push_back(std::make_unique<int>(i)));
		}
		return true;
	}
};

class TestSuite_FlexArray : public TestSuite
{
public:
	explicit TestSuite_FlexArray() {}

	void load_tests() override;

	testdoc_t get_title() override { return "PawLIB: FlexArray Tests"; }

	~TestSuite_FlexArray() {}
};

#endif  // NIMBLY_FLEXARRAY_TESTS_HPP
