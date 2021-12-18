#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ITERATOR

class BankAccount{
public:
    BankAccount(int overdraft_limit)
            :balance(0), overdraft_limit(overdraft_limit){}
    int balance;
    int overdraft_limit;
    bool deposit(int amount){
        balance += amount;
        return true;
    }
    bool withdraw(int amount){
        if (balance - amount >= overdraft_limit){
            balance -= amount;
            return true;
        }
        return false;
    }
    void query() const{
        cout << balance << endl;
    }
};

class Command{
public:
    enum Action {DEPOSIT, WITHDRAW};
    Command(BankAccount& bk):bk(bk) { succeed=false; called=false; }
    ~Command() = default;
    BankAccount& bk;
    virtual bool call() = 0;
    virtual bool undo() = 0;
//protected:  // state recording is important in command pattern!
    bool succeed;
    bool called;
    friend ostream &operator<<(ostream &os, const Command &command) {
        os << "balance: " << command.bk.balance
           << " succeed: " << command.succeed
           << " called: " << command.called << "\n";
        return os;
    }
};

class SingleCommand : public Command{
public:
    int amount;
    Action action;
    SingleCommand(BankAccount& bk, Action action, int amount)
            : Command(bk), action(action), amount(amount) {}
    bool call() override{
        if (called) {
            throw std::logic_error("Call on called!");
        }
        called = true;
        switch (action) {
            case Action::DEPOSIT:
                return succeed = bk.deposit(amount);
            case Action::WITHDRAW:
                return succeed = bk.withdraw(amount);
            default:
                throw std::invalid_argument("Invalid action!");
        }
    }
    bool undo() override{
        if (not called){
            throw std::logic_error("Undo on un-called!");
        }
        called = false;
        if (not succeed){
            return false;
        }
        succeed = false;
        switch (action) {
            case Action::DEPOSIT:
                return bk.withdraw(amount);
            case Action::WITHDRAW:
                return bk.deposit(amount);
            default:
                throw std::invalid_argument("Invalid action!");
        }
    }
};

class MultiCommand : public Command{
public:
    vector<Command*> commands;
    MultiCommand(BankAccount& bk):Command(bk) {}
    void emplace_back(Command* cmd){
        commands.emplace_back(cmd);
    }
    bool call() override{
        if (called){
            throw std::logic_error("Call on called!");
        }
        called = true;
        succeed = true;
        for(auto& cmd : commands){
            // succeed must be placed 2nd otherwise may skip!
            succeed = cmd->call() and succeed;
            if (not succeed) break; // dependency
        }
        return succeed;
    }
    bool undo() override{
        if (not called){
            throw std::logic_error("Undo on un-called!");
        }
        called = false;
        succeed = true;
        for(auto iter=commands.rbegin(); iter!=commands.rend(); iter++){
            if (not (*iter)->succeed) continue; // dependency
            (*iter)->undo();
        }
        return succeed;
    }

#ifdef ITERATOR
    class MultiCommandIterator{
    public:
        MultiCommand* multi_commands;
        size_t index;
        MultiCommandIterator(MultiCommand* multi_commands, size_t index)
            :multi_commands(multi_commands), index(index) {}
        bool operator==(MultiCommandIterator& other) const {
            return multi_commands==other.multi_commands
                   and index == other.index;
        }
        bool operator!=(MultiCommandIterator& other) const {
            return multi_commands==other.multi_commands
                   and index != other.index;
        }
        MultiCommandIterator& operator++(){
            index++;
            return *this;
        }
        Command& operator*() const {
            return *(multi_commands->commands[index]);
        }
    };
    MultiCommandIterator begin(){
        return {this, 0};
    }
    MultiCommandIterator end(){
        return {this, commands.size()};
    }
#endif
};


int main() {
    BankAccount bk {-500};
    MultiCommand commands {bk};
    commands.emplace_back(new SingleCommand {bk, SingleCommand::Action::DEPOSIT, 200});
    commands.emplace_back(new SingleCommand {bk, SingleCommand::Action::WITHDRAW, 500});
    commands.emplace_back(new SingleCommand {bk, SingleCommand::Action::WITHDRAW, 500});
    commands.emplace_back(new SingleCommand {bk, SingleCommand::Action::DEPOSIT, 1000});

    bk.query();
    commands.call();
    bk.query();
    commands.undo();
    bk.query();

#ifdef ITERATOR
    cout << "Test iterator:" << endl;
    for(Command& cmd : commands){
        cout << cmd;
    }
#endif
    return 0;
}