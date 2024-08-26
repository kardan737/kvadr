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

// Status
int InputCoeff(Coeff* coef);
int OutputSolve(int out_solver, double x1, double x2);
int CleanBuffer();
