#!/bin/bash

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Compile
echo "Compilation..."
gcc -Wall -Wextra -Werror argo.c -o argo
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed${NC}"
    exit 1
fi
echo -e "${GREEN}Compilation OK${NC}\n"

# Test counter
total=0
passed=0

# Function to test
test_case() {
    local input="$1"
    local expected="$2"
    local description="$3"
    
    total=$((total + 1))
    result=$(echo -n "$input" | ./argo /dev/stdin)
    
    if [ "$result" == "$expected" ]; then
        echo -e "${GREEN}✓${NC} Test $total: $description"
        passed=$((passed + 1))
    else
        echo -e "${RED}✗${NC} Test $total: $description"
        echo "  Input:    '$input'"
        echo "  Expected: '$expected'"
        echo "  Got:      '$result'"
    fi
}

echo "=== TESTS BASIQUES ==="
test_case '1' '1' "Integer simple"
test_case '42' '42' "Integer 42"
test_case '-5' '-5' "Integer négatif"
test_case '0' '0' "Zero"
test_case '-0' '0' "Negative zero"
test_case '"bonjour"' '"bonjour"' "String simple"
test_case '""' '""' "String vide"

echo -e "\n=== TESTS ECHAPPEMENT ==="
test_case '"escape! \" "' '"escape! \" "' "Echappement guillemet"
test_case '"\\"' '"\\"' "Echappement backslash"
test_case '"test\\\"test"' '"test\\\"test"' "Echappement multiple"
test_case '"\\\\"' '"\\\\"' "Double backslash"
test_case '"\"\""' '"\"\""' "Double guillemet échappé"
test_case '"\\\\\\\"' '"\\\\\\\""' "Backslash + guillemet échappé"

echo -e "\n=== TESTS MAP ==="
test_case '{}' '{}' "Map vide"
test_case '{"key":1}' '{"key":1}' "Map simple"
test_case '{"tomatoes":42,"potatoes":234}' '{"tomatoes":42,"potatoes":234}' "Map deux éléments"
test_case '{"a":1,"b":2,"c":3}' '{"a":1,"b":2,"c":3}' "Map trois éléments"
test_case '{"":"empty"}' '{"":"empty"}' "Clé vide"
test_case '{"key":""}' '{"key":""}' "Valeur vide"
test_case '{"":""}' '{"":""}' "Clé et valeur vides"

echo -e "\n=== TESTS RECURSION ==="
test_case '{"inner":{}}' '{"inner":{}}' "Map dans map vide"
test_case '{"a":{"b":1}}' '{"a":{"b":1}}' "Map dans map simple"
test_case '{"recursion":{"recursion":{"recursion":{"recursion":"recursion"}}}}' '{"recursion":{"recursion":{"recursion":{"recursion":"recursion"}}}}' "Récursion profonde"
test_case '{"x":{"y":{"z":42}}}' '{"x":{"y":{"z":42}}}' "Map imbriquée avec integer"
test_case '{"a":{"b":{"c":{"d":{"e":{"f":{"g":"deep"}}}}}}}' '{"a":{"b":{"c":{"d":{"e":{"f":{"g":"deep"}}}}}}}' "Récursion très profonde"

echo -e "\n=== TESTS ERREURS BASIQUES ==="
test_case '"unfinished string' 'unexpected end of input' "String non terminée"
test_case '"unfinished string 2\"' 'unexpected end of input' "String avec échappement non terminée"
test_case '{"no value?":}' 'unexpected token '\''}'\''' "Map sans valeur"
test_case '{' 'unexpected end of input' "Map non terminée"
test_case '{"key":' 'unexpected end of input' "Map valeur manquante"
test_case '{"key"}' 'unexpected token '\''}'\''' "Map sans deux-points"
test_case ' ' 'unexpected token '\'' '\''' "Espace (invalide)"

