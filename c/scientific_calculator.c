#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define PI 3.14159265358979
#define MAX_HISTORY 100
#define MAX_EXPR 256
#define MAX_DATA 100

typedef struct {
    char expression[MAX_EXPR];
    double result;
    char category[30];
} History;

History history[MAX_HISTORY];
int histCount = 0;

void addHistory(const char *expr, double result, const char *cat) {
    if (histCount < MAX_HISTORY) {
        strncpy(history[histCount].expression, expr, MAX_EXPR - 1);
        history[histCount].result = result;
        strncpy(history[histCount].category, cat, 29);
        histCount++;
    }
}

double toRad(double deg) { return deg * PI / 180.0; }

/* ── Recursive factorial ── */
long long factorial(int n) {
    if (n < 0)  return -1;
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

/* ── Recursive power ── */
double powerRecursive(double base, int exp) {
    if (exp == 0) return 1;
    if (exp < 0)  return 1.0 / powerRecursive(base, -exp);
    return base * powerRecursive(base, exp - 1);
}

/* ── Recursive sum for statistics ── */
double sumRecursive(double *arr, int n) {
    if (n == 0) return 0;
    return arr[n - 1] + sumRecursive(arr, n - 1);
}

/* ── Recursive binary converter ── */
void decToBin(int n) {
    if (n == 0) { printf("0"); return; }
    if (n > 1)  decToBin(n / 2);
    printf("%d", n % 2);
}

int compareDouble(const void *a, const void *b) {
    double da = *(double *)a, db = *(double *)b;
    return (da > db) - (da < db);
}

/* ════════════════════════════════
   MODULE 1: SCIENTIFIC OPERATIONS
   ════════════════════════════════ */
void moduleScientific() {
    int choice;
    double a, result;
    char expr[MAX_EXPR];

    printf("\n--- SCIENTIFIC OPERATIONS ---\n");
    printf("[1] Trigonometry\n");
    printf("[2] Logarithm\n");
    printf("[3] Square Root & Power\n");
    printf("[4] Factorial\n");
    printf("[5] Combinations & Permutations\n");
    printf("[0] Back\n");
    printf("Choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: {
            int trig;
            printf("Angle in degrees: "); scanf("%lf", &a);
            printf("[1] sin  [2] cos  [3] tan: "); scanf("%d", &trig);
            if      (trig == 1) { result = sin(toRad(a)); sprintf(expr, "sin(%.2f)", a); }
            else if (trig == 2) { result = cos(toRad(a)); sprintf(expr, "cos(%.2f)", a); }
            else                { result = tan(toRad(a)); sprintf(expr, "tan(%.2f)", a); }
            printf("Result: %.6f\n", result);
            addHistory(expr, result, "Trigonometry");
            break;
        }
        case 2: {
            printf("Enter value: "); scanf("%lf", &a);
            if (a <= 0) { printf("Error: Value must be positive!\n"); }
            else {
                printf("log10(%.4f) = %.6f\n", a, log10(a));
                printf("ln   (%.4f) = %.6f\n", a, log(a));
                sprintf(expr, "log(%.4f)", a);
                addHistory(expr, log10(a), "Logarithm");
            }
            break;
        }
        case 3: {
            int sub;
            printf("[1] Square Root  [2] Power: "); scanf("%d", &sub);
            if (sub == 1) {
                printf("Enter value: "); scanf("%lf", &a);
                if (a < 0) printf("Error: Cannot sqrt negative!\n");
                else {
                    result = sqrt(a);
                    printf("sqrt(%.4f) = %.6f\n", a, result);
                    sprintf(expr, "sqrt(%.4f)", a);
                    addHistory(expr, result, "Square Root");
                }
            } else {
                int ep;
                printf("Base: "); scanf("%lf", &a);
                printf("Exponent (integer): "); scanf("%d", &ep);
                result = powerRecursive(a, ep);
                printf("%.4f ^ %d = %.6f\n", a, ep, result);
                sprintf(expr, "%.4f^%d", a, ep);
                addHistory(expr, result, "Power");
            }
            break;
        }
        case 4: {
            int n;
            printf("Enter n (0-20): "); scanf("%d", &n);
            if (n > 20 || n < 0) printf("Out of range!\n");
            else {
                long long f = factorial(n);
                printf("%d! = %lld\n", n, f);
                sprintf(expr, "%d!", n);
                addHistory(expr, (double)f, "Factorial");
            }
            break;
        }
        case 5: {
            int n, r;
            printf("n: "); scanf("%d", &n);
            printf("r: "); scanf("%d", &r);
            if (r > n || n < 0 || r < 0) printf("Invalid values!\n");
            else {
                long long perm = factorial(n) / factorial(n - r);
                long long comb = perm / factorial(r);
                printf("P(%d,%d) = %lld\n", n, r, perm);
                printf("C(%d,%d) = %lld\n", n, r, comb);
            }
            break;
        }
        case 0: break;
        default: printf("Invalid choice!\n");
    }
}

