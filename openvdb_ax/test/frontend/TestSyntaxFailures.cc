///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2015-2018 DNEG Visual Effects
//
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
//
// Redistributions of source code must retain the above copyright
// and license notice and the following restrictions and disclaimer.
//
// *     Neither the name of DNEG Visual Effects nor the names
// of its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// IN NO EVENT SHALL THE COPYRIGHT HOLDERS' AND CONTRIBUTORS' AGGREGATE
// LIABILITY FOR ALL CLAIMS REGARDLESS OF THEIR BASIS EXCEED US$250.00.
//
///////////////////////////////////////////////////////////////////////////

#include <cppunit/extensions/HelperMacros.h>

#include <openvdb_ax/compiler/Compiler.h>
#include <openvdb_ax/Exceptions.h>

#include <string>

#include "test/util.h"

namespace {

#define EXPECTED_FAILURE() \
    unittest_util::ExpectedBase::Ptr(new unittest_util::ExpectedType<>())

static const unittest_util::CodeTests tests =
{
    // invalid r-value syntax
    { "@a = @;",                       EXPECTED_FAILURE() },
    { "@a = =;",                       EXPECTED_FAILURE() },
    { "@a = +;",                       EXPECTED_FAILURE() },
    { "@a = -;",                       EXPECTED_FAILURE() },
    { "@a = *;",                       EXPECTED_FAILURE() },
    { "@a = /;",                       EXPECTED_FAILURE() },
    { "@a = %;",                       EXPECTED_FAILURE() },
    { "@a = |;",                       EXPECTED_FAILURE() },
    { "@a = &;",                       EXPECTED_FAILURE() },
    { "@a = ^;",                       EXPECTED_FAILURE() },
    { "@a = ~;",                       EXPECTED_FAILURE() },
    { "@a = ==;",                      EXPECTED_FAILURE() },
    { "@a = !=;",                      EXPECTED_FAILURE() },
    { "@a = >;",                       EXPECTED_FAILURE() },
    { "@a = <;",                       EXPECTED_FAILURE() },
    { "@a = >=;",                      EXPECTED_FAILURE() },
    { "@a = <=;",                      EXPECTED_FAILURE() },
    { "@a = +=;",                      EXPECTED_FAILURE() },
    { "@a = -=;",                      EXPECTED_FAILURE() },
    { "@a = *=;",                      EXPECTED_FAILURE() },
    { "@a = /=;",                      EXPECTED_FAILURE() },
    { "@a = ++;",                      EXPECTED_FAILURE() },
    { "@a = --;",                      EXPECTED_FAILURE() },
    { "@a = &&;",                      EXPECTED_FAILURE() },
    { "@a = ||;",                      EXPECTED_FAILURE() },
    { "@a = !;",                       EXPECTED_FAILURE() },
    { "@a = ,;",                       EXPECTED_FAILURE() },
    { "@a = (;",                       EXPECTED_FAILURE() },
    { "@a = );",                       EXPECTED_FAILURE() },
    { "@a = {;",                       EXPECTED_FAILURE() },
    { "@a =};",                        EXPECTED_FAILURE() },
    { "@a = .x;",                      EXPECTED_FAILURE() },
    { "@a = .y;",                      EXPECTED_FAILURE() },
    { "@a = .z;",                      EXPECTED_FAILURE() },
    { "@a = .r;",                      EXPECTED_FAILURE() },
    { "@a = .g;",                      EXPECTED_FAILURE() },
    { "@a = .b;",                      EXPECTED_FAILURE() },
    { "@a = f@;",                      EXPECTED_FAILURE() },
    { "@a = i@;",                      EXPECTED_FAILURE() },
    { "@a = v@;",                      EXPECTED_FAILURE() },
    { "@a = s@;",                      EXPECTED_FAILURE() },
    { "@a = if;",                      EXPECTED_FAILURE() },
    { "@a = else;",                    EXPECTED_FAILURE() },
    { "@a = return;",                  EXPECTED_FAILURE() },
    { "@a = ;",                        EXPECTED_FAILURE() },
    { "@a = {};",                      EXPECTED_FAILURE() },
    { "@a = {1};",                     EXPECTED_FAILURE() },
    { "@a = \"a;",                     EXPECTED_FAILURE() },
    { "v@a[0] = 0;",                   EXPECTED_FAILURE() },
    { "v@a.a = 0;",                    EXPECTED_FAILURE() },

    // invalid l-value
    // TODO: these should fail syntax tests
    // {"+@a = 0;",                   EXPECTED_FAILURE() },
    // {"-@a = 0;",                   EXPECTED_FAILURE() },
    // {"~@a = 0;",                   EXPECTED_FAILURE() },
    // {"!@a = 0;",                   EXPECTED_FAILURE() },
    { "++@a = 0;",                     EXPECTED_FAILURE() },
    { "--@a = 0;",                     EXPECTED_FAILURE() },
    { "=@a;",                          EXPECTED_FAILURE() },
    { "*@a;",                          EXPECTED_FAILURE() },
    { "/@a;",                          EXPECTED_FAILURE() },
    { "%@a;",                          EXPECTED_FAILURE() },
    { "|@a;",                          EXPECTED_FAILURE() },
    { "&@a;",                          EXPECTED_FAILURE() },
    { "^@a;",                          EXPECTED_FAILURE() },
    { "==@a;",                         EXPECTED_FAILURE() },
    { "!=@a;",                         EXPECTED_FAILURE() },
    { ">@a;",                          EXPECTED_FAILURE() },
    { "<@a;",                          EXPECTED_FAILURE() },
    { ">=@a;",                         EXPECTED_FAILURE() },
    { "<=@a;",                         EXPECTED_FAILURE() },
    { "+=@a;",                         EXPECTED_FAILURE() },
    { "-=@a;",                         EXPECTED_FAILURE() },
    { "*=@a;",                         EXPECTED_FAILURE() },
    { "/=@a;",                         EXPECTED_FAILURE() },
    { "&&@a;",                         EXPECTED_FAILURE() },
    { "||@a;",                         EXPECTED_FAILURE() },
    { ",@a;",                          EXPECTED_FAILURE() },
    { "(@a;",                          EXPECTED_FAILURE() },
    { ")@a;",                          EXPECTED_FAILURE() },
    { "{@a;",                          EXPECTED_FAILURE() },
    { "}@a;",                          EXPECTED_FAILURE() },
    { ".x@a;",                         EXPECTED_FAILURE() },
    { ".y@a;",                         EXPECTED_FAILURE() },
    { ".z@a;",                         EXPECTED_FAILURE() },
    { ".r@a;",                         EXPECTED_FAILURE() },
    { ".g@a;",                         EXPECTED_FAILURE() },
    { ".b@a;",                         EXPECTED_FAILURE() },
    { "@@a;",                          EXPECTED_FAILURE() },
    { "f@@a;",                         EXPECTED_FAILURE() },
    { "i@@a;",                         EXPECTED_FAILURE() },
    { "v@@a;",                         EXPECTED_FAILURE() },
    { "s@@a;",                         EXPECTED_FAILURE() },
    { "if@a;",                         EXPECTED_FAILURE() },
    { "else@a;",                       EXPECTED_FAILURE() },
    { "return@a;",                     EXPECTED_FAILURE() },
    { "{}@a;",                         EXPECTED_FAILURE() },
    { "{1}@a;",                        EXPECTED_FAILURE() },
    { "\"a\"@a;",                      EXPECTED_FAILURE() },
    { "b@a;",                          EXPECTED_FAILURE() },
    { "sht@a;",                        EXPECTED_FAILURE() },
    { "it@a;",                         EXPECTED_FAILURE() },
    { "l@a;",                          EXPECTED_FAILURE() },
    { "flt@a;",                        EXPECTED_FAILURE() },
    { "dbl@a;",                        EXPECTED_FAILURE() },
    { "vecint@a;",                     EXPECTED_FAILURE() },
    { "vint@a;",                       EXPECTED_FAILURE() },
    { "vfloat@a;",                     EXPECTED_FAILURE() },
    { "vecflt@a;",                     EXPECTED_FAILURE() },
    { "vflt@a;",                       EXPECTED_FAILURE() },
    { "vdouble@a;",                    EXPECTED_FAILURE() },
    { "vecdbl@a;",                     EXPECTED_FAILURE() },
    { "vdbl@a;",                       EXPECTED_FAILURE() },
    { "str@a;",                        EXPECTED_FAILURE() },
    { "a ! a;",                        EXPECTED_FAILURE() },
    { "a ~ a;",                        EXPECTED_FAILURE() },
    { "a \\ a;",                       EXPECTED_FAILURE() },
    { "a ? a;",                        EXPECTED_FAILURE() },
    { "bool + a;",                     EXPECTED_FAILURE() },
    { "bool a + a;",                   EXPECTED_FAILURE() },
    { "return + a;",                   EXPECTED_FAILURE() },
    { "if + a;",                       EXPECTED_FAILURE() },
    { "a + if(true) {};",              EXPECTED_FAILURE() },
    { "{} + {};",                      EXPECTED_FAILURE() },
    { "~ + !;",                        EXPECTED_FAILURE() },
    { "+ + -;",                        EXPECTED_FAILURE() },
    { "; + ;",                         EXPECTED_FAILURE() },
    { "int();",                        EXPECTED_FAILURE() },
    { "int(return);",                  EXPECTED_FAILURE() },
    { "int(if(true) {});",             EXPECTED_FAILURE() },
    { "int(;);",                       EXPECTED_FAILURE() },
    { "int(bool a;);",                 EXPECTED_FAILURE() },
    { "int(bool a);",                  EXPECTED_FAILURE() },
    { "int{a};",                       EXPECTED_FAILURE() },
    { "int[a];",                       EXPECTED_FAILURE() },
    { "string(a);",                    EXPECTED_FAILURE() },
    { "vector(a);",                    EXPECTED_FAILURE() },
    { "vec3i(a);",                     EXPECTED_FAILURE() },
    { "vec3f(a);",                     EXPECTED_FAILURE() },
    { "vec3d(a);",                     EXPECTED_FAILURE() },

    // invalid if block
    { "if (a) {b}",                    EXPECTED_FAILURE() },
    { "if (a) else ();",               EXPECTED_FAILURE() },
    { "if (); else (a);",              EXPECTED_FAILURE() },
    { "if (a) if(b) {if (c)} else {}", EXPECTED_FAILURE() },
    { "if (if(a));",                   EXPECTED_FAILURE() },
    { "if ();",                        EXPECTED_FAILURE() },
    { "if (); else ;",                 EXPECTED_FAILURE() },
    { "if (); else ();",               EXPECTED_FAILURE() },
    { "if (); else () {}",             EXPECTED_FAILURE() },
    { "if (); elf {}",                 EXPECTED_FAILURE() },
    { "if (a) {} elif (b) {}",         EXPECTED_FAILURE() },
    { "else {}",                       EXPECTED_FAILURE() },
    { "else ;",                        EXPECTED_FAILURE() },
    { "if a;",                         EXPECTED_FAILURE() },
    { "if a {} elif b {}",             EXPECTED_FAILURE() },
    { "if (a); else ; else ;",         EXPECTED_FAILURE() },
    { "else (a); ",                    EXPECTED_FAILURE() },
    { "if (a) {}; else {};",           EXPECTED_FAILURE() },
    { "if (a) {b = 1} else {};",       EXPECTED_FAILURE() },
    { "if (a) {} ; else {}",           EXPECTED_FAILURE() },
    { "if () {}; else (a);",           EXPECTED_FAILURE() },

    // invalid crement
    { "++5;",                          EXPECTED_FAILURE() },
    { "5++;",                          EXPECTED_FAILURE() },
    { "--5;",                          EXPECTED_FAILURE() },
    { "5--;",                          EXPECTED_FAILURE() },
    { "++5--;",                        EXPECTED_FAILURE() },
    { "++5++;",                        EXPECTED_FAILURE() },
    { "--5++;",                        EXPECTED_FAILURE() },
    { "--5--;",                        EXPECTED_FAILURE() },
    { "{ 1, 1, 1}++;",                 EXPECTED_FAILURE() },
    { "++{ 1, 1, 1};",                 EXPECTED_FAILURE() },
    { "--{ 1, 1, 1};",                 EXPECTED_FAILURE() },
    { "{ 1, 1, 1}--;",                 EXPECTED_FAILURE() },
    { "++{ 1, 1, 1}++;",               EXPECTED_FAILURE() },
    { "++{ 1, 1, 1}--;",               EXPECTED_FAILURE() },
    { "--{ 1, 1, 1}--;",               EXPECTED_FAILURE() },
    { "++{ 1, 1, 1}--;",               EXPECTED_FAILURE() },
    { "++a-;",                         EXPECTED_FAILURE() },
    { "++a--;",                        EXPECTED_FAILURE() },
    { "++a++;",                        EXPECTED_FAILURE() },
    { "--a++;",                        EXPECTED_FAILURE() },
    { "--a--;",                        EXPECTED_FAILURE() },
    { "----a;",                        EXPECTED_FAILURE() },
    { "++++a;",                        EXPECTED_FAILURE() },
    { "a.x--;",                        EXPECTED_FAILURE() },
    { "-a.y--;",                       EXPECTED_FAILURE() },
    { "++a.z;",                        EXPECTED_FAILURE() },
    { "++@a--;",                       EXPECTED_FAILURE() },
    { "@a.x--;",                       EXPECTED_FAILURE() },
    { "-@a.y--;",                      EXPECTED_FAILURE() },
    { "++@a.z;",                       EXPECTED_FAILURE() },
    { "--f();",                        EXPECTED_FAILURE() },
    { "f()++;",                        EXPECTED_FAILURE() },
    { "return++;",                     EXPECTED_FAILURE() },
    { "--return;",                     EXPECTED_FAILURE() },
    { "true++;",                       EXPECTED_FAILURE() },
    { "--false;",                      EXPECTED_FAILURE() },
    { "--if;",                         EXPECTED_FAILURE() },
    { "if++;",                         EXPECTED_FAILURE() },
    { "else++;",                       EXPECTED_FAILURE() },
    { "--else;",                       EXPECTED_FAILURE() },
    { "--bool;",                       EXPECTED_FAILURE() },
    { "short++;",                      EXPECTED_FAILURE() },
    { "--int;",                        EXPECTED_FAILURE() },
    { "long++;",                       EXPECTED_FAILURE() },
    { "--float;",                      EXPECTED_FAILURE() },
    { "++double;",                     EXPECTED_FAILURE() },
    { "--vector;",                     EXPECTED_FAILURE() },
    // @todo - disabled as 'matrix' by itself is not yet a keyword
    // { "matrix--;",                 EXPECTED_FAILURE() },
    { "--();",                         EXPECTED_FAILURE() },
    { "()++;",                         EXPECTED_FAILURE() },
    { "{}++;",                         EXPECTED_FAILURE() },
    { "--{};",                         EXPECTED_FAILURE() },
    { "--,;",                          EXPECTED_FAILURE() },
    { ",--;",                          EXPECTED_FAILURE() },

    // invalid declare
    { "int;",                          EXPECTED_FAILURE() },
    { "int 1;",                        EXPECTED_FAILURE() },
    { "string int;",                   EXPECTED_FAILURE() },
    { "int bool a;",                   EXPECTED_FAILURE() },
    { "int a",                         EXPECTED_FAILURE() },
    { "vector a",                      EXPECTED_FAILURE() },
    { "vector float a",                EXPECTED_FAILURE() },

    // invalid function
    { "function(;",                    EXPECTED_FAILURE() },
    { "function);",                    EXPECTED_FAILURE() },
    { "return();",                     EXPECTED_FAILURE() },
    { "function(bool);",               EXPECTED_FAILURE() },
    { "function(bool a);",             EXPECTED_FAILURE() },
    { "function(+);",                  EXPECTED_FAILURE() },
    { "function(!);",                  EXPECTED_FAILURE() },
    { "function(~);",                  EXPECTED_FAILURE() },
    { "function(-);",                  EXPECTED_FAILURE() },
    { "function(&&);",                 EXPECTED_FAILURE() },
    { "function({});",                 EXPECTED_FAILURE() },
    { "function{};" ,                  EXPECTED_FAILURE() },
    { "function(if(true) {});",        EXPECTED_FAILURE() },
    { "function(return);",             EXPECTED_FAILURE() },
    { "function(return;);",            EXPECTED_FAILURE() },
    { "\"function\"();" ,              EXPECTED_FAILURE() },
    { "();",                           EXPECTED_FAILURE() },
    { "@a();",                         EXPECTED_FAILURE() },
    { "+();",                          EXPECTED_FAILURE() },
    { "10();",                         EXPECTED_FAILURE() },

    // invalid keyword return
    { "return return;",                EXPECTED_FAILURE() },
    { "return",                        EXPECTED_FAILURE() },
    { "int return;",                   EXPECTED_FAILURE() },
    { "return return;",                EXPECTED_FAILURE() },
    { "return max(1, 2);",             EXPECTED_FAILURE() },
    { "return 1 + a;",                 EXPECTED_FAILURE() },
    { "return !a;",                    EXPECTED_FAILURE() },
    { "return a = 1;",                 EXPECTED_FAILURE() },
    { "return a.x = 1;",               EXPECTED_FAILURE() },
    { "return ++a;",                   EXPECTED_FAILURE() },
    { "return int(a);",                EXPECTED_FAILURE() },
    { "return {1, 2, 3};",             EXPECTED_FAILURE() },
    { "return a[1];",                  EXPECTED_FAILURE() },
    { "return true;",                  EXPECTED_FAILURE() },
    { "return 0;",                     EXPECTED_FAILURE() },
    { "return (1);",                   EXPECTED_FAILURE() },
    { "return \"a\";",                 EXPECTED_FAILURE() },
    { "return int a;",                 EXPECTED_FAILURE() },
    { "return a;",                     EXPECTED_FAILURE() },
    { "return @a;",                    EXPECTED_FAILURE() },

    // invalid unary
    { "+bool;" ,                       EXPECTED_FAILURE() },
    { "+bool a;" ,                     EXPECTED_FAILURE() },
    { "bool -a;" ,                     EXPECTED_FAILURE() },
    { "-return;" ,                     EXPECTED_FAILURE() },
    { "!return;" ,                     EXPECTED_FAILURE() },
    { "+return;" ,                     EXPECTED_FAILURE() },
    { "~return;" ,                     EXPECTED_FAILURE() },
    { "~if(a) {};" ,                   EXPECTED_FAILURE() },
    { "if(a) -{};" ,                   EXPECTED_FAILURE() },
    { "if(a) {} !else {};",            EXPECTED_FAILURE() },
    { "~;",                            EXPECTED_FAILURE() },
    { "!;",                            EXPECTED_FAILURE() },
    { "+;",                            EXPECTED_FAILURE() },
    { "-;",                            EXPECTED_FAILURE() },
    // @todo  unary crementation expressions should be parsable but perhaps
    //        not compilable
    { "---a;" ,                        EXPECTED_FAILURE() },
    { "+++a;" ,                        EXPECTED_FAILURE() },

    // invalid value
    { ".0.0;",                         EXPECTED_FAILURE() },
    { ".0.0f;",                        EXPECTED_FAILURE() },
    { ".f;",                           EXPECTED_FAILURE() },
    { "0..0;",                         EXPECTED_FAILURE() },
    { "0.0l;",                         EXPECTED_FAILURE() },
    { "0.0ls;",                        EXPECTED_FAILURE() },
    { "0.0s;",                         EXPECTED_FAILURE() },
    { "0.0sf;",                        EXPECTED_FAILURE() },
    { "0.a",                           EXPECTED_FAILURE() },
    { "0.af",                          EXPECTED_FAILURE() },
    { "00ls;",                         EXPECTED_FAILURE() },
    { "0ef;",                          EXPECTED_FAILURE() },
    { "0f0;",                          EXPECTED_FAILURE() },
    { "1.0f.0;",                       EXPECTED_FAILURE() },
    { "1.\"1\";",                      EXPECTED_FAILURE() },
    { "1.e6f;",                        EXPECTED_FAILURE() },
    { "10000000.00000001s;",           EXPECTED_FAILURE() },
    { "1e.6f;",                        EXPECTED_FAILURE() },
    { "1Ee6;",                         EXPECTED_FAILURE() },
    { "1ee6;",                         EXPECTED_FAILURE() },
    { "1eE6f;",                        EXPECTED_FAILURE() },
    { "1ee6f;",                        EXPECTED_FAILURE() },
    { "1l.0;",                         EXPECTED_FAILURE() },
    { "1s.0;",                         EXPECTED_FAILURE() },
    { "\"1.\"2;",                      EXPECTED_FAILURE() },
    { "a.0",                           EXPECTED_FAILURE() },
    { "a.0f",                          EXPECTED_FAILURE() },
    { "false.0;",                      EXPECTED_FAILURE() },
    { "true.;",                        EXPECTED_FAILURE() },

    // invalid vector
    { "{1.0,2.0};",                    EXPECTED_FAILURE() },
    { "{2.0};",                        EXPECTED_FAILURE() },
    { "{1,2,3,4};",                    EXPECTED_FAILURE() },
    { "(1,2,3);",                      EXPECTED_FAILURE() },
    { "{1,2,3];",                      EXPECTED_FAILURE() },
    { "[1,2,3};",                      EXPECTED_FAILURE() },
    { "{,,};",                         EXPECTED_FAILURE() },
    { "{,2,3};",                       EXPECTED_FAILURE() },

    // invalid vector unpack
    { "5.x;",                          EXPECTED_FAILURE() },
    { "foo.2;",                        EXPECTED_FAILURE() },
    { "a.w;",                          EXPECTED_FAILURE() },
    { "a.X;",                          EXPECTED_FAILURE() },
    { "a.Y;",                          EXPECTED_FAILURE() },
    { "a.Z;",                          EXPECTED_FAILURE() },
    { "@a.X;",                         EXPECTED_FAILURE() },
    { "@a.Y;",                         EXPECTED_FAILURE() },
    { "@a.Z;",                         EXPECTED_FAILURE() },
    { "a.xx;",                         EXPECTED_FAILURE() },
    { "a++.x",                         EXPECTED_FAILURE() },
    { "++a.x",                         EXPECTED_FAILURE() },
    { "func().x",                      EXPECTED_FAILURE() },
    { "int(y).x",                      EXPECTED_FAILURE() },
    { "vector foo.x",                  EXPECTED_FAILURE() },
    { "(a + b).x",                     EXPECTED_FAILURE() },
    { "(a).x;",                        EXPECTED_FAILURE() },
    { "(@a).x;",                       EXPECTED_FAILURE() },
    { "@.x;",                          EXPECTED_FAILURE() },
    { "true.x;",                       EXPECTED_FAILURE() },
    { "a.rx;",                         EXPECTED_FAILURE() },
    { "a.rgb;",                        EXPECTED_FAILURE() },
};

}

class TestSyntaxFailures : public CppUnit::TestCase
{
public:

    CPPUNIT_TEST_SUITE(TestSyntaxFailures);
    CPPUNIT_TEST(testSyntax);
    CPPUNIT_TEST_SUITE_END();

    void testSyntax() { TEST_SYNTAX(tests); }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestSyntaxFailures);
// Copyright (c) 2015-2018 DNEG Visual Effects
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
