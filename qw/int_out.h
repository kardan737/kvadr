
// #define #ifdef ...
enum Options
    {
    NONE         = 0,
    VERIFICATION = 1,
    SOLUTION     = 2,
    EXIT         = 3,
    RT           = 4,
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

const char* const rt =  "пр пр пр пр пр пр пр пр         пр пр пр пр пр пр пр пр пр пр пр пр\n"
                    "пр пр пр пр пр пр пр пр PT      пр пр пр пр пр пр пр пр пр пр пр пр\n"
                    "PT PT пр пр пр пр пр пр пр      пр пр пр пр пр пр пр пр пр пр пр пр\n"
                    "PT PT                PT PT пр                  пр пр               \n"
                    "PT PT                   PT пр                  пр пр               \n"
                    "PT PT                   пр пр                  пр пр               \n"
                    "PT PT                   пр пр                  пр пр               \n"
                    "PT PT                   пр пр                  пр пр               \n"
                  "%sPT PT                   пр пр                  пр пр               \n"
                    "PT PT                пр пр пр                  пр пр               \n"
                    "PT PT пр пр пр пр пр пр пр                     пр пр               \n"
                    "PT PT пр пр пр пр пр пр пр                     пр пр               \n"
                    "PT PT пр пр пр пр пр пр                        пр пр               \n"
                    "PT PT                                          пр пр               \n"
                    "PT PT                                          пр пр               \n%s"
                  "%sPT PT                                          пр пр               \n"
                    "PT PT                                          пр пр               \n"
                    "PT PT                                          пр пр               \n"
                    "PT PT                                          пр пр               \n"
                    "PT PT                                          пр пр               \n"
                    "PT PT                                          пр пр               \n"
                    "PT PT                                          пр пр               \n"
                    "PT PT                                          пр пр               \n%s";

const char* const seagull =
"\n                                                                              .\n"
"                                           :-+**##%###*+=-.                .---: \n"
"                                       .=*%#+=:..      .:-+*+-         :=**=.    \n"
"                                     =#%*-.                  :++.  :=*%*-        \n"
"                                   =%#=.                        ++%%*-           \n"
"                                 .#%=                        :*%%%+-             \n"
"                                :%#:                       =%%%%=   -            \n"
"                               :%#.                       #%%%*.     :           \n"
"                               +*.    ...                *%%%=        .          \n"
"                     .:--=++**##%%%%%%%%%%#=.           -%%%=                    \n"
"           .:-=++*#%%%%%%%%%%%%%%%%%%%%%%%%%%*-         %%%*                     \n"
"   .::---==--:::=*%%##*++==--:=+::--+*%%%%%%%%%%+.     =%%%                      \n"
"               ..             =%       :+%%%%%%%%%*:   %%%+       .:.            \n"
"                              .%:         :*%%%%%%%%#==%%%::-+*#%%#-             \n"
"                               =+           :*%%%%%%%%%%%%%%%%%#+:               \n"
"                                *-           :#%%%%%%%%%%%%*=-.                  \n"
"                                 +:     .-+*%%%%%%%%#*+-:.                       \n"
"                                  ::.::-: :##*+=-:.                              \n"
"                                    ::                                           \n"
"                                      ..                                         \n";

// Status
int InputCoeff(Coeff* coef);
int OutputSolve(int out_solver, double x1, double x2);
int CleanBuffer();