/* ════════════════════════════════
   MODULE 2: STATISTICAL ANALYZER
   ════════════════════════════════ */
void moduleStatistics() {
    double data[MAX_DATA];
    int n, i;

    printf("\n--- STATISTICAL ANALYZER ---\n");
    printf("How many values? (max %d): ", MAX_DATA);
    scanf("%d", &n);
    if (n < 1 || n > MAX_DATA) { printf("Invalid count!\n"); return; }

    printf("Enter %d values:\n", n);
    for (i = 0; i < n; i++) {
        printf("[%d]: ", i + 1); scanf("%lf", &data[i]);
    }

    double sorted[MAX_DATA];
    memcpy(sorted, data, n * sizeof(double));
    qsort(sorted, n, sizeof(double), compareDouble);

    double sum      = sumRecursive(data, n);
    double mean     = sum / n;
    double varSum   = 0;
    for (i = 0; i < n; i++) varSum += (data[i] - mean) * (data[i] - mean);
    double variance = varSum / n;
    double stddev   = sqrt(variance);
    double median;
    if (n % 2 == 0) median = (sorted[n/2 - 1] + sorted[n/2]) / 2.0;
    else            median =  sorted[n/2];

    printf("\n--- RESULTS ---\n");
    printf("Count    : %d\n",     n);
    printf("Sum      : %.4f\n",   sum);
    printf("Mean     : %.4f\n",   mean);
    printf("Median   : %.4f\n",   median);
    printf("Std Dev  : %.4f\n",   stddev);
    printf("Variance : %.4f\n",   variance);
    printf("Min      : %.4f\n",   sorted[0]);
    printf("Max      : %.4f\n",   sorted[n-1]);
    printf("Range    : %.4f\n",   sorted[n-1] - sorted[0]);

    printf("\n--- HISTOGRAM ---\n");
    double maxVal = sorted[n-1];
    for (i = 0; i < n; i++) {
        int bars = (maxVal > 0) ? (int)(sorted[i] / maxVal * 20) : 0;
        printf("%6.2f | ", sorted[i]);
        int j;
        for (j = 0; j < bars; j++) printf("#");
        printf("\n");
    }

    char expr[64];
    sprintf(expr, "Stats on %d values", n);
    addHistory(expr, mean, "Statistics");
}

/* ════════════════════════════════
   MODULE 3: EXPRESSION EVALUATOR
   ════════════════════════════════ */
double parseExpr(const char **s);
double parseTerm(const char **s);
double parseFactor(const char **s);

void skipSpaces(const char **s) { while (**s == ' ') (*s)++; }

double parseFactor(const char **s) {
    skipSpaces(s);
    double val = 0;
    if (**s == '(') {
        (*s)++;
        val = parseExpr(s);
        if (**s == ')') (*s)++;
    } else if (**s == '-') {
        (*s)++; val = -parseFactor(s);
    } else {
        char *end; val = strtod(*s, &end); *s = end;
    }
    return val;
}

double parseTerm(const char **s) {
    double val = parseFactor(s);
    skipSpaces(s);
    while (**s == '*' || **s == '/') {
        char op = **s; (*s)++;
        double rhs = parseFactor(s);
        if (op == '*') val *= rhs;
        else if (rhs != 0) val /= rhs;
        else { printf("Division by zero!\n"); val = 0; }
        skipSpaces(s);
    }
    return val;
}

double parseExpr(const char **s) {
    double val = parseTerm(s);
    skipSpaces(s);
    while (**s == '+' || **s == '-') {
        char op = **s; (*s)++;
        double rhs = parseTerm(s);
        if (op == '+') val += rhs; else val -= rhs;
        skipSpaces(s);
    }
    return val;
}

