enum Options
    {
    NONE         = 0,
    VERIFICATION = 1,
    SOLUTION     = 2,
    EXIT         = 3,
    };

enum ErrorType
    {
    ERROR_SOLVE = 1,
    ERROR_EOF   = 1,
    };

enum Status
    {
    ERROR,
    OK,
    };

#define GREEN "\033[1;32m"
#define RED   "\033[1;31m"
#define BLUE  "\033[1;34m"
#define RESET "\033[0m"

// Status
int InputCoeff(Coeff* coef);
int OutputSolve(int out_solver, double x1, double x2);
int CleanBuffer();