echo -e "\n${YELLOW}=== TESTS EVIL 😈 ===${NC}"
test_case '' 'unexpected end of input' "Input vide"
test_case '"\' 'unexpected end of input' "Backslash seul en fin de string"
test_case '"\a"' 'unexpected token '\''a'\''' "Echappement invalide \\a"
test_case '"\n"' 'unexpected token '\''n'\''' "Echappement invalide \\n"
test_case '{"key":1' 'unexpected end of input' "Map sans accolade fermante"
test_case '{"key":1,' 'unexpected end of input' "Map virgule finale sans élément"
test_case '{"key":1,}' 'unexpected token '\''}'\''' "Map virgule avant accolade"
test_case '{,}' 'unexpected token '\'','\''' "Map avec virgule seule"
test_case '{"a":1,"a":2}' '{"a":1,"a":2}' "Clés dupliquées (devrait parser)"
test_case '{1:2}' 'unexpected token '\''1'\''' "Clé non-string"
test_case '{"key" "value"}' 'unexpected token '\''"'\''' "Map sans deux-points"
test_case '{"key"::1}' 'unexpected token '\'':'\''' "Double deux-points"
test_case '{"key":1,,}' 'unexpected token '\'','\''' "Double virgule"
test_case '{"":{"":{"":""}}}' '{"":{"":{"":""}}}' "Clés vides imbriquées"
test_case '1234567890' '1234567890' "Grand nombre"
test_case '-1234567890' '-1234567890' "Grand nombre négatif"
test_case '--1' 'unexpected token '\''-'\''' "Double moins"
test_case '1-' '1' "Nombre suivi d'un moins (scanf s'arrête)"
test_case '{"a":{"b":' 'unexpected end of input' "Map imbriquée non terminée"
test_case '{"\\":"\\"}' '{"\\":"\\"}' "Backslash comme clé et valeur"
test_case '{"\"":"\""}' '{"\"":"\""}' "Guillemet échappé comme clé et valeur"
test_case '{"\\\\":1}' '{"\\\\":1}' "Double backslash comme clé"
test_case 'null' 'unexpected token '\''n'\''' "null non supporté"
test_case 'true' 'unexpected token '\''t'\''' "true non supporté"
test_case 'false' 'unexpected token '\''f'\''' "false non supporté"
test_case '[]' 'unexpected token '\''['\''' "Array non supporté"
test_case '[1,2,3]' 'unexpected token '\''['\''' "Array avec éléments"
test_case '1.5' '1' "Float (devrait s'arrêter au point)"
test_case '{"key":1.5}' '{"key":1}' "Float dans map"
test_case '1e10' '1' "Notation scientifique"
test_case '+1' 'unexpected token '\''+'\''' "Plus non supporté"
test_case '{"key":{}}' '{"key":{}}' "Map vide comme valeur"
test_case '{"":"","":""}' '{"":"","":""}' "Deux clés vides"
test_case '"\\\\\\\\"' '"\\\\\\\\"' "Quatre backslashes"

echo -e "\n=== TESTS ULTRA EVIL 💀 ==="
test_case '{"a":{"b":{"c":{"d":{"e":{"f":{"g":{"h":{"i":{"j":"x"}}}}}}}}}}' '{"a":{"b":{"c":{"d":{"e":{"f":{"g":{"h":{"i":{"j":"x"}}}}}}}}}}' "10 niveaux d'imbrication"
test_case '{"}":"}"}' '{"}":"}"}' "Guillemet échappé dans clé et valeur"
test_case '{"\\n":"\\t"}' '{"\\n":"\\t"}' "Echappements invalides mais parsés comme caractères normaux"
test_case '{"key":{"":{"":1}}}' '{"key":{"":{"":1}}}' "Clés vides imbriquées avec valeur"
test_case '":"' 'unexpected token '\'':'\''' "Deux-points seul"
test_case ',' 'unexpected token '\'','\''' "Virgule seule"
test_case '}' 'unexpected token '\''}'\''' "Accolade fermante seule"
test_case '{"}' 'unexpected end of input' "Accolade + guillemet non terminé"
test_case '{"' 'unexpected end of input' "Accolade + guillemet"
test_case '"\\\\\\\\\\\\"' '"\\\\\\\\\\\\"' "Six backslashes"

echo -e "\n=== RÉSUMÉ ==="
echo -e "Tests passés: ${GREEN}$passed${NC}/$total"

if [ $passed -eq $total ]; then
    echo -e "${GREEN}Tous les tests sont passés ! 🎉${NC}"
    exit 0
else
    echo -e "${RED}Certains tests ont échoué${NC}"
    failed=$((total - passed))
    echo -e "${RED}$failed${NC} test(s) échoué(s)"
    exit 1
fi