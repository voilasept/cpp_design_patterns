#include <iostream>
#include <array>
#include <numeric>
using namespace std;

enum Attribute{ LOW, MID, HIGH, LENGTH };

template <typename AttrType>
class StockBar{
public:
    std::array<AttrType, Attribute::LENGTH> attributes;
    [[nodiscard]] AttrType get(Attribute attr) const { return attributes[attr]; };
    [[nodiscard]] AttrType get_sum() const {
        return std::accumulate(attributes.begin(), attributes.end(), AttrType(0));
    }
    [[nodiscard]] AttrType get_max() const {
        return *std::max_element(attributes.begin(), attributes.end());
    }
    [[nodiscard]] AttrType get_min() const {
        return *std::max_element(
                attributes.begin(), attributes.end(), [](AttrType x, AttrType y){return x>y;} );
    }
};

int main() {
    StockBar<int> bar {};
    bar.attributes[Attribute::LOW] = 1;
    bar.attributes[Attribute::MID] = 3;
    bar.attributes[Attribute::HIGH] = 4;
    std::cout << "High " << bar.get(Attribute::HIGH) << std::endl;
    std::cout << "Sum " << bar.get_sum() << std::endl;
    std::cout << "Max " << bar.get_max() << std::endl;
    std::cout << "Min " << bar.get_min() << std::endl;
    return 0;
}
