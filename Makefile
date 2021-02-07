# Top Level Makefile (MousePaw Media Build System)
# Version: 2.1.0
# Tailored For: Nimbly
#
# Author(s): Jason C. McDonald

# LICENSE (BSD-3-Clause)
# Copyright (c) 2018 MousePaw Media.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors
# may be used to endorse or promote products derived from this software without
# specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
# THE POSSIBILITY OF SUCH DAMAGE.
#
# CONTRIBUTING
# See https://www.mousepawmedia.com/developers for information
# on how to contribute to our projects.

MK_DIR = @cmake -E make_directory
CH_DIR = @cmake -E chdir
CP = @cmake -E copy
CP_DIR = @cmake -E copy_directory
RM = @cmake -E remove
RM_DIR = @cmake -E remove_directory
ECHO = @cmake -E echo
LN = @cmake -E create_symlink

none: help

help:
	$(ECHO) "=== Nimbly 1.3 ==="
	$(ECHO) "Select a build target:"
	$(ECHO) "  make ready         Build Nimbly and bundles it for distribution."
	$(ECHO) "  make clean         Clean up Nimbly and Tester."
	$(ECHO) "  make cleandebug    Clean up Nimbly and Tester Debug."
	$(ECHO) "  make cleanrelease  Clean up Nimbly and Tester Release."
	$(ECHO) "  make docs          Generate HTML docs."
	$(ECHO) "  make docs_pdf      Generate PDF docs."
	$(ECHO) "  make nimbly        Build Nimbly as release."
	$(ECHO) "  make nimbly_debug  Build Nimbly as debug."
	$(ECHO) "  make tester        Build Nimbly Tester (+Nimbly) as release."
	$(ECHO) "  make tester_debug  Build Nimbly Tester (+Nimbly) as debug."
	$(ECHO) "  make all           Build everything."
	$(ECHO) "  make allfresh      Clean and rebuild everything."
	$(ECHO)
	$(ECHO) "Clang Sanitizers (requires Debug build and Clang.)"
	$(ECHO) "  SAN=address     Use AddressSanitizer"
	$(ECHO) "  SAN=leak        Use LeakSanitizer w/o AddressSanitizer (Linux only)"
	$(ECHO) "  SAN=memory      Use MemorySanitizer"
	$(ECHO) "  SAN=thread      Use ThreadSanitizer"
	$(ECHO) "  SAN=undefined   Use UndefiniedBehaviorSanitizer"
	$(ECHO)
	$(ECHO) "Optional Architecture"
	$(ECHO) "  ARCH=32         Make x86 build (-m32)"
	$(ECHO) "  ARCH=64         Make x64 build (-m64)"
	$(ECHO)
	$(ECHO) "Use Configuration File"
	$(ECHO) "  CONFIG=foo      Uses the configuration file 'foo.config'"
	$(ECHO) "                  in the root of this repository."
	$(ECHO) "  When unspecified, default.config will be used."
	$(ECHO)
	$(ECHO) "For other build options, see the 'make' command in 'docs/', 'nimbly-source/', and 'nimbly-tester/'."

clean:
	$(MAKE) clean -C nimbly-source
	$(MAKE) clean -C nimbly-tester
	$(RM) tester_debug
	$(RM) tester

cleanall: clean
	$(MAKE) clean -C docs

cleandebug:
	$(MAKE) cleandebug -C nimbly-source
	$(MAKE) cleandebug -C nimbly-tester
	$(RM) tester_debug

cleanrelease:
	$(MAKE) cleanrelease -C nimbly-source
	$(MAKE) cleanrelease -C nimbly-tester
	$(RM) tester

docs:
	$(RM_DIR) docs/build/html
	$(MAKE) html -C docs
	$(ECHO) "-------------"
	$(ECHO) "<<<<<<< FINISHED >>>>>>>"
	$(ECHO) "View docs at 'docs/build/html/index.html'."
	$(ECHO) "-------------"

docs_pdf:
	$(MAKE) latexpdf -C docs
	$(ECHO) "-------------"
	$(ECHO) "<<<<<<< FINISHED >>>>>>>"
	$(ECHO) "View docs at 'docs/build/latex/Nimbly.pdf'."
	$(ECHO) "-------------"

nimbly:
	$(MAKE) release -C nimbly-source
	$(ECHO) "-------------"
	$(ECHO) "<<<<<<< FINISHED >>>>>>>"
	$(ECHO) "Nimbly is in 'nimbly-source/lib/Release'."
	$(ECHO) "-------------"

nimbly_debug:
	$(MAKE) debug -C nimbly-source
	$(ECHO) "-------------"
	$(ECHO) "<<<<<<< FINISHED >>>>>>>"
	$(ECHO)  on "Nimbly is in 'nimbly-source/lib/Debug'."
	$(ECHO) "-------------"

minimal:
	$(RM_DIR) nimbly
	$(ECHO) "Creating file structure..."
	$(MK_DIR) nimbly/include/nimbly
	$(ECHO) "Copying Nimbly Minimal..."
	$(CP) nimbly-source/include/nimbly/core_types.hpp nimbly/include/nimbly/core_types.hpp
	$(ECHO) "Copying README and LICENSE..."
	$(CP) README.md nimbly/README.md
	$(CP) LICENSE.md nimbly/LICENSE.md
	$(ECHO) "-------------"
	$(ECHO) "<<<<<<< FINISHED >>>>>>>"
	$(ECHO) "The header-only library is in 'nimbly'."
	$(ECHO) "-------------"

ready: nimbly
	$(RM_DIR) nimbly
	$(ECHO) "Creating file structure..."
	$(MK_DIR) nimbly
	$(ECHO) "Copying Nimbly..."
	$(CP_DIR) nimbly-source/include/ nimbly/include/
	$(CP_DIR) nimbly-source/lib/Release/ nimbly/lib/
	$(ECHO) "Copying README and LICENSE..."
	$(CP) README.md nimbly/README.md
	$(CP) LICENSE.md nimbly/LICENSE.md
	$(ECHO) "-------------"
	$(ECHO) "<<<<<<< FINISHED >>>>>>>"
	$(ECHO) "The libraries are in 'nimbly'."
	$(ECHO) "-------------"

tester: nimbly
	$(MAKE) release -C nimbly-tester
	$(RM) tester
	$(LN) nimbly-tester/bin/Release/nimbly-tester tester
	$(ECHO) "-------------"
	$(ECHO) "<<<<<<< FINISHED >>>>>>>"
	$(ECHO) "Nimbly Tester is in 'nimbly-tester/bin/Release'."
	$(ECHO) "The link './tester' has been created for convenience."
	$(ECHO) "-------------"


tester_debug: nimbly_debug
	$(MAKE) debug -C nimbly-tester
	$(RM) tester_debug
	$(LN) nimbly-tester/bin/Debug/nimbly-tester tester_debug
	$(ECHO) "-------------"
	$(ECHO) "<<<<<<< FINISHED >>>>>>>"
	$(ECHO) "Nimbly Tester is in 'nimbly-tester/bin/Debug'."
	$(ECHO) "The link './tester_debug' has been created for convenience."
	$(ECHO) "-------------"

all: docs tester

allfresh: cleanall all

.PHONY: all allfresh clean cleanall cleandebug cleanrelease docs docs_pdf nimbly nimbly_debug ready tester tester_debug