void moduleExpression() {
    char input[MAX_EXPR];
    printf("\n--- EXPRESSION EVALUATOR ---\n");
    printf("Supports: + - * / and brackets\n");
    printf("Example : 3 + 5 * (2 - 8) / 4\n");
    printf("Type 'back' to return\n\n");

    while (1) {
        printf("Enter expression: ");
        scanf(" ");
        fgets(input, MAX_EXPR, stdin);
        input[strcspn(input, "\n")] = 0;
        if (strcmp(input, "back") == 0) break;
        const char *ptr = input;
        double result = parseExpr(&ptr);
        printf("= %.6f\n\n", result);
        addHistory(input, result, "Expression");
    }
}

/* ════════════════════════════════
   MODULE 4: UNIT CONVERTER
   ════════════════════════════════ */
void moduleConverter() {
    int cat, choice;
    double val, result;

    printf("\n--- UNIT CONVERTER ---\n");
    printf("[1] Length\n[2] Temperature\n[3] Weight\n[0] Back\n");
    printf("Category: "); scanf("%d", &cat);
    if (cat == 0) return;

    printf("Enter value: "); scanf("%lf", &val);
    result = 0;

    if (cat == 1) {
        printf("[1] km->miles  [2] miles->km  [3] m->ft  [4] ft->m\n");
        scanf("%d", &choice);
        if      (choice == 1) { result = val * 0.621371;  printf("%.4f km    = %.4f miles\n", val, result); }
        else if (choice == 2) { result = val * 1.60934;   printf("%.4f miles = %.4f km\n",    val, result); }
        else if (choice == 3) { result = val * 3.28084;   printf("%.4f m     = %.4f ft\n",    val, result); }
        else                  { result = val * 0.3048;    printf("%.4f ft    = %.4f m\n",     val, result); }
    } else if (cat == 2) {
        printf("[1] C->F  [2] F->C  [3] C->K  [4] K->C\n");
        scanf("%d", &choice);
        if      (choice == 1) { result = val*9/5 + 32;  printf("%.2f C = %.2f F\n", val, result); }
        else if (choice == 2) { result = (val-32)*5/9;  printf("%.2f F = %.2f C\n", val, result); }
        else if (choice == 3) { result = val + 273.15;  printf("%.2f C = %.2f K\n", val, result); }
        else                  { result = val - 273.15;  printf("%.2f K = %.2f C\n", val, result); }
    } else {
        printf("[1] kg->lbs  [2] lbs->kg  [3] g->oz  [4] oz->g\n");
        scanf("%d", &choice);
        if      (choice == 1) { result = val * 2.20462;  printf("%.4f kg  = %.4f lbs\n", val, result); }
        else if (choice == 2) { result = val * 0.453592; printf("%.4f lbs = %.4f kg\n",  val, result); }
        else if (choice == 3) { result = val * 0.035274; printf("%.4f g   = %.4f oz\n",  val, result); }
        else                  { result = val * 28.3495;  printf("%.4f oz  = %.4f g\n",   val, result); }
    }

    char expr[64];
    sprintf(expr, "Convert %.4f", val);
    addHistory(expr, result, "Converter");
}

/* ════════════════════════════════
   MODULE 5: QUADRATIC SOLVER
   ════════════════════════════════ */
void moduleQuadratic() {
    double a, b, c, disc;
    printf("\n--- QUADRATIC SOLVER (ax^2 + bx + c = 0) ---\n");
    printf("a: "); scanf("%lf", &a);
    printf("b: "); scanf("%lf", &b);
    printf("c: "); scanf("%lf", &c);

    if (a == 0) { printf("Not quadratic! (a cannot be 0)\n"); return; }

    disc = b*b - 4*a*c;
    printf("\nEquation     : %.2fx^2 + %.2fx + %.2f = 0\n", a, b, c);
    printf("Discriminant : %.4f\n\n", disc);

    if (disc > 0) {
        double r1 = (-b + sqrt(disc)) / (2*a);
        double r2 = (-b - sqrt(disc)) / (2*a);
        printf("Two Real Roots:\n");
        printf("x1 = %.6f\n", r1);
        printf("x2 = %.6f\n", r2);
        char expr[64];
        sprintf(expr, "Quad(%.1f,%.1f,%.1f)", a, b, c);
        addHistory(expr, r1, "Quadratic");
    } else if (disc == 0) {
        double r = -b / (2*a);
        printf("One Repeated Root:\n");
        printf("x = %.6f\n", r);
    } else {
        double real = -b / (2*a);
        double imag = sqrt(-disc) / (2*a);
        printf("Complex Roots:\n");
        printf("x1 = %.4f + %.4fi\n", real, imag);
        printf("x2 = %.4f - %.4fi\n", real, imag);
    }
}

