#include <iostream>
#include <string>
#include <vector>
#include <utility>

class GraphObject{
public:
    explicit GraphObject(std::string name):name(std::move(name)){}
    virtual ~GraphObject() = default;
    virtual void print(const size_t& indent) const = 0;
    virtual void scale(const int& scaler) = 0;
    std::string name;
};

class Signal : public GraphObject{
public:
    explicit Signal(std::string name):GraphObject(std::move(name)), obj_scaler(1){}
    void print(const size_t& indent) const override{
        std::cout << std::string(indent, ' ') << "Signal_" << name << " " << obj_scaler << std::endl;
    }
    void scale(const int& scaler) override{
        obj_scaler *= scaler;
    }
    int obj_scaler;
    [[nodiscard]] Signal* begin() const {return const_cast<Signal*>(this);} // const away constness
    [[nodiscard]] Signal* end() const {return const_cast<Signal*>(this+1);}
};

class Combiner : public GraphObject{
public:
    explicit Combiner(std::string name):GraphObject(std::move(name)){}
    std::vector<GraphObject*> contents;
    void push_back(GraphObject * const gptr){
        contents.push_back(gptr);
    }
    void print(const size_t& indent) const override{
        std::cout << std::string(indent, ' ') << "Combiner_" << name << std::endl;
        for (auto& gptr : contents){
            gptr->print(indent + 4);
        }
    }
    void scale(const int& scaler) override{
        for (auto& gptr : contents){
            gptr->scale(scaler);
        }
    }
    [[nodiscard]] decltype(contents)::const_iterator begin() const { return contents.begin(); }
    [[ nodiscard]] decltype(contents)::const_iterator end() const { return contents.end(); }
};


int main() {
    auto* vwap = new Signal {"vwap"};
    auto* wave = new Signal {"wave"};
    auto* comb0 = new Combiner {"Combiner0"};
    comb0->push_back(vwap);
    comb0->push_back(wave);
    auto* comb1 = new Combiner {"Combiner1"};
    auto* self_return = new Signal{"self_return"};
    comb1->push_back(comb0);
    comb1->push_back(self_return);
    comb1->print(0);

    std::cout << std::endl;
    self_return->scale(3);
    comb1->scale(2);
    comb1->print(0);

    // begin & end are implemented for both Signal and Combiner
    for(auto v : *vwap){;}
    for(auto v: *comb1){;}
    return 0;
}
