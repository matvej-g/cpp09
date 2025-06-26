#include <iostream>
#include <vector>
#include <algorithm>  // for std::lower_bound
#include <cstdlib>    // for std::atoi

// Compute the Jacobsthal sequence up to n, then produce
// a zero-based insertion order with duplicates removed.
static std::vector<size_t> computeJacobsthalOrder(size_t n) {
    // build raw J-seq until >= n
    std::vector<size_t> J = {0, 1};
    while (J.back() < n) {
        size_t k = J.size();
        J.push_back(J[k-1] + 2 * J[k-2]);
    }
    // build insertion order, skipping >n and dedup
    std::vector<size_t> order;
    std::vector<bool> seen(n, false);
    for (size_t x : J) {
        if (x == 0 || x > n) continue;
        if (!seen[x-1]) {
            order.push_back(x-1);
            seen[x-1] = true;
        }
    }
    // finally any indices 0..n-1 not yet in order
    for (size_t i = 0; i < n; ++i) {
        if (!seen[i]) order.push_back(i);
    }
    return order;
}

static std::vector<int> mergeInsertSort(std::vector<int> vec) {
    if (vec.size() <= 1)
        return vec;

    // 1) Pair off into smaller & larger
    std::vector<int> smaller, larger;
    for (size_t i = 0; i+1 < vec.size(); i += 2) {
        int a = vec[i], b = vec[i+1];
        if (a < b) {
            smaller.push_back(a);
            larger .push_back(b);
        } else {
            smaller.push_back(b);
            larger .push_back(a);
        }
    }
    if (vec.size() % 2) {
        // odd one out
        larger.push_back(vec.back());
    }

    // 2) Recursively sort the "larger" half
    larger = mergeInsertSort(std::move(larger));

    // 3) Insert each "smaller" back into the sorted 'larger'
    auto order = computeJacobsthalOrder(smaller.size());
    for (size_t idx : order) {
        int x = smaller[idx];
        auto it = std::lower_bound(larger.begin(), larger.end(), x);
        larger.insert(it, x);
    }
    return larger;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error: need at least one integer\n";
        return 1;
    }

    //  --- parse inputs ---
    std::vector<int> v;
    for (int i = 1; i < argc; ++i) {
        int x = std::atoi(argv[i]);
        if (x <= 0) {
            std::cerr << "Error\n";
            return 1;
        }
        v.push_back(x);
    }

    //  --- before ---
    std::cout << "Before: ";
    for (int x : v) std::cout << x << ' ';
    std::cout << "\n";

    //  --- sort ---
    auto sorted = mergeInsertSort(v);

    //  --- after ---
    std::cout << "After:  ";
    for (int x : sorted) std::cout << x << ' ';
    std::cout << "\n";

    return 0;
}

// int main(void)
// {
// 	//J0​=0,J1​=1,Jn​=Jn−1​+2Jn−2

// 	int i = 0;
// 	int j1 = 0;
// 	int j2 = 1;

// 	while(i < 10)
// 	{
// 		int j_n = j2 + 2 * j1;
// 		std::cout << j_n << "\n";
// 		j1 = j2;
// 		j2 = j_n;
// 		i++;
// 	}
//}