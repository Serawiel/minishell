#!/bin/bash

# Script de test Valgrind STRICT - Aucune fuite tolérée

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo "=========================================="
echo "   TEST VALGRIND STRICT - 0 LEAK"
echo "=========================================="
echo ""

if [ ! -f "./miniRT" ]; then
    echo -e "${RED}❌ miniRT introuvable${NC}"
    exit 1
fi

if [ ! -d "scenes/error" ]; then
    echo -e "${RED}❌ dossier scenes/error/ introuvable${NC}"
    exit 1
fi

total=0
perfect=0
failed=0

test_strict() {
    local scene=$1
    local description=$2
    
    total=$((total + 1))
    printf "Test %2d: %-40s " "$total" "$description"
    
    # Exécuter Valgrind et capturer la sortie
    output=$(valgrind --leak-check=full --show-leak-kinds=all \
             --errors-for-leak-kinds=all \
             --error-exitcode=42 \
             ./miniRT "$scene" 2>&1)
    
    exit_code=$?
    
    # Extraire TOUS les messages du programme (pas seulement Error)
    program_output=$(echo "$output" | sed -n '/^[A-Z]/p' | grep -v "^==" | head -20)
    
    # Si Valgrind détecte des leaks, exit code = 42
    if [ $exit_code -eq 42 ]; then
        echo -e "${RED}✗ LEAK${NC}"
        failed=$((failed + 1))
        
        # Afficher la sortie complète du programme
        if [ ! -z "$program_output" ]; then
            echo -e "    ${YELLOW}Programme:${NC}"
            while IFS= read -r line; do
                echo "       $line"
            done <<< "$program_output"
        fi
        
        # Afficher les détails des leaks
        echo -e "    ${RED}Leaks:${NC}"
        echo "$output" | grep -E "(definitely lost|indirectly lost|possibly lost|still reachable)" | sed 's/^/       /'
    else
        echo -e "${GREEN}✓ CLEAN${NC}"
        perfect=$((perfect + 1))
        
        # Afficher la sortie complète du programme
        if [ ! -z "$program_output" ]; then
            echo -e "    ${YELLOW}Programme:${NC}"
            while IFS= read -r line; do
                echo "       $line"
            done <<< "$program_output"
        fi
    fi
}

# Tests
test_strict "scenes/error/error_duplicate_ambient.rt" "Duplicate ambient"
test_strict "scenes/error/error_duplicate_camera.rt" "Duplicate camera"
test_strict "scenes/error/error_duplicate_light.rt" "Duplicate light"
test_strict "scenes/error/error_missing_ambient.rt" "Missing ambient"
test_strict "scenes/error/error_missing_camera.rt" "Missing camera"
test_strict "scenes/error/error_missing_light.rt" "Missing light"
test_strict "scenes/error/error_invalid_identifier.rt" "Invalid identifier"
test_strict "scenes/error/error_ambient_wrong_args.rt" "Ambient wrong args"
test_strict "scenes/error/error_camera_wrong_args.rt" "Camera wrong args"
test_strict "scenes/error/error_light_wrong_args.rt" "Light wrong args"
test_strict "scenes/error/error_sphere_wrong_args.rt" "Sphere wrong args"
test_strict "scenes/error/error_plane_wrong_args.rt" "Plane wrong args"
test_strict "scenes/error/error_cylinder_wrong_args.rt" "Cylinder wrong args"
test_strict "scenes/error/error_color_out_of_range.rt" "Color out of range"
test_strict "scenes/error/error_fov_out_of_range.rt" "FOV out of range"
test_strict "scenes/error/error_ambient_ratio_range.rt" "Ambient ratio range"
test_strict "scenes/error/error_light_brightness_range.rt" "Light brightness range"
test_strict "scenes/error/error_empty_file.rt" "Empty file"
test_strict "scenes/error/error_orientation_range.rt" "Orientation range"

# Résumé
echo ""
echo "=========================================="
echo "              RÉSUMÉ STRICT"
echo "=========================================="
echo -e "Total:   $total tests"
echo -e "${GREEN}Perfect: $perfect tests (0 bytes leaked)${NC}"
echo -e "${RED}Failed:  $failed tests (leaks détectés)${NC}"
echo ""

if [ $failed -eq 0 ]; then
    echo -e "${GREEN}🎉 PARFAIT ! Aucune fuite mémoire !${NC}"
    exit 0
else
    echo -e "${RED}❌ $failed tests ont des fuites mémoire${NC}"
    echo -e "${RED}TOUS les leaks doivent être fixés !${NC}"
    exit 1
fi