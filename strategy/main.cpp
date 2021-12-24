#include <iostream>
#include <vector>
#include <memory>
#include <boost/numeric/ublas/matrix.hpp>

namespace ublas = boost::numeric::ublas;


class FitterBase{
public:
    // Note: not pure virtual
    virtual boost::numeric::ublas::matrix<double> get_xtx() {
        std::cout << "base xtx getter" << std::endl;
        return {};
    };
    virtual std::vector<ublas::vector<double>> solve(ublas::vector<double>) const {
        std::cout << "base solve" << std::endl;
        return {};
    };
    void run(){
        get_xtx();
        solve({0, 0});
    }
};

class Fitter_Regularization_20211224 : public FitterBase{
public:
    std::vector<ublas::vector<double>> solve(ublas::vector<double>) const override {
        std::cout << "Regularization_20211124 solve" << std::endl;
        return {};
    }
};

class Fitter_SR_20211225 : public FitterBase{
public:
    boost::numeric::ublas::matrix<double> get_xtx() override {
        std::cout << "SR_20211225 xtx getter" << std::endl;
        return {};
    };
};

int main() {
    std::vector<FitterBase*> experiments;
    experiments.emplace_back(new FitterBase);
    experiments.emplace_back(new Fitter_Regularization_20211224);
    experiments.emplace_back(new Fitter_SR_20211225);
    for(auto exp : experiments){
        exp->run();
        std::cout << std::endl;
    }
    return 0;
}
