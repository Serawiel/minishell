#!/bin/bash

# Couleurs
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Compteurs
TOTAL=0
PASSED=0
FAILED=0

# Fonction de test
test_expr() {
    local expr="$1"
    local expected="$2"
    
    TOTAL=$((TOTAL + 1))
    
    result=$(./a.out "$expr" 2>&1)
    
    if [ "$result" == "$expected" ]; then
        echo -e "${GREEN}✓${NC} '$expr' = $expected"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗${NC} '$expr' | Attendu: '$expected' | Obtenu: '$result'"
        FAILED=$((FAILED + 1))
    fi
}

echo "=== TESTS VBC ==="
echo

# Compilation
echo "Compilation..."
cc -Wall -Wextra -Werror vbc.c 2>/dev/null
if [ $? -ne 0 ]; then
    echo -e "${RED}Erreur de compilation!${NC}"
    exit 1
fi
echo -e "${GREEN}Compilation OK${NC}"
echo

# Tests simples
echo "--- Tests simples ---"
test_expr '1' '1'
test_expr '9' '9'
test_expr '0' '0'
echo

# Additions
echo "--- Additions ---"
test_expr '2+3' '5'
test_expr '1+2+3+4+5' '15'
test_expr '0+0' '0'
test_expr '9+1' '10'
echo

# Multiplications
echo "--- Multiplications ---"
test_expr '2*3' '6'
test_expr '2*3*4' '24'
test_expr '9*9' '81'
test_expr '0*5' '0'
test_expr '5*0' '0'
echo

# Priorité
echo "--- Priorité des opérations ---"
test_expr '3*4+5' '17'
test_expr '3+4*5' '23'
test_expr '2+3*4+5' '19'
test_expr '1+2*3+4*5' '27'
echo

# Parenthèses simples
echo "--- Parenthèses simples ---"
test_expr '(3+4)*5' '35'
test_expr '(1)' '1'
test_expr '(9)' '9'
test_expr '(2+3)' '5'
test_expr '(1+2)*3' '9'
echo

# Parenthèses multiples
echo "--- Parenthèses multiples ---"
test_expr '((3))' '3'
test_expr '(((((3)))))' '3'
test_expr '(((((2+2)*2+2)*2+2)*2+2)*2+2)*2' '188'
test_expr '(1+2)*(3+4)' '21'
<<<<<<< HEAD
test_expr '((1+2)*3)' '9'
=======
test_expr '((1+2)*3)' '9's
>>>>>>> b1a44e5 (vbc)
test_expr '((6*6+7+5+8)*(1+0+4*8+7)+2)+4*(1+2)' '2254'
echo

# Expressions complexes
<<<<<<< HEAD
echo "--- Expressions complexes ---"
test_expr '2*4+9+3+2*1+5+1+6+6*1*1+8*0+0+5' '45'
test_expr '1+2*3+4*5+6' '33'
echo

# Erreurs - syntaxe invalide
echo "--- Tests d'erreurs ---"
test_expr '1+' "Unexpected end of input"
test_expr '1+2)' "Unexpected token ')'"
test_expr '(1+2' "Unexpected end of input"
test_expr '((1+2)' "Unexpected end of input"
test_expr ')1+2(' "Unexpected token ')'"
test_expr '1++2' "Unexpected token '+'"
test_expr '1**2' "Unexpected token '*'"
test_expr 'a+2' "Unexpected token 'a'"
test_expr '1+a' "Unexpected token 'a'"
echo

# Résumé
echo "================================="
echo -e "Total: $TOTAL tests"
echo -e "${GREEN}Réussis: $PASSED${NC}"
if [ $FAILED -gt 0 ]; then
    echo -e "${RED}Échoués: $FAILED${NC}"
else
    echo -e "${GREEN}Tous les tests sont passés! 🎉${NC}"
fi
echo "================================="

# Code de sortie
if [ $FAILED -gt 0 ]; then
    exit 1
else
    exit 0
fi
=======
echo "--- Expressi
>>>>>>> b1a44e5 (vbc)
