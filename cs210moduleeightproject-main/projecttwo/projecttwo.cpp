#include <iostream>
#include <iomanip>

class InvestmentCalculator {
// declare variables
private:
    double initialInvestment;
    double monthlyDeposit;
    double annualInterestRate;
    int numberOfYears;

public:
    InvestmentCalculator(double initInvestment, double monthlyDep, double annualInterest, int numYears)
        : initialInvestment(initInvestment), monthlyDeposit(monthlyDep), annualInterestRate(annualInterest), numberOfYears(numYears) {}

    void calculateAndDisplay() {
        // print data needed
        std::cout << "Initial Investment Amount: $" << std::fixed << std::setprecision(2) << initialInvestment << std::endl;
        std::cout << "Monthly Deposit: $" << std::fixed << std::setprecision(2) << monthlyDeposit << std::endl;
        std::cout << "Annual Interest: %" << std::fixed << std::setprecision(2) << annualInterestRate << std::endl;
        std::cout << "Number of Years: " << numberOfYears << std::endl;
        std::cout << "Press any key to continue..." << std::endl;
        std::cin.get();

        // calc and display balance and interest w/o monthly deposits
        std::cout << "Balance and Interest Without Additional Monthly Deposits" << std::endl;
        std::cout << "Year\tYear End Balance\tYear End Earned Interest" << std::endl;
        double balance = initialInvestment;
        double earnedInterest = 0.0;
        for (int year = 1; year <= numberOfYears; year++) {
            earnedInterest = balance * (annualInterestRate / 100);
            balance += earnedInterest;
            std::cout << year << "\t$" << std::fixed << std::setprecision(2) << balance << "\t\t\t$" << std::fixed << std::setprecision(2) << earnedInterest << std::endl;
        }

        // calc and display balance and interest w/ monthly deposits
        std::cout << "\nBalance and Interest With Additional Monthly Deposits" << std::endl;
        std::cout << "Year\tYear End Balance\tYear End Earned Interest" << std::endl;
        balance = initialInvestment;
        earnedInterest = 0.0;
        for (int year = 1; year <= numberOfYears; year++) {
            for (int month = 1; month <= 12; month++) {
                balance += monthlyDeposit;
                earnedInterest = balance * (annualInterestRate / 100) / 12;
                balance += earnedInterest;
            }
            std::cout << year << "\t$" << std::fixed << std::setprecision(2) << balance << "\t\t$" << std::fixed << std::setprecision(2) << earnedInterest << std::endl;
        }
    }
};

int main() {
    // declare variables
    double initialInvestment, monthlyDeposit, annualInterestRate;
    int numberOfYears;

    // get user input
    std::cout << "**************************************\n";
    std::cout << "Enter Initial Investment Amount: $";
    std::cin >> initialInvestment;
    std::cout << "Enter Monthly Deposit: $";
    std::cin >> monthlyDeposit;
    std::cout << "Enter Annual Interest Rate (%): ";
    std::cin >> annualInterestRate;
    std::cout << "Enter Number of Years: ";
    std::cin >> numberOfYears;
    std::cout << "**************************************\n";

    // create investment calc opject
    InvestmentCalculator calculator(initialInvestment, monthlyDeposit, annualInterestRate, numberOfYears);
    calculator.calculateAndDisplay();

    return 0;
}
