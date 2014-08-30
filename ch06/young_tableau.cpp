#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>


template <typename T, std::pair<int ,int> &dimen>
class YoungTableau {
public:

    YoungTableau(std::initializer_list<T> list) : yt_(list) {}
    ~YoungTableau() =default;

    T extract_min() {

        auto min = yt_[0];

        std::swap(yt_[0], yt_[yt_.size() - 1]);

        yt_.pop_back();

        max_ytify(std::make_pair(0, 0));

        return min;
    }

    void print() {
        for (auto y : yt_) {
            std::cout << y <<std::endl;
        }
    }
private:
    std::vector<T> yt_;

    int getIndex(std::pair<int, int> coordinate) {
        int index = coordinate.first +  coordinate.second * dimen.first;
        return index;
    }

    
    inline std::pair<int, int> parent(std::pair<int, int> coordinate) {
        int first = coordinate.first;
        int second = coordinate.second;

        if (first == 0) {
            first = 1;
        }

        if (second == 0) {
            second = 1;
        }

        return std::make_pair(first - 1, second -1);
    }

    inline std::pair<int, int> left(std::pair<int, int> coordinate) {

        if (coordinate.first == (dimen.first - 1)) {
            return coordinate;
        }

        return std::make_pair(coordinate.first + 1, coordinate.second);
    }

    inline std::pair<int, int> right(std::pair<int, int> coordinate) {
        if (coordinate.second == (dimen.second - 1)) {
                return coordinate;
        }

        return std::make_pair(coordinate.first, coordinate.second + 1);
    }


    void max_ytify(std::pair<int, int> coordinate){

        if (((coordinate.first + 1) * (coordinate.second + 1)) >= yt_.size()) {
            return;
        }
        auto l = left(coordinate);
        auto r = right(coordinate);

        std::cout << "==================" << std::endl;
        std::cout << yt_[getIndex(l)] << std::endl;
        std::cout << yt_[getIndex(r)] << std::endl;
        std::cout << yt_[getIndex(coordinate)] << std::endl;
        std::cout << "==================" << std::endl;
        if (l == coordinate && r == coordinate) {
            return;
        }

        auto min = std::min({yt_[getIndex(l)], yt_[getIndex(r)], yt_[getIndex(coordinate)]});

        std::pair<int, int> min_p;
        if (min == yt_[getIndex(l)]) {
            min_p = l;
        } else if (min == yt_[getIndex(r)]) {
            min_p = r;
        } else {
            return;
        }

        std::swap(yt_[getIndex(min_p)], yt_[getIndex(coordinate)]);
        max_ytify(min_p);
    }
};

    auto c = std::make_pair(4, 4);
int main() {

    YoungTableau<int, c> yt = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

    auto min = yt.extract_min();

    std::cout << min << std::endl;

    yt.print();
}