/* ════════════════════════════════
   MODULE 6: NUMBER BASE CONVERTER
   ════════════════════════════════ */
void moduleBaseConverter() {
    int n, choice;
    printf("\n--- NUMBER BASE CONVERTER ---\n");
    printf("[1] Decimal -> All Bases\n");
    printf("[2] Binary  -> Decimal\n");
    printf("[3] Hex     -> Decimal\n");
    printf("[4] Octal   -> Decimal\n");
    printf("Choice: "); scanf("%d", &choice);

    if (choice == 1) {
        printf("Decimal: "); scanf("%d", &n);
        printf("Binary  : "); decToBin(n); printf("\n");
        printf("Octal   : %o\n", n);
        printf("Hex     : %X\n", n);
        char expr[32];
        sprintf(expr, "Dec %d -> All", n);
        addHistory(expr, n, "Base Convert");
    } else if (choice == 2) {
        char bin[64];
        printf("Binary: "); scanf("%s", bin);
        int dec = 0, base = 1, len = strlen(bin);
        int i;
        for (i = len - 1; i >= 0; i--) { dec += (bin[i] - '0') * base; base *= 2; }
        printf("Decimal: %d\n", dec);
    } else if (choice == 3) {
        char hex[32];
        printf("Hex: "); scanf("%s", hex);
        int dec; sscanf(hex, "%x", &dec);
        printf("Decimal: %d\n", dec);
    } else if (choice == 4) {
        int oct;
        printf("Octal: "); scanf("%o", &oct);
        printf("Decimal: %d\n", oct);
    }
}

/* ════════════════════════════════
   MODULE 7: HISTORY
   ════════════════════════════════ */
void sortHistoryByResult() {
    int i, j;
    for (i = 0; i < histCount - 1; i++)
        for (j = 0; j < histCount - i - 1; j++)
            if (history[j].result > history[j+1].result) {
                History tmp  = history[j];
                history[j]   = history[j+1];
                history[j+1] = tmp;
            }
}

void searchHistory(const char *keyword) {
    int found = 0, i;
    printf("\nSearch results for '%s':\n", keyword);
    for (i = 0; i < histCount; i++) {
        if (strstr(history[i].expression, keyword) ||
            strstr(history[i].category,   keyword)) {
            printf("[%d] %-30s = %.6f  (%s)\n",
                   i+1, history[i].expression,
                   history[i].result, history[i].category);
            found++;
        }
    }
    if (!found) printf("No matches found.\n");
}

void moduleHistory() {
    int choice, i;
    printf("\n--- CALCULATION HISTORY ---\n");
    if (histCount == 0) { printf("No history yet!\n"); return; }

    printf("[1] View All\n[2] Sort by Result\n[3] Search\n");
    printf("Choice: "); scanf("%d", &choice);

    if (choice == 2) sortHistoryByResult();

    if (choice == 1 || choice == 2) {
        printf("\n%-4s %-30s %-15s %s\n", "#", "Expression", "Result", "Category");
        printf("----------------------------------------------------------\n");
        for (i = 0; i < histCount; i++)
            printf("%-4d %-30s %-15.6f %s\n",
                   i+1, history[i].expression,
                   history[i].result, history[i].category);
    } else if (choice == 3) {
        char kw[64];
        printf("Keyword: "); scanf("%s", kw);
        searchHistory(kw);
    }
}

/* ════════════════════════════════
   MAIN MENU
   ════════════════════════════════ */
int main() {
    int choice;

    printf("==========================================\n");
    printf("   SCIENTIFIC CALCULATOR & ANALYZER\n");
    printf("==========================================\n");

    do {
        printf("\n--- MAIN MENU ---\n");
        printf("[1] Scientific Operations\n");
        printf("[2] Statistical Analyzer\n");
        printf("[3] Expression Evaluator\n");
        printf("[4] Unit Converter\n");
        printf("[5] Quadratic Equation Solver\n");
        printf("[6] Number Base Converter\n");
        printf("[7] Calculation History (%d entries)\n", histCount);
        printf("[0] Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: moduleScientific();    break;
            case 2: moduleStatistics();    break;
            case 3: moduleExpression();    break;
            case 4: moduleConverter();     break;
            case 5: moduleQuadratic();     break;
            case 6: moduleBaseConverter(); break;
            case 7: moduleHistory();       break;
            case 0: printf("\nGoodbye!\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
