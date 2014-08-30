#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <utility>


template <typename T, int dimen = 2>
class max_heap {
public:
    using iterator_type = typename std::vector<T>::iterator;

    max_heap() = default;

    max_heap(std::initializer_list<T> list) :heap_ {list} {}

    void build_max_heap() {

        auto iter = heap_.rbegin();

        for (; iter != heap_.rend(); iter++) {
            max_heapify(iter.base());
        }
    }

    T heap_get_max() {
        return heap_[0];
    }

    T heap_extract_max() {

        auto max = heap_[0];

        std::swap(heap_[0], heap_[heap_.size() - 1]);

        heap_.pop_back();

        max_heapify(heap_.begin());

        return max;
    }

    void heap_insert(T value) {
        heap_.push_back(value);
        heap_increase_key(heap_.end() - 1, value);
    }

    void print() {
        for (auto h: heap_) {
            std::cout << h << std::endl;
        }
    }

    bool operator< (const max_heap<T>& lhs) const {
        return true;
    }

    bool empty() const {
        return heap_.empty();
    }

    ~max_heap() =default;

private:
    std::vector<T> heap_;

    inline iterator_type parent(iterator_type i) {
        if (i == heap_.begin()) {
            return i;
        }

        auto dis = ((i - heap_.begin()) - 1) / dimen;
        return heap_.begin() + dis;
    }

    inline iterator_type left(iterator_type i) {

        auto dis = (((i - heap_.begin()) * dimen) + 1);
        if (dis >= heap_.size()) {
            return heap_.end();
        }

        return heap_.begin() + dis;
    }

    inline iterator_type right(iterator_type i) {
        auto dis = ((i - heap_.begin() + 1) * dimen);

        if (dis >= heap_.size()) {
            return heap_.end();
        }

        return heap_.begin() + dis;
    }

    void heap_increase_key(iterator_type i, T value) {
        if (value < *i) {
            return;
        }

        *i = value;
        for( ;i != heap_.end(); ) {

            auto p = parent(i);
            value = *i;
            if (value > *p) {
                std::swap(*p, *i);
                i = parent(i);
            } else {
                return;
            }
        }

    }

    void max_heapify(iterator_type i) {
        auto l = left(i);
        auto r = right(i);

        if (l == heap_.end()) {
            return;
        }

        decltype(l) max_iter;
        if (r == heap_.end()) {
            max_iter = std::max_element(l, heap_.end());
        } else {
            max_iter = std::max_element(l, r + 1);
        }

        if (*max_iter <= *i) {
            return;
        }

        std::swap(*max_iter, *i);
        max_heapify(max_iter);
    }
};


std::unique_ptr<std::vector<int>>
mergeN(std::vector<std::shared_ptr<max_heap<int>>> &hs)
{
    auto result = new std::vector<int>();

    max_heap<std::pair<int, std::shared_ptr<max_heap<int>>>> mh = {};

    for (auto h : hs) {
        auto max = h->heap_extract_max();
        mh.heap_insert(std::make_pair(max, h));
    }

    while(!mh.empty()) {
        auto p = mh.heap_extract_max();
        result->push_back(p.first);
        if (p.second->empty()) {
            continue;
        }

        auto max = p.second->heap_extract_max();
        mh.heap_insert(std::make_pair(max, p.second));
    }

    return std::unique_ptr<std::vector<int>>(result);
}

int main() {

    max_heap<int> mh = {16,4,10,14,7, 9, 3, 2, 8, 1};

    mh.build_max_heap();

    mh.print();

    std::cout << "============" << std:: endl;
    std::cout << mh.heap_extract_max() << std::endl;

    std::cout << "============" << std:: endl;
    mh.print();

    std::cout << "============" << std:: endl;
    std::cout << mh.heap_extract_max() << std::endl;

    std::cout << "============" << std:: endl;
    mh.print();

    std::cout << "============" << std:: endl;
    std::cout << mh.heap_extract_max() << std::endl;

    std::cout << "============" << std:: endl;
    mh.print();
    std::cout << "============" << std:: endl;

    mh.heap_insert(20);
    mh.print();

    std::cout << "============" << std:: endl;

    max_heap<int, 4> mh2 = {16,4,10,14,7, 9, 3, 2, 8, 1};
    mh2.build_max_heap();
    mh2.print();
    std::cout << "============" << std:: endl;

    std::cout << "merge n" << std:: endl;

    auto hs = std::vector<std::shared_ptr<max_heap<int>>>();

    max_heap<int> ms1 = {16, 15, 14, 13, 12, 11};
    hs.push_back(std::make_shared<max_heap<int>>(ms1));
    max_heap<int> ms2 = {17, 15, 11, 9, 7, 6};
    hs.push_back(std::make_shared<max_heap<int>>(ms2));
    max_heap<int> ms3 = {20, 19 , 18};
    hs.push_back(std::make_shared<max_heap<int>>(ms3));
    max_heap<int> ms4 = {16, 15, 14, 13, 12, 11, 10 , 9 , 8};
    hs.push_back(std::make_shared<max_heap<int>>(ms4));

    auto s = mergeN(hs);

    for(auto r : *s) {
        std::cout << r << std::endl;
    }

    return 1;
}
