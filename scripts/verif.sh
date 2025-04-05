#!/bin/bash

# Vérifie qu'un argument est fourni
if [ -z "$1" ]; then
    echo "Usage : $0 <chemin_du_site>"
    exit 1
fi

PATH="$1"

# Vérification de l'arborescence
if [[ ! -d "$PATH/img" || ! -d "$PATH/css" || ! -d "$PATH/script" ]]; then
    echo "Erreur : L'arborescence du site est incorrecte dans '$PATH'."
    exit 1
fi

# Vérification des fichiers à la racine de PATH
if find "$PATH" -maxdepth 1 -type f ! \( -name "*.html" -o -name "*.php" \) | grep -q .; then
    echo "Erreur : '$PATH' ne doit contenir que des fichiers .html ou .php à la racine."
    exit 1
fi

# Vérification des fichiers dans "img"
if find "$PATH/img" -type f ! \( -name "*.png" -o -name "*.jpg" -o -name "*.webp" -o -name "*.svg" \) | grep -q .; then
    echo "Erreur : 'img' ne doit contenir que des fichiers .png, .jpg, .svg ou .webp."
    exit 1
fi

# Vérification des fichiers dans "css"
if find "$PATH/css" -type f ! -name "*.css" | grep -q .; then
    echo "Erreur : 'css' ne doit contenir que des fichiers .css."
    exit 1
fi

# Vérification des fichiers dans "script"
if find "$PATH/script" -type f ! -name "*.js" | grep -q .; then
    echo "Erreur : 'script' ne doit contenir que des fichiers .js."
    exit 1
fi

echo "Toutes les vérifications ont réussi pour '$PATH'."
exit 0
