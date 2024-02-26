#include <stdio.h>
#include <assert.h>
#include "../src/minishell.h"

void    test_quotes_counter()
{
    assert(quotes_counter("") == 1); // Expected to handle empty string
    assert(quotes_counter("Hello, World!") == 1); // No quotes
    assert(quotes_counter("\"Hello, World!\"") == 1); // Quotes at start and end
    assert(quotes_counter("He said, \"Hello, World!\"") == 2); // Single quote inside
    assert(quotes_counter("''") == 1); // Adjacent single quotes
    assert(quotes_counter("\"\"") == 1); // Adjacent double quotes
    assert(quotes_counter("'\"'") == 1); // Mixed adjacent quotes
}

int main()
{
    test_quotes_counter();
    printf("All tests passed.\n");
    return 0;
}

