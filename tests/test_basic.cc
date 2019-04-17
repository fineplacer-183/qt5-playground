#include <tests.h>

void testBasic()
{
  // do some nice calculation; store the results in `foo` and `bar`,
  // respectively
  float foo = 2.0, bar = 1.0;

  ASSERT_THROW( foo != bar );
  ASSERT_EQUAL( foo, 2.0 );
  ASSERT_EQUAL( bar, 1.0 );
}

void testAdvanced()
{
  // a more advanced test
}

int main(int, char**)
{
  testBasic();
  testAdvanced();
}