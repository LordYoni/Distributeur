#!/bin/bash

# Vérification de l'arborescence
if [[ ! -d "./Raspberry/WebApp/img" || ! -d "./Raspberry/WebApp/css" || ! -d "./Raspberry/WebApp/js" ]]; then
    echo "Erreur : L'arborescence du site est incorrecte."
    exit 1
fi

# Vérification des fichiers dans "./Raspberry/WebApp"
if find ./Raspberry/WebApp -maxdepth 1 -type f ! \( -name "*.html" -o -name "*.php" \) | grep -q .; then
    echo "Erreur : './Raspberry/WebApp' ne doit contenir que des fichiers .html ou .php à la racine."
    exit 1
fi

# Vérification des fichiers dans "img"
if find ./Raspberry/WebApp/img -type f ! \( -name "*.png" -o -name "*.jpg" -o -name "*.webp" \) | grep -q .; then
    echo "Erreur : 'img' ne doit contenir que des fichiers .png, .jpg ou .webp."
    exit 1
fi

# Vérification des fichiers dans "css"
if find ./Raspberry/WebApp/css -type f ! -name "*.css" | grep -q .; then
    echo "Erreur : 'css' ne doit contenir que des fichiers .css."
    exit 1
fi

# Vérification des fichiers dans "js"
if find ./Raspberry/WebApp/js -type f ! -name "*.js" | grep -q .; then
    echo "Erreur : 'js' ne doit contenir que des fichiers .js."
    exit 1
fi

echo "Toutes les vérifications ont réussi."
exit 0