/** Nimbly Tester
 * Version: 2.0
 *
 * Allows running tests and custom code for Nimbly.
 *
 * Author(s): Jason C. McDonald
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

////#include "goldilocks/goldilocks_shell.hpp"
#include <iostream>

#include "goldilocks/shell.hpp"
#include "iosqueak/channel.hpp"

#include "nimbly/tests/flexarray_tests.hpp"
#include "nimbly/tests/flexqueue_tests.hpp"
#include "nimbly/tests/flexstack_tests.hpp"
#include "nimbly/tests/pool_tests.hpp"

//#include "nimbly/experimental/tests/flexbit_tests.hpp"

/** Temporary test code goes in this function ONLY.
 * All test code that is needed long term should be
 * moved to a dedicated Nimbly Test and Suite.
 */
void test_code()
{

}

/////// WARNING: DO NOT ALTER BELOW THIS POINT! ///////

int main(int argc, char* argv[])
{
	// Return code.
	int r = 0;

	// Set up signal handling.
	channel.configure_echo(IOEchoMode::cout);

	GoldilocksShell* shell = new GoldilocksShell(">> ");
	shell->register_suite<TestSuite_FlexArray>("N-sB01");
	shell->register_suite<TestSuite_FlexQueue>("N-sB02");
	shell->register_suite<TestSuite_FlexStack>("N-sB03");
	shell->register_suite<TestSuite_Pool>("N-sB04");
	//shell->register_suite<TestSuite_FlexBit>("N-sB05");

	// If we got command-line arguments.
	if(argc > 1)
	{
		r = shell->command(argc, argv);
	}
	else
	{
		channel << IOFormatTextAttr::bold << IOFormatTextFG::blue
			<< "===== Nimbly Tester =====\n" << IOCtrl::endl;

		test_code();

		// Shift control to the interactive console.
		shell->interactive();
	}

	// Delete our GoldilocksShell.
	delete shell;

	test_code();

	return r;
}
