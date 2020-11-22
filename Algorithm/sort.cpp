#include <algorithm>
#include <cmath>
#include <fmt/ranges.h>
#include <functional>
#include <list>
#include <string>
#include <vector>

using namespace std;
using namespace fmt;

vector<int> data = {1, 54, 3, 5, 7, 3, 6, 8, 13, 5, 4, 7, 22, 10, 23};

inline void PrintData(const vector<int> &data, string msg) {
    print("{} -- {}\n", data, msg);
}

void BubbleSort(vector<int> data) {
    int len = data.size();
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (data[i] > data[j]) {
                swap(data[i], data[j]);
            }
        }
    }
    PrintData(data, __FUNCTION__);
}

void SelectionSort(vector<int> data) {
    int len = data.size();
    for (int i = 0; i < len; i++) {
        int min = i;
        for (int j = i; j < len; j++) {
            if (data[j] < data[min]) {
                min = j;
            }
        }
        swap(data[i], data[min]);
    }
    PrintData(data, __FUNCTION__);
}

void InsertionSort(vector<int> data) {
    int len = data.size();
    for (int i = 1; i < len; i++) {
        int preIndex = i - 1;
        int current = data[i];
        while (preIndex >= 0 && current < data[preIndex]) {
            data[preIndex + 1] = data[preIndex];
            preIndex--;
        }
        data[preIndex + 1] = current;
    }
    PrintData(data, __FUNCTION__);
}

void ShellSort(vector<int> data) {
    int len = data.size();
    for (int gap = len / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < len; i++) {
            int preIndex = i - gap;
            int current = data[i];
            while (preIndex >= 0 && current < data[preIndex]) {
                data[preIndex + gap] = data[preIndex];
                preIndex -= gap;
            }
            data[preIndex + gap] = current;
        }
    }
    PrintData(data, __FUNCTION__);
}

void MergeSort(vector<int> data) {
    function<vector<int>(const vector<int> &, const vector<int> &)> merge;
    merge = [&](const vector<int> &left, const vector<int> &right) -> vector<int> {
        vector<int> result;
        int leftLen = left.size();
        int rightLen = right.size();
        int i = 0, j = 0;
        while (i < leftLen && j < rightLen) {
            if (left[i] < right[j]) {
                result.push_back(left[i]);
                i++;
            } else {
                result.push_back(right[j]);
                j++;
            }
        }
        while (i < leftLen) {
            result.push_back(left[i]);
            i++;
        }
        while (j < rightLen) {
            result.push_back(right[j]);
            j++;
        }
        return result;
    };

    function<vector<int>(vector<int> &)> sort;
    sort = [&](vector<int> &d) -> vector<int> {
        int len = d.size();
        if (len < 2) {
            return d;
        }
        auto half = len / 2;
        vector<int> left(d.cbegin(), d.cbegin() + half);
        vector<int> right(d.cbegin() + half, d.cend());
        return merge(sort(left), sort(right));
    };

    PrintData(sort(data), __FUNCTION__);
}

void QuickSort(vector<int> data) {
    auto getIndex = [](vector<int> &d, int left, int right) -> int {
        int tmp = d[left];
        while (left < right) {
            while (d[right] >= tmp && left < right) {
                right--;
            }
            if (left < right) {
                d[left++] = d[right];
            }
            while (d[left] < tmp && left < right) {
                left++;
            }
            if (left < right) {
                d[right--] = d[left];
            }
        }
        d[left] = tmp;
        return left;
    };

    function<void(vector<int> &, int, int)> sort;
    sort = [&](vector<int> &d, int left, int right) {
        if (left >= right) {
            return;
        }
        int index = getIndex(d, left, right);
        sort(d, left, index - 1);
        sort(d, index + 1, right);
    };

    sort(data, 0, data.size() - 1);
    PrintData(data, __FUNCTION__);
}

int main() {
    PrintData(data, __FUNCTION__);
    BubbleSort(data);
    SelectionSort(data);
    InsertionSort(data);
    ShellSort(data);
    MergeSort(data);
    QuickSort(data);
    return 0;
}
