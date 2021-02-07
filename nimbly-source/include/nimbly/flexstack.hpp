/** FlexStack [Nimbly]
 * Version: 2.0
 *
 * A Flex-based stack with a low dynamic allocation demand.
 *
 * Author(s): Jason C. McDonald, Michael Parkman,
 *            Jonathan Theodore, Moshe Uminer
 */

/* LICENSE (BSD-3-Clause)
 * Copyright (c) 2016-2021 MousePaw Media.
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

#ifndef NIMBLY_FLEXSTACK_HPP
#define NIMBLY_FLEXSTACK_HPP

#include "iosqueak/channel.hpp"

#include "nimbly/core/flex.hpp"

template<typename type, bool raw_copy = false, bool factor_double = true>
class FlexStack : public Flex<type, raw_copy, factor_double>
{
public:
	FlexStack() : Flex<type, raw_copy, factor_double>() {}

	// cppcheck-suppress noExplicitConstructor
	FlexStack(size_t numElements)
	: Flex<type, raw_copy, factor_double>(numElements)
	{
	}

	/** Add the specified element to the FlexStack.
	 * This is just an alias for push()
	 * \param the element to add.
	 * \return true if successful, else false.
	 */
	bool push_back(type& newElement) { return push(std::move(newElement)); }

	/** Add the specified element to the FlexStack.
	 * This is just an alias for push()
	 * \param the element to add.
	 * \return true if successful, else false.
	 */
	bool push_back(type&& newElement) { return push(std::move(newElement)); }

	/** Add the specified element to the FlexStack.
	 * \param the element to add.
	 * \return true if successful, else false.
	 */
	bool push(type& newElement) { return push(std::move(newElement)); }

	/** Add the specified element to the FlexStack.
	 * \param the element to add.
	 * \return true if successful, else false.
	 */
	bool push(type&& newElement)
	{
		/* Use the deque tail insertion function.
		 * Use that function's error messages.
		 */
		return this->insertAtTail(std::move(newElement), true);
	}

	/** Returns the next (last) element in the FlexStack without
	 * modifying the data structure.
	 * \return the next element in the FlexStack.
	 */
	type& peek()
	{
		// If the stack is empty
		if (this->isEmpty()) {
			// Throw a fatal error.
			throw std::out_of_range(
				"FlexStack: Cannot peek() from empty FlexStack.");
		}

		return this->getFromTail();
	}

	const type& peek() const
	{
		// If the stack is empty
		if (this->isEmpty()) {
			// Throw a fatal error.
			throw std::out_of_range(
				"FlexStack: Cannot peek() from empty FlexStack.");
		}

		return this->getFromTail();
	}

	/** Return and remove the next element in the FlexStack.
	 * This is just an alias for pop()
	 * \return the next (last) element, now removed.
	 */
	type pop_back() { return pop(); }

	/** Return and remove the next element in the FlexStack.
	 * \return the next (last) element, now removed.
	 */
	type pop()
	{
		// If the stack is empty...
		if (this->isEmpty()) {
			// Throw a fatal error.
			throw std::out_of_range(
				"FlexStack: Cannot pop() from empty FlexStack.");
		}
		// Get the current element at the tail.
		type temp = this->getFromTail();
		// Remove the tail element.
		this->removeAtTail();
		// Return the element we stored.
		return temp;
	}
};

#endif  // NIMBLY_FLEXSTACK_HPP
