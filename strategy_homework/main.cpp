#include <iostream>
#include <complex>
#include <tuple>
#include <cmath>
using namespace std;

struct DiscriminantStrategy
{
    virtual double calculate_discriminant(double a, double b, double c) = 0;
};

struct OrdinaryDiscriminantStrategy : DiscriminantStrategy
{
    double calculate_discriminant(double a, double b, double c) override{
        return b*b - 4*a*c;
    }
};

struct RealDiscriminantStrategy : DiscriminantStrategy
{
    double calculate_discriminant(double a, double b, double c) override{
        auto discriminant = b*b - 4*a*c;
        if(discriminant>=0) return discriminant;
        else return nan("");
    }
};

class QuadraticEquationSolver
{
    DiscriminantStrategy& strategy;
public:
    QuadraticEquationSolver(DiscriminantStrategy &strategy) : strategy(strategy) {}

    tuple<complex<double>, complex<double>> solve(double a, double b, double c)
    {
        auto discriminant = strategy.calculate_discriminant(a, b, c);
        auto sqrt_discriminant = sqrt(
                complex<decltype(discriminant)> {discriminant, 0});
        auto sol0 = (-b+sqrt_discriminant)/2./a;
        auto sol1 = (-b-sqrt_discriminant)/2./a;
        return {sol0, sol1};
    }
};


int main(){
    double a=1, b=2, c=3;
    auto ord_strat = OrdinaryDiscriminantStrategy {};
    auto solver = QuadraticEquationSolver(ord_strat);
    auto res = solver.solve(a, b, c);
    cout << get<0>(res) << " " << get<1>(res) << endl;

    auto real_strat = RealDiscriminantStrategy {};
    auto solver2 = QuadraticEquationSolver(real_strat);
    auto res2 = solver2.solve(a, b, c);
    cout << get<0>(res2) << " " << get<1>(res2) << endl;
}