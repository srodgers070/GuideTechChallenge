#include <iostream>
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
#include <vector>

int main() {
    /* Set up vector to hold chars a-z */
    std::vector<char> path;
    for (int ch = 'a'; ch <= 'z'; ++ch)
        path.push_back(ch);

    /* Print path vector to console */
    std::copy(path.begin(), path.end(), std::ostream_iterator<char>(std::cout, " "));

    return 0;
}