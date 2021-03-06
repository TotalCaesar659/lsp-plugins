/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 22 авг. 2018 г.
 *
 * lsp-plugins is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * lsp-plugins is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with lsp-plugins. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef TEST_TEST_H_
#define TEST_TEST_H_

#include <data/cvector.h>

#ifdef LSP_TESTING
    #define TEST_EXPORT(ptr)        ::test::Test::mark_supported(ptr)
    #define TEST_SUPPORTED(ptr)     ::test::Test::check_supported(ptr)
#else
    #define TEST_EXPORT(ptr)
    #define TEST_SUPPORTED(ptr)     false
#endif /* LSP_TESTING */

#define TEST_ASSERT(code) \
        if (!(code)) { \
            fprintf(stderr, "Test assertion has failed at file %s, line %d:\n  %s\n", \
                    __FILE__, __LINE__, # code); \
            exit(2); \
        }

namespace test
{
    class Test
    {
        private:
            static lsp::cvector<void> support;
            static void     __mark_supported(const void *x);
            static bool     __check_supported(const void *ptr);

        protected:
            const char     *__test_group;
            const char     *__test_name;
            mutable char   *__full_name;
            bool            __verbose;
            const char     *__executable;

        public:
            int             printf(const char *fmt, ...);
            int             eprintf(const char *fmt, ...);

        public:
            inline const char *name() const         { return __test_name; }
            inline const char *group() const        { return __test_group; }
            inline const char *executable() const   { return __executable; }
            const char *full_name() const;

        public:
            explicit Test(const char *group, const char *name);
            virtual ~Test();

        public:
            inline void set_verbose(bool verbose)       { __verbose = verbose; }
            inline void set_executable(const char *name){ __executable = name; }

            virtual void execute(int argc, const char **argv) = 0;

            virtual void init();

            virtual bool ignore() const;

            virtual void destroy();

            virtual Test *next_test() const = 0;

        public:
            template <typename T>
                static inline void     mark_supported(T x)
                {
                    __mark_supported(reinterpret_cast<const void *>(x));
                }

            template <typename T>
                static bool     check_supported(T x)
                {
                    return __check_supported(reinterpret_cast<const void *>(x));
                }

    };
}

#endif /* TEST_TEST_H_ */
