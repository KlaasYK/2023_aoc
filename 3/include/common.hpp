#include <vector>

bool is_first_column(int idx, int width);

bool is_last_column(int idx, int width);

bool is_first_row(int idx, int width);

bool is_last_row(int idx, int width, int height);

bool is_symbol(char c);

bool is_symbol_adjacent(int idx, std::vector<char> const &schematic, int width, int height);

int is_gear_adjacent(int idx, std::vector<char> const &schematic, int width, int height);
