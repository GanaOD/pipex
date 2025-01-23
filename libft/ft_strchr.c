/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:59:13 by go-donne          #+#    #+#             */
/*   Updated: 2024/10/27 16:08:39 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>
// #include <limits.h>
// #include <stddef.h>

char	*ft_strchr(const char *src, int c)
{
	unsigned char	chr;

	chr = (unsigned char)c;
	while (*src)
	{
		if ((unsigned char)*src == chr)
			return ((char *)src);
		src++;
	}
	if (chr == '\0')
		return ((char *)src);
	return (NULL);
}

// /* Test Result Structure */
// typedef struct s_test_result {
//     int passed;
//     char *message;
// } t_test_result;

// /* Test Case Structure */
// typedef struct s_test_case {
//     const char *name;        // Test name
//     const char *str;         // Input string
//     int search_val;         
	// Search value (int, not char, to test conversion)
//     const char *expected;   
	// Expected return value (NULL or pointer offset) - Now const
//     int analyze_offset;     // Whether to analyze pointer offset
// } t_test_case;

// /* Print Utilities */
// static void print_test_header(const char *group_name) {
//     printf("\n=== %s ===\n", group_name);
// }

// static void print_test_result(const t_test_case *test,
//	t_test_result result) {
//     printf("\nTest: %s\n", test->name);
//     printf("Input string: \"%s\"\n", test->str);
//     printf("Search value: %d (0x%x)\n", test->search_val, test->search_val);
//     printf("Result: %s\n", result.passed ? "PASS" : "FAIL");
//     if (!result.passed) {
//         printf("Error: %s\n", result.message);
//     }
// }

// /* Core Testing Logic */
// static t_test_result run_single_test(const t_test_case *test) {
//     t_test_result result = {0, NULL};
//     const char *got = ft_strchr(test->str, test->search_val);
//     const char *expected = test->expected;

//     if (got == expected) {
//         result.passed = 1;
//         return result;
//     }

//     // If expected is NULL, got should be NULL
//     if (expected == NULL && got == NULL) {
//         result.passed = 1;
//         return result;
//     }

//     // If analyzing offset is important (for string position tests)
//     if (test->analyze_offset && expected != NULL && got != NULL) {
//         if (got - test->str == expected - test->str) {
//             result.passed = 1;
//             return result;
//         }
//     }

//     result.passed = 0;
//     static char err_msg[256];
//     snprintf(err_msg, sizeof(err_msg), 
//              "Expected: %p, Got: %p", (void*)expected, (void*)got);
//     result.message = err_msg;
//     return result;
// }

// /* Test Groups - Using Systematic Analysis */

// // 1. Bit-level Analysis Tests
// static void test_bit_patterns(void) {
//     print_test_header("Bit Pattern Tests");

//     static const char test_str[] = "test";

//     t_test_case tests[] = {
//         {
//             "NULL byte - direct",
//             test_str,
//             '\0',
//             test_str + 4,
//             1
//         },
//         {
//             "NULL byte - via 256",
//             test_str,
//             256,
//             test_str + 4,
//             1
//         },
//         {
//             "NULL byte - via 1024",
//             test_str,
//             1024,
//             test_str + 4,
//             1
//         },
//     };

//     for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
//         print_test_result(&tests[i], run_single_test(&tests[i]));
//     }
// }

// // 2. Position Analysis Tests
// static void test_string_positions(void) {
//     print_test_header("String Position Tests");

//     static const char test_str[] = "hello world";
//     t_test_case tests[] = {
//         {
//             "First character",
//             test_str,
//             'h',
//             test_str,
//             1
//         },
//         {
//             "Middle character",
//             test_str,
//             'o',
//             test_str + 4,
//             1
//         },
//         {
//             "Last character",
//             test_str,
//             'd',
//             test_str + 10,
//             1
//         },
//         {
//             "Terminating null",
//             test_str,
//             '\0',
//             test_str + 11,
//             1
//         }
//     };

//     for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
//         print_test_result(&tests[i], run_single_test(&tests[i]));
//     }
// }

// // 3. Edge Case Analysis
// static void test_edge_cases(void) {
//     print_test_header("Edge Cases");

//     static const char empty_str[] = "";
//     static const char single_char[] = "x";

//     t_test_case tests[] = {
//         {
//             "Empty string - searching for null",
//             empty_str,
//             '\0',
//             empty_str,
//             1
//         },
//         {
//             "Empty string - searching for char",
//             empty_str,
//             'x',
//             NULL,
//             0
//         },
//         {
//             "Single char string - searching for that char",
//             single_char,
//             'x',
//             single_char,
//             1
//         },
//         {
//             "Very large search value",
//             "test",
//             INT_MAX,
//             NULL,
//             0
//         }
//     };

//     for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
//         print_test_result(&tests[i], run_single_test(&tests[i]));
//     }
// }

// int main(void) {
//     printf("Starting ft_strchr tests...\n");

//     test_bit_patterns();
//     test_string_positions();
//     test_edge_cases();

//     return 0;
// }