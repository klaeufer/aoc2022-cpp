#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <string>
#include <vector>

#include <range/v3/view.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/iterator.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/action.hpp>

#include <doctest/doctest.h>

std::pair<int, int> most_nutritious_inventories(std::string_view const filename) {
  using namespace ranges;
 
  auto line_to_int = [](auto const& s) { return s.empty() ? 0 : std::stoi(s); };
  
  // read lines into vector to support chunk_by, which requires a forward range
  std::ifstream input{filename.data()};
  std::vector<int> data;
  copy(
    getlines(input) | views::transform(line_to_int),
    back_inserter(data)
  );

  auto has_no_zeroes = [](auto const& xs) {
    return none_of(xs, [](auto const x) { return x == 0; });
  };
  
  // divide into chunks separated by blank lines converted to zeroes
  // then add up each chunk's calories
  auto inventories = data 
    | views::chunk_by([](auto const l, auto const r) { return (l == 0) == (r == 0); })
    | views::filter(has_no_zeroes)
    | views::transform([](auto const& c) { return accumulate(c, 0); })
    | to<std::vector>()
    ;
  make_heap(inventories);

  auto constexpr n = 3;
  std::vector<int> top_n;

  for_each(views::ints(0, n), [&](auto i) {
    top_n.push_back(front(inventories));
    pop_heap(inventories);
    inventories.pop_back();
  });

  return std::make_pair(front(top_n), accumulate(top_n, 0));
}

TEST_CASE ("Test function") {
  CHECK(most_nutritious_inventories("data/day1example.txt") == std::pair(24000, 45000));
  auto const result = most_nutritious_inventories("data/day1input.txt");
  std::cout << "Day 1 part 1 (max) = " << result.first << "\n";
  std::cout << "Day 1 part 2 (sum) = " << result.second << "\n";
}
